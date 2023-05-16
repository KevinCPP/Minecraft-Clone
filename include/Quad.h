#ifndef QUAD_H
#define QUAD_H

// project headers
#include "Vertex.h"
#include "Geometry.h"
#include "TextureAtlas.h"

namespace Geometry {

    struct Quad {
        // a quad is just 4 vertices
        Vertex vertices[VERTICES_PER_QUAD];

        // indices for rendering a quad
        static constexpr std::array<unsigned int, 6> indices = { 0, 1, 2, 0, 2, 3 };

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

        // sets the Z value for texture coordinates
        void setTextureArrayIndex(float index);

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

        // add an offset to the quad, then scale it
        void addOffsetAndScale(float X, float Y, float Z, float scale);

        bool operator==(const Quad& other) const;
        bool operator!=(const Quad& other) const;

        void setNormalizedDeviceCoordinates(float scale);

        void addOffset(const glm::vec3& offset);
        void addOffsetAndScale(const glm::vec4& offsetAndScale);
    };

    struct QuadInstanceData {
        
    }

    // returns a tuple with an array of floats, and the size of the array
    inline std::tuple<float*, size_t> getFloatArray(Quad* quads, size_t numQuads) {
        return std::make_tuple((float*)quads, numQuads * FLOATS_PER_QUAD);
    }
}
#endif
