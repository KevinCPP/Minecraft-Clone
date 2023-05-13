#ifndef BLOCK_H
#define BLOCK_H

#include "Cube.h"

namespace Blocks {  

    enum Material : uint8_t {
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

    enum Direction : uint8_t {
        NORTH = 0,
        SOUTH,
        EAST,
        WEST
    };

    constexpr size_t NUM_MATERIALS = AIR;

    struct Block {
        Material mat;
        Direction dir;
        
        Block(Material material = AIR, Direction direction = NORTH);
        Block(const Block& other);

        Block& operator=(const Block& other);
    };
}

#endif
