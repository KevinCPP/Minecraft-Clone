#ifndef VERTEX_H
#define VERTEX_H

// project headers
#include "Geometry.h"
#include "VertexBufferLayout.h"

namespace Geometry {
    struct Vertex {
        // stores the actual vertex data
        float data[FLOATS_PER_VERTEX];

        // default constructor
        Vertex() = default;

        // initializer list constructor. allows for initializer list syntax
        Vertex(std::initializer_list<float> list) {
            auto it = list.begin();
            for(size_t i = 0; i < FLOATS_PER_VERTEX && it != list.end(); ++i, ++it) {
                data[i] = *it;
            }
        }
       
        // vertex constructor that accepts floats
        template <typename... Args>
        Vertex(Args... args) : data{static_cast<float>(args)...} {
            static_assert(sizeof...(Args) == FLOATS_PER_VERTEX, "Constructor requires exactly N arguments!");
        }

        // setters (floats)
        void setPosition(float x, float y, float z);
        void setTextureCoords(float u, float v);
        void setTextureArrayCoords(float u, float v, float index);
        void setNormal(float x, float y, float z);
        void setTextureArrayIndex(float index);

        // setters (glm vectors)
        void setPosition(const glm::vec3& pos);
        void setTextureCoords(const glm::vec2& uv);
        void setTextureArrayCoords(const glm::vec3& uvz);
        void setNormal(const glm::vec3& norm);
        

        // getters (floats)
        float getTextureArrayIndex();
        
        // operator overloads
        bool operator==(const Vertex& other) const;
        bool operator!=(const Vertex& other) const;

        // getters (glm vectors)
        glm::vec3 getPosition() const;
        glm::vec2 getTextureCoords() const;
        glm::vec3 getTextureArrayCoords() const;
        glm::vec3 getNormal() const;
    }; 
    
    VertexBufferLayout makeVertexLayout(); 
}
#endif
