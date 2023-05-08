#ifndef VERTEX_H
#define VERTEX_H

// standard library headers
#include <initializer_list>
#include <cassert>
#include <array>

// third party library headers
#include <glm/glm.hpp>

// A vertex of size N. Can be converted directly into
// an array of floats in O(1) since there is no additional
// member variables that creates padding
template <size_t N>
struct Vertex {
    // stores the actual vertex data
    std::array<float, N> data;

    // default constructor
    Vertex() = default;

    // initializer list constructor. allows for initializer list syntax
    Vertex(std::initializer_list<float> list) {
        auto it = list.begin();
        for(size_t i = 0; i < N && it != list.end(); ++i, ++it) {
            data[i] = *it;
        }
    }
   
    template <typename... Args>
    Vertex(Args... args) : data{static_cast<float>(args)...} {
        static_assert(sizeof...(Args) == N, "Constructor requires exactly N arguments!");
    }

    // setters and getters...
    void setPos(float x, float y, float z) {
        static_assert(N >= 3, "Vertex::setPos, N < 3");
        data[0] = x; data[1] = y; data[2] = z;
    }

    void setTexCoords(float u, float v) {
        static_assert(N >= 5, "Vertex::setTexCoords, N < 5");
        data[3] = u; data[4] = v;
    }

    void setNormal(float x, float y, float z) {
        static_assert(N >= 8, "Vertex::setNormal, N < 8");
        data[5] = x; data[6] = y; data[7] = z;
    }

    void setPos(const glm::vec3& pos) {
        setPos(pos.x, pos.y, pos.z);
    }

    void setTexCoords(const glm::vec2& uv) {
        setTexCoords(uv.x, uv.y);
    }

    void setNormal(const glm::vec3& norm) {
        setNormal(norm.x, norm.y, norm.z);
    }

    glm::vec3 getPos() {
        return glm::vec3(data[0], data[1], data[2]);
    }

    glm::vec2 getTexCoords() {
        return glm::vec2(data[3], data[4]);
    }

    glm::vec3 getNormal() {
        return glm::vec3(data[5], data[6], data[7]);
    }
};

#endif
