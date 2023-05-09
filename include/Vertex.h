#ifndef VERTEX_H
#define VERTEX_H

// project headers
#include "Geometry.h"

namespace Geometry {
    struct Vertex {
        // stores the actual vertex data
        std::array<float, VERTEX_SIZE> data;

        // default constructor
        Vertex() = default;

        // initializer list constructor. allows for initializer list syntax
        Vertex(std::initializer_list<float> list) {
            auto it = list.begin();
            for(size_t i = 0; i < VERTEX_SIZE && it != list.end(); ++i, ++it) {
                data[i] = *it;
            }
        }
       
        // vertex constructor that accepts floats
        template <typename... Args>
        Vertex(Args... args) : data{static_cast<float>(args)...} {
            static_assert(sizeof...(Args) == VERTEX_SIZE, "Constructor requires exactly N arguments!");
        }

        // setters (floats)
        void setPosition(float x, float y, float z);
        void setTextureCoords(float u, float v);
        void setNormal(float x, float y, float z);

        // setters (glm vectors)
        void setPosition(const glm::vec3& pos);
        void setTextureCoords(const glm::vec2& uv);
        void setNormal(const glm::vec3& norm);

        // getters (glm vectors)
        glm::vec3 getPosition() const;
        glm::vec2 getTextureCoords() const;
        glm::vec3 getNormal() const;
    };
}
#endif
