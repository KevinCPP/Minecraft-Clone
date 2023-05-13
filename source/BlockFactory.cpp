#include "../include/BlockFactory.h"

namespace Blocks {
    
    BlockFactory::BlockFactory() {
        for(uint32_t m = 0; m < AIR; m++) {
            blocks[m] = Block(static_cast<Material>(m));
        }
    }
    
    Block* BlockFactory::getBlock(const Material& mat) {
        if(mat >= AIR) return NULL;

        return &blocks[mat];
    }

    std::optional<Block> BlockFactory::makeBlock(const Material& mat) {
        if(mat >= AIR) return std::nullopt;

        std::optional<Block> tempBlock;
        tempBlock = Block(mat);
        return tempBlock;
    }

}
