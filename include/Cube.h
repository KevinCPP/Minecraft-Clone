#ifndef CUBE_H
#define CUBE_H

#include "Geometry.h"
#include "Vertex.h"
#include "Quad.h"

namespace Geometry {
    class Cube {
    public:
        
        // construct it with 1x1x1
        Cube();

        // construct it with a given length, width, and height
        Cube(float sizeX, float sizeY, float sizeZ);
        Cube(const glm::vec3& dimensions);

        // getters
        glm::vec3 getDimensions();

        // setters
        void setDimensions(float sizeX, float sizeY, float sizeZ);
        void setDimensions(const glm::vec3& dimensions);
        void setPosition(float x, float y, float z);
        void setPosition(const glm::vec3& position);


        // get a copy of any of the quads
        Quad copyQuad(Direction dir) const;
        
        glm::vec3 getPosition();

        // set the texture for a given face
        void setTextureArrayIndex(Direction dir, unsigned int index);
        void setTopBottomTextureArrayIndex(unsigned int index);
        void setSidesTextureArrayIndex(unsigned int index);
        void setAllTextureArrayIndex(unsigned int index);

//    private:
        // private member variables
        glm::vec3 m_Center;
        glm::vec3 m_Dimensions;
        Quad m_Quads[QUADS_PER_CUBE];
        
        // function to update quad after dimensions are changed
        void updateQuads();
    };
}
#endif
