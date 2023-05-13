#ifndef CHUNK_H
#define CHUNK_H

#include "Cube.h"
#include "World.h"
#include "Block.h"
#include "CubeFactory.h"

#include <vector>

namespace World {

    struct Chunk {
        Blocks::Block volume[CHUNK_SIZE_X][CHUNK_SIZE_Y][CHUNK_SIZE_Z];

        Chunk();
        Chunk(size_t x, size_t y, size_t z);

        void makeStone();

        std::tuple<std::vector<float>, std::vector<unsigned int>> getFloatsAndIndices();
    };

}

#endif
