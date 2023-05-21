#include "../include/Cube.h"

namespace Geometry {
    Cube::Cube() {
        setPosition(0, 0, 0);
        setDimensions(1.0f, 1.0f, 1.0f);
    }

    Cube::Cube(float sizeX, float sizeY, float sizeZ) {
        setPosition(0, 0, 0);
        setDimensions(sizeX, sizeY, sizeZ);
    }

    Cube::Cube(const glm::vec3& dimensions) {
        setPosition(0, 0, 0);
        setDimensions(dimensions);
    }

    glm::vec3 Cube::getDimensions() {
        return m_Dimensions;
    }

    void Cube::setDimensions(float sizeX, float sizeY, float sizeZ) {
        m_Dimensions = glm::vec3(sizeX, sizeY, sizeZ);
        updateQuads();
    }

    void Cube::setDimensions(const glm::vec3& dimensions) {
        m_Dimensions = dimensions;
        updateQuads();
    }

    void Cube::setPosition(float x, float y, float z) {
        setPosition(glm::vec3(x, y, z));
    }

    void Cube::setPosition(const glm::vec3& position) {
        m_Center = position;
        updateQuads();
    }

    glm::vec3 Cube::getPosition() {
        return m_Center;
    }

    Quad Cube::copyQuad(Direction dir) const {
        std::string msg = "Attempting to copy a quad with an invalid direction! returning default (front)"; 
        if(Utility::warn(dir >= QUADS_PER_CUBE, msg))
            return m_Quads[FRONT];
        
        return m_Quads[dir];
    }

    void Cube::setTextureArrayIndex(Direction dir, unsigned int index) {
        m_Quads[dir].setTextureArrayIndex(index);
    }

    void Cube::setTopBottomTextureArrayIndex(unsigned int index) {
        setTextureArrayIndex(TOP, index);
        setTextureArrayIndex(BOTTOM, index);
    }

    void Cube::setSidesTextureArrayIndex(unsigned int index) {
        setTextureArrayIndex(LEFT,  index);
        setTextureArrayIndex(BACK,  index);
        setTextureArrayIndex(FRONT, index);
        setTextureArrayIndex(RIGHT, index);
    }

    void Cube::setAllTextureArrayIndex(unsigned int index) {
        setTopBottomTextureArrayIndex(index);
        setSidesTextureArrayIndex(index);
    }

    void Cube::updateQuads() {
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

        for(auto& q : m_Quads)
            q.addOffset(m_Center);
    }
}




