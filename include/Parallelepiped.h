#ifndef PARALLELEPIPED_H
#define PARALLELEPIPED_H

#include "Geometry.h"
#include "Vertex.h"
#include "Quad.h"

namespace Geometry {
    class Parallelepiped {
    public:
        
        // construct it with 1x1x1
        Parallelepiped();

        // construct it with a given length, width, and height
        Parallelepiped(float x, float y, float z);
        Parallelepiped(const glm::vec3& dimensions);

        // getters
        glm::vec3 getDimensions();

        // setters
        void setDimensions(float x, float y, float z);
        void setDimensions(const glm::vec3& dimensions);

        // get a copy of any of the quads
        Quad copyQuad(Direction dir) const;
        
        // set the texture for a given face
        void setTextureArrayIndex(Direction dir, unsigned int index);

//    private:
        // private member variables
        glm::vec3 m_Dimensions;
        Quad m_Quads[QUADS_PER_CUBE];
        
        // function to update quad after dimensions are changed
        void updateQuads();
    };
}
#endif
