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
        //void generateChunk(Chunk* chunk, const Geometry::Location& ck);
        
        std::shared_ptr<Chunk> generateChunk(const Geometry::Location& ck);
    };
}










#endif
