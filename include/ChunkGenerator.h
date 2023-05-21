#ifndef CHUNKGENERATOR_H
#define CHUNKGENERATOR_H

#include "Geometry.h"
#include "Biome.h"
#include "Cube.h"
#include "Quad.h"
#include "Chunk.h"

namespace World {
    class ChunkGenerator {
    public:
        ChunkGenerator();

        Biome b;
        void generateChunk(Chunk* chunk, int64_t chunkX, int64_t chunkY, int64_t chunkZ);
    };
}










#endif
