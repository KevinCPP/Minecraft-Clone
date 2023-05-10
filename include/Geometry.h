#ifndef GEOMETRY_H
#define GEOMETRY_H

// standard library headers
#include <initializer_list>
#include <type_traits>
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <cstring>
#include <cassert>
#include <memory>
#include <cstdio>
#include <tuple>
#include <array>

// third party library headers
#include <glm/glm.hpp>

namespace Geometry {
    
    // vertex constants
    constexpr size_t FLOATS_PER_VERTEX = 5;

    // quad constants
    constexpr size_t VERTICES_PER_QUAD = 4;
    constexpr size_t FLOATS_PER_QUAD = VERTICES_PER_QUAD * FLOATS_PER_VERTEX;
    constexpr size_t INDICES_PER_QUAD = 6;

    // cube constants
    constexpr size_t QUADS_PER_CUBE = 6;
    constexpr size_t VERTICES_PER_CUBE = QUADS_PER_CUBE * VERTICES_PER_QUAD;
    constexpr size_t FLOATS_PER_CUBE = FLOATS_PER_VERTEX * VERTICES_PER_CUBE;
    constexpr size_t INDICES_PER_CUBE = 36;
}

#endif
