#include "../include/Block.h"

namespace Blocks {
    Block::Block(Material material, Direction direction) {
        mat = material;
        dir = direction;
    }

    Block::Block(const Block& other) {
        memcpy(this, &other, sizeof(Block));
    }

    Block& Block::operator=(const Block& other) {
        if(this != &other)
            memcpy(this, &other, sizeof(Block));
        
        return *this;
    }
}
