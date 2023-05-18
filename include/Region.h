#ifndef REGION_H
#define REGION_H

#include <glm/glm.hpp>

#include "Quad.h"
#include "Cube.h"
#include "World.h"
#include "Chunk.h"
#include "Settings.h"
#include "CubeFactory.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace World {
    class Region {
    private:
        const size_t rd;
        Chunk*** loadedChunks;
         
    public:
        
        Region();
        ~Region();
         
        // (0, 0, 0) will be the origin
//        Chunk* getChunk(int64_t cx, int64_t cy, int64_t cz);
//        Block* getBlock(int64_t x, int64_t y, int64_t z);
//
//        bool setChunk(int64_t cs, int64_t cy, int64_t cz, const Chunk& c);
//        bool setBlock(int64_t x, int64_t y, int64_t z, const Block& b);
        
        
    };
}

#endif
