#include "../include/Vertex.h"
#include "../include/VertexBufferLayout.h"

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

    void Vertex::setTextureArrayCoords(float u, float v, float z) {
        assert(FLOATS_PER_VERTEX >= 6 && "Vertex::setTextureArrayCoords, N < 6");
        data[3] = u; data[4] = v; data[5] = z;
    }

    void Vertex::setTextureArrayCoords(const glm::vec3& uvz) {
        setTextureArrayCoords(uvz.x, uvz.y, uvz.z);
    }

    void Vertex::setTextureArrayIndex(float index) {
        setTextureArrayCoords(data[3], data[4], index);
    }

    void Vertex::setNormal(float x, float y, float z) {
        assert(FLOATS_PER_VERTEX >= 9 && "Vertex::setNormal, N < 9");
        data[6] = x; data[7] = y; data[8] = z;
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

    
    float Vertex::getTextureArrayIndex() {
        assert(FLOATS_PER_VERTEX >= 6 && "Vertex::getTextureArrayCoords, FLOATS_PER_VERTEX < 6");
        return data[5];
    }

    glm::vec3 Vertex::getPosition() const {
        assert(FLOATS_PER_VERTEX >= 3 && "Vertex::getPosition, FLOATS_PER_VERTEX < 3");
        return glm::vec3(data[0], data[1], data[2]);
    }

    glm::vec2 Vertex::getTextureCoords() const {
        assert(FLOATS_PER_VERTEX >= 5 && "Vertex::getTextureCoords, FLOATS_PER_VERTEX < 5");
        return glm::vec2(data[3], data[4]);
    }

    glm::vec3 Vertex::getTextureArrayCoords() const {
        assert(FLOATS_PER_VERTEX >= 6 && "Vertex::getTextureArrayCoords, FLOATS_PER_VERTEX < 6");
        return glm::vec3(data[3], data[4], data[5]);
    }

    glm::vec3 Vertex::getNormal() const { 
        assert(FLOATS_PER_VERTEX >= 9 && "vertex::getNormal, FLOATS_PER_VERTEX < 9"); 
        return glm::vec3(data[6], data[7], data[8]);
    }

    bool Vertex::operator==(const Vertex& other) const {
        for(size_t i = 0; i < FLOATS_PER_VERTEX; i++) {
            if(data[i] != other.data[i]) return false;
        }

        return true;
    }

    bool Vertex::operator!=(const Vertex& other) const {
        for(size_t i = 0; i < FLOATS_PER_VERTEX; i++) {
            if(data[i] == other.data[i]) return false;
        }

        return true;
    }

    VertexBufferLayout makeVertexLayout() {
        VertexBufferLayout layout;
        if constexpr (FLOATS_PER_VERTEX == 3) {
            layout.push_float(3);
        } else if constexpr (FLOATS_PER_VERTEX == 5) {
            layout.push_float(3);
            layout.push_float(2);
        } else if constexpr (FLOATS_PER_VERTEX == 6) {
            layout.push_float(3);
            layout.push_float(3);
        } else if constexpr (FLOATS_PER_VERTEX == 9) {
            layout.push_float(3);
            layout.push_float(3);
            layout.push_float(3);
        }
        return layout;
    }


}
