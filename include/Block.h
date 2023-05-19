#ifndef BLOCK_H
#define BLOCK_H

#include <optional>

#include "Cube.h"

namespace Blocks {  

    // list of every material in the game
    enum Material : uint8_t {
        STONE = 0,
        DEV,
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

    // list of all transparent materials. Important for face culling. 
    constexpr uint8_t TRANSPARENT_MATERIALS_ARRAY[] = {
        AIR,
        GLASS,
        WATER
    };

    // AIR is the last element in the Material enum, so
    // we can use that to get the size of the enum. Additionally,
    // we never really need to iterate over AIR since "AIR" is not
    // truly a block
    constexpr size_t NUM_MATERIALS = AIR;

    // test if a material is transparent
    bool isTransparent(const Material& mat);

    // stores necessary data for a block
    struct Block {
        Material mat;
        Geometry::Direction dir;

        Block(Material material = AIR, Geometry::Direction dir = Geometry::FRONT);
        Block(const Block& other);

        std::optional<Geometry::Cube> getCube(float x, float y, float z);

        Block& operator=(const Block& other);
    };
}

#endif
