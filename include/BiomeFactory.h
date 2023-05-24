#ifndef BIOMEFACTORY_H
#define BIOMEFACTORY_H

#include <vector>
#include <map>

#include "Biome.h"

namespace World {

    constexpr float MIN_TEMP = -50.0f;
    constexpr float MAX_TEMP =  50.0f;

    enum Biomes : uint8_t {
        PLAINS = 0,
        DESERT,
        FOREST,
        MOUNTAIN,
        OCEAN,
        NUM_BIOMES
    };

    class BiomeFactory {
    public:
        // constructor. Default seed 1337
        BiomeFactory(int seed = 1337);

        // get a biome.
        Biome getBiome(float temp);
        
        // set the seed
        void setSeed(int seed);

    private:
        // will store all the biomes
        Biome[NUM_BIOMES] biomeArray;  
        
        // generator to retrieve a biome from overlapping temp ranges
        std::default_random_engine generator;
    };

}

#endif
