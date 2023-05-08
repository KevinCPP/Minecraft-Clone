#ifndef QUAD_H
#define QUAD_H

// project headers
#include "Vertex.h"
#include "TextureAtlas.h"

struct Quad {
    // will store the size of the vertices so we can easily change it later
    static constexpr size_t VERTEX_SIZE = 5;

    // a quad is just 4 vertices
    Vertex<VERTEX_SIZE> vertices[4];
    
    // constructors
    Quad() = default;
    Quad(std::initializer_list<Vertex<VERTEX_SIZE>> list);

    // A texture atlas has X columns and Y rows of textures. This function will accept x and y, which will be
    // the bottom left corner of the texture you want. Then, rather than simply doing x+1 and y+1 to find
    // the top right corner, we will use (x + width) and (y + height) in case you have a texture that takes up
    // two slots in the texture atlas. Useful for any blocks (paintings?) that are multiple blocks wide/tall.
    void setTextureCoordsFromAtlas(TextureAtlas* a, uint32_t x, uint32_t y, uint32_t width, uint32_t height);

    // returns the indices for an index buffer
    std::array<unsigned int, 6> getIndices();
};

#endif
