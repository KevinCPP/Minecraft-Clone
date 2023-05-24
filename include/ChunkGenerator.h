#ifndef CHUNKGENERATOR_H
#define CHUNKGENERATOR_H

#include <functional>

#include "BiomeCharacteristics.h"
#include "BiomeFactory.h"
#include "Geometry.h"
#include "Biome.h"
#include "Cube.h"
#include "Quad.h"
#include "Chunk.h"

namespace World {
    class ChunkGenerator {
    private:
        BiomeFactory biomeFactory;

        // the noise at X, Y, will be the temperature of a chunk. Used to determine biome
        FastNoiseLite biomeGenerator;
        
        // general noise generator to be used for terrain.
        FastNoiseLite noiseGenerator;
        
        std::shared_ptr<Chunk> generate_base(const Geometry::Location& ck,
            std::function<Blocks::Block(const FastNoiseLite&, const BiomeFactory&, int64_t, int64_t, int64_t)> characteristic);

    public:
        ChunkGenerator(int seed = 1337);
        //void generateChunk(Chunk* chunk, const Geometry::Location& ck);
         
        std::shared_ptr<Chunk> generateChunk(const Geometry::Location& ck);
    };
}

#endif
