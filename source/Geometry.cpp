#include "Geometry.h"
#include "Vertex.h"
#include "Quad.h"
#include "Cube.h"


namespace Geometry {
    // converts an array of vertices into an array of floats
    template <size_t N>
    std::array<float, FLOATS_PER_VERTEX * N>& getFloatArray(std::array<Vertex, N>& vertices) {
        static_assert(std::is_standard_layout_v<Vertex>, "Vertex struct doesn't have standard layout!");
        static_assert(sizeof(Vertex) == sizeof(float) * FLOATS_PER_VERTEX, "Vertex size doesn't equal sizeof(float) * FLOATS_PER_VERTEX!");
        static_assert(offsetof(Vertex, data) == 0, "data array is not at offset 0 in Vertex struct!");

        // yeah, if you don't like it, fuck you
        return reinterpret_cast<std::array<float, FLOATS_PER_VERTEX * N>&>(vertices);
    }

    // converts an array of quads into an array of floats
    template <size_t N>
    std::array<float, FLOATS_PER_QUAD * N>& getFloatArray(std::array<Quad, N>& quads) {
        static_assert(std::is_standard_layout_v<Quad>, "Quad struct doesn't have standard layout!");
        static_assert(sizeof(Quad) == sizeof(float) * FLOATS_PER_QUAD, "Quad size doesn't equal sizeof(float) * FLOATS_PER_QUAD!");
        static_assert(offsetof(Quad, vertices) == 0, "vertices array is not at offset 0 in Quad struct!");

        return reinterpret_cast<std::array<float, FLOATS_PER_QUAD * N>&>(quads);
    }

    // converts an array of cubes into an array of floats
    template <size_t N>
    std::array<float, FLOATS_PER_CUBE * N>& getFloatArray(std::array<Cube, N>& cubes) {
        static_assert(std::is_standard_layout_v<Cube>, "Cube struct doesn't have standard layout!");
        static_assert(sizeof(Cube) == sizeof(float) * FLOATS_PER_CUBE, "Cube size doesn't equal sizeof(float) * FLOATS_PER_CUBE!");
        static_assert(offsetof(Cube, quads) == 0, "quads array is not at offset 0 in Cube struct!");

        return reinterpret_cast<std::array<float, FLOATS_PER_CUBE * N>&>(cubes);
    }

}
