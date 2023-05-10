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
    constexpr size_t FLOATS_PER_VERTEX = 5;

    // quad constants
    constexpr size_t VERTICES_PER_QUAD = 4;
    constexpr size_t FLOATS_PER_QUAD = VERTICES_PER_QUAD * FLOATS_PER_VERTEX;
    
    // cube constants
    constexpr size_t QUADS_PER_CUBE = 6;
    constexpr size_t VERTICES_PER_CUBE = QUADS_PER_CUBE * VERTICES_PER_QUAD;
    constexpr size_t FLOATS_PER_CUBE = FLOATS_PER_VERTEX * VERTICES_PER_CUBE;

    // forward declarations for upcoming functions
    struct Vertex;
    struct Quad;
    struct Cube;

    // converts an array of vertices into an array of floats
    template <size_t N>
    std::array<float, FLOATS_PER_VERTEX * N>& getFloatArray(std::array<Vertex, N>& vertices);

    // converts an array of quads into an array of floats
    template <size_t N>
    std::array<float, FLOATS_PER_QUAD * N>& getFloatArray(std::array<Quad, N>& quads);

    // converts an array of cubes into an array of floats
    template <size_t N>
    std::array<float, FLOATS_PER_CUBE * N>& getFloatArray(std::array<Cube, N>& cubes);
}

#endif
