#ifndef CHUNKGENERATOR_H
#define CHUNKGENERATOR_H

#include "Geometry.h"
#include "Biome.h"
#include "Cube.h"
#include "Quad.h"
#include "Chunk.h"

namespace World {
    class ChunkGenerator {
    private:
        // the noise at X, Y, will be the temperature of a chunk. Used to determine biome
        FastNoiseLite biomeGenerator;
        
        // general noise generator to be used for terrain.
        FastNoiseLite noiseGenerator;
    public:
        ChunkGenerator();
        //void generateChunk(Chunk* chunk, const Geometry::Location& ck);
         
        std::shared_ptr<Chunk> generateChunk(const Geometry::Location& ck);
    };
}

#endif
