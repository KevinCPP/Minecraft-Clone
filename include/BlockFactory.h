#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H

#include <optional>

#include "Block.h"

namespace Blocks {
    
    class BlockFactory {
    public:
        
        static BlockFactory& getInstance() {
            static BlockFactory instance;
            return instance;
        }

        Block* getBlock(const Material& mat);
        std::optional<Block> makeBlock(const Material& mat);
        

    private:
        
        BlockFactory();
        ~BlockFactory() = default;
        BlockFactory(const Material&) = delete;
        BlockFactory& operator=(const Material&) = delete;
        
        Block blocks[NUM_MATERIALS];
    };

}

#endif
