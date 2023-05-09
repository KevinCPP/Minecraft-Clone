#ifndef QUAD_H
#define QUAD_H

// project headers
#include "Vertex.h"
#include "Geometry.h"
#include "TextureAtlas.h"

namespace Geometry {

    struct Quad {
        // a quad is just 4 vertices
        std::array<Vertex, VERTICES_PER_QUAD> vertices;
        
        // constructors
        Quad() = default;
        Quad(std::initializer_list<Vertex> list);
        Quad(const std::array<Vertex, VERTICES_PER_QUAD>& v);
        Quad(const Vertex* v);

        // A texture atlas has X columns and Y rows of textures. This function will accept x and y, which will be
        // the bottom left corner of the texture you want. Then, rather than simply doing x+1 and y+1 to find
        // the top right corner, we will use (x + width) and (y + height) in case you have a texture that takes up
        // two slots in the texture atlas. Useful for any blocks (paintings?) that are multiple blocks wide/tall.
        void setTextureCoordsFromAtlas(TextureAtlas* a, uint32_t x, uint32_t y, uint32_t width, uint32_t height);

        // returns the indices for an index buffer
        std::array<unsigned int, 6> getIndices();

        void addOffset(float X, float Y, float Z);
        void addOffsetAndScale(float X, float Y, float Z, float scale);

        void addOffset(const glm::vec3& offset);
        void addOffsetAndScale(const glm::vec4& offsetAndScale);
    };

}
#endif
