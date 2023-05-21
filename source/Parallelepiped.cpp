#include "../include/Parallelepiped.h"

namespace Geometry {
    Parallelepiped::Parallelepiped() {
        setDimensions(1.0f, 1.0f, 1.0f);
    }

    Parallelepiped::Parallelepiped(float x, float y, float z) {
        setDimensions(x, y, z);
    }

    Parallelepiped::Parallelepiped(const glm::vec3& dimensions) {
        setDimensions(dimensions);
    }

    glm::vec3 Parallelepiped::getDimensions() {
        return m_Dimensions;
    }

    void Parallelepiped::setDimensions(float x, float y, float z) {
        m_Dimensions = glm::vec3(x, y, z);
        updateQuads();
    }

    void Parallelepiped::setDimensions(const glm::vec3& dimensions) {
        m_Dimensions = dimensions;
        updateQuads();
    }

    Quad Parallelepiped::copyQuad(Direction dir) const {
        std::string msg = "Attempting to copy a quad with an invalid direction! returning default (front)"; 
        if(Utility::warn(dir >= QUADS_PER_CUBE, msg))
            return m_Quads[FRONT];
        
        return m_Quads[dir];
    }

    void Parallelepiped::setTextureArrayIndex(Direction dir, unsigned int index) {
        m_Quads[dir].setTextureArrayIndex(index);
    }

    void Parallelepiped::updateQuads() {
        float x = m_Dimensions.x;
        float y = m_Dimensions.y;
        float z = m_Dimensions.z;
//        Vertex vertices[VERTICES_PER_CUBE] = {
//
//            // front
//            Vertex(   -0.5f, y - 0.5f,    -0.5f,    x,    y,    0), // top left
//            Vertex(x - 0.5f, y - 0.5f,    -0.5f,    0,    y,    0), // top right
//            Vertex(x - 0.5f,    -0.5f,    -0.5f,    0,    0,    0), // bottom right
//            Vertex(   -0.5f,    -0.5f,    -0.5f,    x,    0,    0), // bottom left
//
//            // right side
//            Vertex(x - 0.5f, y - 0.5f, z - 0.5f,    0,    y,    0),
//            Vertex(x - 0.5f,    -0.5f, z - 0.5f,    0,    0,    0),
//            Vertex(x - 0.5f,    -0.5f,    -0.5f,    z,    0,    0),
//            Vertex(x - 0.5f, y - 0.5f,    -0.5f,    z,    y,    0),
//             
//            // back
//            Vertex(x - 0.5f, y - 0.5f, z - 0.5f,    x,    y,    0),
//            Vertex(   -0.5f, y - 0.5f, z - 0.5f,    0,    y,    0),
//            Vertex(   -0.5f,    -0.5f, z - 0.5f,    0,    0,    0),
//            Vertex(x - 0.5f,    -0.5f, z - 0.5f,    x,    0,    0),
//            
//            // left side
//            Vertex(   -0.5f,    -0.5f, z - 0.5f,    z,    0,    0),
//            Vertex(   -0.5f, y - 0.5f, z - 0.5f,    z,    y,    0),
//            Vertex(   -0.5f, y - 0.5f,    -0.5f,    0,    y,    0),
//            Vertex(   -0.5f,    -0.5f,    -0.5f,    0,    0,    0),
//            
//            // bottom
//            Vertex(x - 0.5f,    -0.5f, z - 0.5f,    x,    z,    0),
//            Vertex(   -0.5f,    -0.5f, z - 0.5f,    0,    z,    0),
//            Vertex(   -0.5f,    -0.5f,    -0.5f,    0,    0,    0),
//            Vertex(x - 0.5f,    -0.5f,    -0.5f,    x,    0,    0),
//            
//            // top
//            Vertex(   -0.5f, y - 0.5f, z - 0.5f,    0,    z,    0),
//            Vertex(x - 0.5f, y - 0.5f, z - 0.5f,    x,    z,    0),
//            Vertex(x - 0.5f, y - 0.5f,    -0.5f,    x,    0,    0),
//            Vertex(   -0.5f, y - 0.5f,    -0.5f,    0,    0,    0),
//        };
        
        float i = m_Quads[FRONT].getTextureArrayIndex();
        m_Quads[FRONT] = {
            Vertex(   -0.5f, y - 0.5f,    -0.5f,    x,    y,    i), // top left
            Vertex(x - 0.5f, y - 0.5f,    -0.5f,    0,    y,    i), // top right
            Vertex(x - 0.5f,    -0.5f,    -0.5f,    0,    0,    i), // bottom right
            Vertex(   -0.5f,    -0.5f,    -0.5f,    x,    0,    i), // bottom left
        };
        
        i = m_Quads[RIGHT].getTextureArrayIndex();
        m_Quads[RIGHT] = {
            Vertex(x - 0.5f, y - 0.5f, z - 0.5f,    0,    y,    i),
            Vertex(x - 0.5f,    -0.5f, z - 0.5f,    0,    0,    i),
            Vertex(x - 0.5f,    -0.5f,    -0.5f,    z,    0,    i),
            Vertex(x - 0.5f, y - 0.5f,    -0.5f,    z,    y,    i),
        };
        
        i = m_Quads[BACK].getTextureArrayIndex();
        m_Quads[BACK] = {
            Vertex(x - 0.5f, y - 0.5f, z - 0.5f,    x,    y,    i),
            Vertex(   -0.5f, y - 0.5f, z - 0.5f,    0,    y,    i),
            Vertex(   -0.5f,    -0.5f, z - 0.5f,    0,    0,    i),
            Vertex(x - 0.5f,    -0.5f, z - 0.5f,    x,    0,    i),
        };

        i = m_Quads[LEFT].getTextureArrayIndex();
        m_Quads[LEFT] = {
            Vertex(   -0.5f,    -0.5f, z - 0.5f,    z,    0,    i),
            Vertex(   -0.5f, y - 0.5f, z - 0.5f,    z,    y,    i),
            Vertex(   -0.5f, y - 0.5f,    -0.5f,    0,    y,    i),
            Vertex(   -0.5f,    -0.5f,    -0.5f,    0,    0,    i),
        };

        i = m_Quads[BOTTOM].getTextureArrayIndex();
        m_Quads[BOTTOM] = {
            Vertex(x - 0.5f,    -0.5f, z - 0.5f,    x,    z,    i),
            Vertex(   -0.5f,    -0.5f, z - 0.5f,    0,    z,    i),
            Vertex(   -0.5f,    -0.5f,    -0.5f,    0,    0,    i),
            Vertex(x - 0.5f,    -0.5f,    -0.5f,    x,    0,    i),
        };
        
        i = m_Quads[TOP].getTextureArrayIndex();
        m_Quads[TOP] = {
            Vertex(   -0.5f, y - 0.5f, z - 0.5f,    0,    z,    i),
            Vertex(x - 0.5f, y - 0.5f, z - 0.5f,    x,    z,    i),
            Vertex(x - 0.5f, y - 0.5f,    -0.5f,    x,    0,    i),
            Vertex(   -0.5f, y - 0.5f,    -0.5f,    0,    0,    i),
        };
    }
}
