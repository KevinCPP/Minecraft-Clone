#include "../include/Quad.h"

namespace Geometry {
    
    // Constructor that accepts an initializer list of vertices
    Quad::Quad(std::initializer_list<Vertex> list) {
        if(list.size() == VERTICES_PER_QUAD) {
            auto it = list.begin();
            for(size_t i = 0; i < VERTICES_PER_QUAD && it != list.end(); ++i, ++it) {
                vertices[i] = *it;
            }
        }
    }

    // Constructor that accepts an array of vertices
    Quad::Quad(const std::array<Vertex, VERTICES_PER_QUAD>& v) {
        std::copy(v.begin(), v.end(), vertices.begin()); 
    }

    // Constructor that accepts a C-Style array of vertices
    Quad::Quad(const Vertex* v) {
        std::copy(v, v + VERTICES_PER_QUAD, vertices.begin());
    }

    // sets the texture coordinates of the vertices in the quad to a specific texture in the atlas.
    // width and height are how many "blocks" (textures) large it should be. Useful if you need to use
    // two texture slots in the texture atlas for a quad that is two blocks wide, for example
    void Quad::setTextureCoordsFromAtlas(TextureAtlas* a, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        assert(VERTICES_PER_QUAD == 4 && "VERTICES_PER_QUAD != 4");

        vertices[0].setTextureCoords(a->getTextureCoords(x, y + height));
        vertices[1].setTextureCoords(a->getTextureCoords(x, y));
        vertices[2].setTextureCoords(a->getTextureCoords(x + width, y + height));
        vertices[3].setTextureCoords(a->getTextureCoords(x + width, y));
    }

    // returns the order in which vertices should be rendered to render the quad.
    // can be used with an Index Buffer.
    std::array<unsigned int, 6> Quad::getIndices() {
        assert(VERTICES_PER_QUAD == 4 && "VERTICES_PER_QUAD != 4");
        return {0, 1, 2, 2, 1, 3};
    }

    void Quad::addOffset(float X, float Y, float Z) {
        addOffset(glm::vec3(X, Y, Z)); 
    }

    void Quad::addOffsetAndScale(float X, float Y, float Z, float scale) {
        addOffsetAndScale(glm::vec4(X, Y, Z, scale));
    }

    void Quad::addOffset(const glm::vec3& offset) {
        for(auto& v : vertices) {
            v.setPosition(v.getPosition() + offset);
        }
    }

    void Quad::addOffsetAndScale(const glm::vec4& offsetAndScale) {
        std::cout << "not implemented\n"; 
    }

}



