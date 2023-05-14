#ifndef BLOCK_H
#define BLOCK_H

#include <optional>

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

    constexpr uint8_t TRANSPARENT_MATERIALS_ARRAY[] = {
        AIR,
        GLASS,
        WATER
    };

    constexpr size_t NUM_MATERIALS = AIR;

    bool isTransparent(const Material& mat);

    struct Block {
        Material mat;
        Direction dir;
        
        Block(Material material = AIR, Direction direction = NORTH);
        Block(const Block& other);

        std::optional<Geometry::Cube> getCube(float x, float y, float z);

        Block& operator=(const Block& other);
    };
}

#endif
