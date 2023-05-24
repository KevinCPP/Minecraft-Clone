#include "BiomeFactory.h"

#include <random>

namespace World {
    
    // hard coded biomes
    namespace {
        Biome plains   (20,       35,       60, 70,  "plains");
        Biome desert   (35,       MAX_TEMP, 60, 75,  "desert");
        Biome forest   (10,       25,       60, 75,  "forest");
        Biome mountain (-5,       10,       55, 115, "mountain");
        Biome ocean    (MIN_TEMP, MAX_TEMP, 30, 65,  "ocean");
    }

    Biome BiomeFactory::getBiome(Biomes biome) const {
        if(biome >= NUM_BIOMES) return biomeArray[PLAINS];

        return biomeArray[biome];
    }

    // retrieves a biome from a temperature
    Biomes BiomeFactory::getBiomeFromTemp(float temp) {
        // if it's out of the temp range, just round to the nearest valid temp
        if(temp > MAX_TEMP) temp = MAX_TEMP;
        if(temp < MIN_TEMP) temp = MIN_TEMP;
        
        // store indices for each biome that's in the temperature range
        uint8_t indices[NUM_BIOMES];
        
        // count the number of possible biomes.
        size_t count = 0;

        // iterate through each biome in the array and compare it's
        // min and max temperature with the given temp.
        for(size_t i = 0; i < (uint8_t)NUM_BIOMES; i++) {
            // if it's in the range, add it to the indices and increment count
            if(biomeArray[i].isTempRange(temp)) {
                indices[count] = i;
                ++count;
            }
        }
        
        // if there was not a valid biome, just return plains
        if(count == 0)
            return PLAINS;

        // get a random number between 0 and count-1
        std::uniform_int_distribution<int> distribution(0, count - 1);
        
        // return a random element in the list of possible biomes.
        // uses the seed passed to the constructor, so that it will
        // always return the same biome with the same seed.
        return (Biomes)indices[distribution(generator)];
    }
    
    // set the seed
    void BiomeFactory::setSeed(int seed) {
        generator = std::default_random_engine(seed);
    }

    // constructor. initializes the biomes array and generator seed.
    BiomeFactory::BiomeFactory(int seed) : generator(seed) {
        biomeArray[PLAINS]   = plains;
        biomeArray[DESERT]   = desert;
        biomeArray[FOREST]   = forest;
        biomeArray[MOUNTAIN] = mountain;
        biomeArray[OCEAN]    = ocean;
    }
}
