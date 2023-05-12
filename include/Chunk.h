#ifndef CHUNK_H
#define CHUNK_H

#include "Cube.h"
#include "Block.h"
#include "CubeFactory.h"

#include <vector>

struct Chunk {

    
    static const size_t sizex = 64, sizey = 128, sizez = 64;

    Blocks::Block*** volume;

    Chunk();
    Chunk(size_t x, size_t y, size_t z);

    void generateTerrain();

    std::tuple<std::vector<float>, std::vector<unsigned int>> getFloatsAndIndices();
};

#endif
