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
        memcpy(vertices, v.data(), sizeof(Vertex) * VERTICES_PER_QUAD);
    }

    // Constructor that accepts a C-Style array of vertices
    Quad::Quad(const Vertex* v) {
        assert(v != NULL && "Attempting to initialize quad with NULL array!");
        memcpy(vertices, v, sizeof(Vertex) * VERTICES_PER_QUAD);
    }

    bool Quad::operator==(const Quad& other) const {
        for(size_t i = 0; i < VERTICES_PER_QUAD; i++) {
            if(vertices[i] != other.vertices[i]) return false;
        }

        return true;
    }

    bool Quad::operator!=(const Quad& other) const {
        for(size_t i = 0; i < VERTICES_PER_QUAD; i++) {
            if(vertices[i] == other.vertices[i]) return false;
        }

        return true;
    }

    // sets the texture coordinates of the vertices in the quad to a specific texture in the atlas.
    // width and height are how many "blocks" (textures) large it should be. Useful if you need to use
    // two texture slots in the texture atlas for a quad that is two blocks wide, for example
    void Quad::setTextureCoordsFromAtlas(TextureAtlas* a, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        assert(VERTICES_PER_QUAD == 4 && "VERTICES_PER_QUAD != 4");
        
        float tol = 0.002f;

        vertices[0].setTextureCoords(a->getTextureCoords(x, y + height) + glm::vec2(tol, -tol) );
        vertices[1].setTextureCoords(a->getTextureCoords(x, y) + glm::vec2(tol, tol));
        vertices[2].setTextureCoords(a->getTextureCoords(x + width, y + height) + glm::vec2(-tol, -tol));
        vertices[3].setTextureCoords(a->getTextureCoords(x + width, y) + glm::vec2(-tol, tol));
    } 

    bool Quad::isFacingCamera(const glm::vec3& cameraPos) const {
        glm::vec3 toCamera = glm::normalize(cameraPos - getCenter());
        return glm::dot(getNormal(), toCamera) < 0;
    }

    glm::vec3 Quad::getCenter() const {
        glm::vec3 center(0.0f);
        for (const auto& vertex : vertices) {
            center += vertex.getPosition();
        }
        return center / static_cast<float>(VERTICES_PER_QUAD);
    }


    glm::vec3 Quad::getNormal() const {
        glm::vec3 edge1 = vertices[1].getPosition() - vertices[0].getPosition();
        glm::vec3 edge2 = vertices[2].getPosition() - vertices[0].getPosition();

        glm::vec3 normal = glm::cross(edge1, edge2);

        return glm::normalize(normal);
    }

    void Quad::setTextureArrayIndex(float index) {
        assert(index >= 0.0f && "Z value for Texture Array cannot be zero!");
        for(auto& v : vertices)
            v.setTextureArrayIndex(index);
    }

    void Quad::rotateX() {
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        transform(rotation);
    }

    void Quad::rotateY() {
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        transform(rotation);
    }

    void Quad::rotateZ() {
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        transform(rotation);
    }

    void Quad::transform(const glm::mat4& transformationMatrix) {
        for(auto& v : vertices)
            v.setPosition(glm::vec4(v.getPosition(), 1.0f) * transformationMatrix);
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
        for(auto& v : vertices) {
            v.setPosition((v.getPosition() + glm::vec3(offsetAndScale)) * offsetAndScale.w);
        }
    }

}



