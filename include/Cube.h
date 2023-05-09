#ifndef CUBE_H
#define CUBE_H

#include "Geometry.h"
#include "Quad.h"

namespace Geometry {

    struct Cube {
        // underlying data structure for a cube
        std::array<Quad, QUADS_PER_CUBE> quads;

        // creates a default cube with scale = 1
        Cube();

        // creates a cube where the offsets are added to the position data in the vertices
        Cube(float offsetX, float offsetY, float offsetZ);

        // creates a cube where the offsets are added to the position data in the vertices,
        // AND multiplied by the scale in the end.
        Cube(float offsetX, float offsetY, float offsetZ, float scale);
        
        // Does the same thing as the previous two constructors
        // but accepts glm vectors as arguments rather than just floats
        Cube(const glm::vec3& offset);
        Cube(const glm::vec4& offsetAndScale);

        // Will accept coordinates of the cube relative to the camera, then the max coordinates
        // so that it can be converted into normalized device coordinates in the constructor
        Cube(float X, float Y, float Z, float maxX, float maxY, float maxZ);

        // Will create a cube with normalized device coordinates, and scaled about the center of the cube.
        Cube(float X, float Y, float Z, float scale, float maxX, float maxY, float maxZ);

        // same thing as previous two, but accepts glm vectors instead of floats
        Cube(const glm::vec3& position, const glm::vec3& maxPosition);
        Cube(const glm::vec4& positionAndScale, const glm::vec3& maxPosition);

        // accepts an array of quads so a cube can be made manually by the user
        Cube(std::array<Quad, 6> quads);

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

        // sets the cube to normalized device coordinates relative to the maxX, maxY, and maxZ
        void setNormalizedDeviceCoordinates(float maxX, float maxY, float maxZ);
        void setNormalizedDeviceCoordinates(const glm::vec3& maxPosition);

        // returns the center coordinate of the cube
        glm::vec3 getCenter();

        // converts a cube into an array of floats (raw vertex data)
        std::array<float, FLOATS_PER_CUBE> getFloatArray(); 
    };

}

#endif 
