#include "../include/BlockAttributeFactory.h"

namespace Blocks {
    BlockAttributeFactory::BlockAttributeFactory() {
        // set all item IDs to the correct material
        attributes[STONE]       .ItemID = STONE;
        attributes[COBBLESTONE] .ItemID = COBBLESTONE;
        attributes[DIRT]        .ItemID = DIRT;
        attributes[GRASS_BLOCK] .ItemID = GRASS_BLOCK;
        attributes[SAND]        .ItemID = SAND;
        attributes[GRAVEL]      .ItemID = GRAVEL;
        attributes[LOG]         .ItemID = LOG;
        attributes[LEAVES]      .ItemID = LEAVES;
        attributes[PLANKS]      .ItemID = PLANKS;
        attributes[BRICKS]      .ItemID = BRICKS;
        attributes[OBSIDIAN]    .ItemID = OBSIDIAN;
        attributes[WATER]       .ItemID = WATER;
        attributes[GLASS]       .ItemID = GLASS;
    
        // set additional parameters for blocks with transparency
        attributes[LEAVES]      .isTransparent = true;
        attributes[GLASS]       .isTransparent = true;

        // set additional parameters for liquids
        attributes[WATER]       .state = State::LIQUID;
    }

    BlockAttributes* BlockAttributeFactory::getAttributes(const Material& mat) {
        if(mat >= NUM_MATERIALS) return nullptr;

        return &attributes[mat];
    }
}
