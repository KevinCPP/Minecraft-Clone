#ifndef BLOCK_H
#define BLOCK_H

#include "Cube.h"
#include "BlockData.h"

namespace Blocks {

    enum Material {
        STONE = 0,
        COBBLESTONE,
        DIRT,
        GRASS_BLOCK,
        SAND,
        GRAVEL,
        LOG,
        LEAVES,
        PLANKS,
        BRICKS,
        OBSIDIAN,
        WATER,
        LAVA,
        GLASS,
        AIR
    };

    struct Block {
        Geometry::Cube cube;
        BlockData data;
    };

}

#endif
