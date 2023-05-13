#include "../include/Chunk.h"

using namespace Blocks;

namespace World {
    
    Chunk::Chunk() { }

    void Chunk::makeStone() {
        for(auto& row : volume) 
            for(auto& col : row)
                for(auto& block : col)
                    block = Block(STONE);
    }

}

