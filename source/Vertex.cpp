#include "../include/Vertex.h"

namespace Geometry {
    
    // setters and getters...
    void Vertex::setPosition(float x, float y, float z) {
        assert(FLOATS_PER_VERTEX >= 3 && "Vertex::setPosition, N < 3");
        data[0] = x; data[1] = y; data[2] = z;
    }

    void Vertex::setTextureCoords(float u, float v) {
        assert(FLOATS_PER_VERTEX >= 5 && "Vertex::setTextureCoords, N < 5");
        data[3] = u; data[4] = v;
    }

    void Vertex::setNormal(float x, float y, float z) {
        assert(FLOATS_PER_VERTEX >= 8 && "Vertex::setNormal, N < 8");
        data[5] = x; data[6] = y; data[7] = z;
    }

    void Vertex::setPosition(const glm::vec3& pos) {
        setPosition(pos.x, pos.y, pos.z);
    }

    void Vertex::setTextureCoords(const glm::vec2& uv) {
        setTextureCoords(uv.x, uv.y);
    }

    void Vertex::setNormal(const glm::vec3& norm) {
        setNormal(norm.x, norm.y, norm.z);
    }

    glm::vec3 Vertex::getPosition() const {
        assert(FLOATS_PER_VERTEX >= 3 && "Vertex::getPosition, FLOATS_PER_VERTEX < 3");
        return glm::vec3(data[0], data[1], data[2]);
    }

    glm::vec2 Vertex::getTextureCoords() const {
        assert(FLOATS_PER_VERTEX >= 5 && "Vertex::getTextureCoords, FLOATS_PER_VERTEX < 5");
        return glm::vec2(data[3], data[4]);
    }

    glm::vec3 Vertex::getNormal() const { 
        assert(FLOATS_PER_VERTEX >= 8 && "vertex::getNormal, FLOATS_PER_VERTEX < 8"); 
        return glm::vec3(data[5], data[6], data[7]);
    }
}
