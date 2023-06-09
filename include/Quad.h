#ifndef QUAD_H
#define QUAD_H

#include <ankerl/unordered_dense.h>

// project headers
#include "Utility.h"
#include "Vertex.h"
#include "Geometry.h"
#include "TextureAtlas.h"

#include <vector>

namespace Geometry {
     
    struct Quad {
        // a quad is just 4 vertices
        Vertex vertices[VERTICES_PER_QUAD];

        // indices for rendering a quad
        static constexpr std::array<unsigned int, 6> indices = { 0, 1, 2, 0, 2, 3 };

        // constructors
        Quad() = default;
        Quad(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4);
//        Quad(std::initializer_list<Vertex> list);
        Quad(const std::array<Vertex, VERTICES_PER_QUAD>& v);
        Quad(const Vertex* v);

        // A texture atlas has X columns and Y rows of textures. This function will accept x and y, which will be
        // the bottom left corner of the texture you want. Then, rather than simply doing x+1 and y+1 to find
        // the top right corner, we will use (x + width) and (y + height) in case you have a texture that takes up
        // two slots in the texture atlas. Useful for any blocks (paintings?) that are multiple blocks wide/tall.
        void setTextureCoordsFromAtlas(TextureAtlas* a, uint32_t x, uint32_t y, uint32_t width, uint32_t height);

        // sets the Z value for texture coordinates
        void setTextureArrayIndex(float index);
        
        float getTextureArrayIndex();

        // rotates the quad around the X, Y, or Z axis respectively.
        void rotateZ();
        void rotateY();
        void rotateX();

        // returns the normal vector of the quad
        glm::vec3 getNormal() const;

        // returns the center point of the quad
        glm::vec3 getCenter() const;

        bool isFacingCamera(const glm::vec3& cameraPos) const;

        // applies a general transformation matrix to the quad
        void transform(const glm::mat4& transformationMatrix);
        
        // add an offset to the quad
        void addOffset(float X, float Y, float Z);
        void addOffset(const glm::vec3& offset);
        
        // returns the scale in the x/y direction
        void setScale(const glm::vec2& xyscale);

        void setHeight(float height);

        bool operator==(const Quad& other) const;
        bool operator!=(const Quad& other) const;
    };
    
    // stores information about the location of a quad and which way it's facing.
    struct QuadLocation {
        int16_t x, y, z;
        uint8_t face;

        QuadLocation(int16_t cx, int16_t cy, int16_t cz, Geometry::Direction dir) : x(cx), y(cy), z(cz), face((uint8_t)dir) { }
        QuadLocation(int16_t cx, int16_t cy, int16_t cz, uint8_t dir) : x(cx), y(cy), z(cz), face(dir) { } 
        
        bool operator==(const QuadLocation& other) const { return x == other.x && y == other.y && z == other.z && face == other.face; }
    };
    
    // hash functor for the QuadLocation struct
    struct QuadLocation_hash_avalanching {
        using is_avalanching = void;
        uint64_t operator()(const QuadLocation& obj) const noexcept;
    };
    
    // given a number of quads and a reference to a vector, it will insert the proper indices into the vector.
    void makeIndicesFromQuads(size_t numQuads, std::vector<unsigned int>& vec);
}
#endif
