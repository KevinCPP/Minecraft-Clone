#ifndef GEOMETRY_H
#define GEOMETRY_H

// standard library headers
#include <initializer_list>
#include <type_traits>
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <cassert>
#include <memory>
#include <array>

// third party library headers
#include <glm/glm.hpp>

namespace Geometry {
    
    // vertex constants
    constexpr size_t VERTEX_SIZE = 5;

    // quad constants
    constexpr size_t VERTICES_PER_QUAD = 4;
    constexpr size_t FLOATS_PER_QUAD = VERTICES_PER_QUAD * VERTEX_SIZE;
    
    // cube constants
    constexpr size_t QUADS_PER_CUBE = 6;
    constexpr size_t VERTICES_PER_CUBE = QUADS_PER_CUBE * VERTICES_PER_QUAD;
    constexpr size_t FLOATS_PER_CUBE = VERTEX_SIZE * VERTICES_PER_CUBE;

    /*
    template <size_t N, size_t M>
    std::array<float, N * M>& getFloatArray(std::array<Vertex<N>, M>& vertices) {
        static_assert(std::is_standard_layout_v<Vertex<N>>, "Vertex must have standard layout!");
        static_assert(sizeof(Vertex<N>) == sizeof(float) * N, "Vertex<N> has unexpected size!");
        static_assert(offsetof(Vertex<N>, data) == 0, "data must be at beginning of Vertex!");

        return reinterpret_cast<std::array<float, N * M>&>(vertices);
    }

    template <size_t N>
    std::array<float, N * VERTICES_PER_QUAD * VERTEX_SIZE>& getFloatArray(std::array<Quad, N>& quads) {
        
    }
    */
}

#endif
