#ifndef CUBE_H
#define CUBE_H

#include "Geometry.h"
#include "Quad.h"

namespace Geometry {

    struct Cube {
        // underlying data structure for a cube
        Quad quads[QUADS_PER_CUBE];

        static constexpr std::array<unsigned int, 36> indices = {
            0,  1,  2,  0,  2,  3,  // front
            4,  5,  6,  4,  6,  7,  // right side
            8,  9,  10, 8,  10, 11, // back
            12, 13, 14, 12, 14, 15, // left side
            16, 17, 18, 16, 18, 19, // bottom
            20, 21, 22, 20, 22, 23  // top
        };

        // creates a default cube with scale = 1
        Cube();

        // copy constructor
        Cube(const Cube& other);

        // Assignment operator
        Cube& operator=(const Cube& other);

        // creates a cube where the offsets are added to the position data in the vertices
        Cube(float offsetX, float offsetY, float offsetZ);

        // creates a cube where the offsets are added to the position data in the vertices,
        // AND multiplied by the scale in the end.
        Cube(float offsetX, float offsetY, float offsetZ, float scale);
        
        // Does the same thing as the previous two constructors
        // but accepts glm vectors as arguments rather than just floats
        Cube(const glm::vec3& offset);
        Cube(const glm::vec4& offsetAndScale);

        // accepts an array of quads so a cube can be made manually by the user
        Cube(std::array<Quad, 6> quadArr);

        bool operator==(const Cube& other) const;
        bool operator!=(const Cube& other) const;

        // resets the cube to default cube
        void Reset();

        // resets the cube position vertices to default
        void ResetPosition();

        // sets the scale of the cube
        void setScale(float scale);

        // calculates the scale of the cube
        float getScale();

        // adds X Y and Z to the vertices positions
        void addOffset(float X, float Y, float Z);
        void addOffset(const glm::vec3& offset);

        // adds X Y and Z to the vertices positions, and scales it about the cube's center
        void addOffsetAndScale(float X, float Y, float Z, float scale);
        void addOffsetAndScale(const glm::vec4& offsetAndScale);

        // sets the position of the cube
        void setPosition(float X, float Y, float Z);
        void setPosition(const glm::vec3& position);
        
        // sets the position AND scale of the cube
        void setPositionAndScale(float X, float Y, float Z, float scale);
        void setPositionAndScale(const glm::vec4& positionAndScale);

        // sets the cube to normalized device coordinates relative to the maxDist
        void setNormalizedDeviceCoordinates(float maxDist);

        // returns the center coordinate of the cube
        glm::vec3 getCenter();

        // converts a cube into an array of floats (raw vertex data)
        std::tuple<float*, size_t> floats(); 
    
        // set bottom corner position rather than setting position by the center
        void setBottomCornerPosition(float X, float Y, float Z);
        void setBottomCornerPosition(const glm::vec3& position);

        // returns the bottom corner position
        glm::vec3 getBottomCornerPosition();

        // sets the texture coordinates for every cube face
        void setAllTextureCoords(TextureAtlas* a, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        
        // sets the texture coordinates for individual faces
        void setTopTextureCoords(TextureAtlas* a, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        void setBackTextureCoords(TextureAtlas* a, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        void setLeftTextureCoords(TextureAtlas* a, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        void setRightTextureCoords(TextureAtlas* a, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        void setFrontTextureCoords(TextureAtlas* a, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        void setBottomTextureCoords(TextureAtlas* a, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        
        // sets the texture coords for all the side faces
        void setSidesTextureCoords(TextureAtlas* a, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        
        // sets the texture coords for both the top and bottom
        void setTopBottomTextureCoords(TextureAtlas* a, uint32_t x, uint32_t y, uint32_t width, uint32_t height);


        void setTopTextureArrayIndex(float index);
        void setBackTextureArrayIndex(float index);
        void setLeftTextureArrayIndex(float index);
        void setRightTextureArrayIndex(float index);
        void setFrontTextureArrayIndex(float index);
        void setBottomTextureArrayIndex(float index);

        void setAllTextureArrayIndex(float index);
        void setSidesTextureArrayIndex(float index);
        void setTopBottomTextureArrayIndex(float index);

        Quad* getQuad(Geometry::Direction dir);
        Quad copyQuad(Geometry::Direction dir) const;
    };
}

#endif 
