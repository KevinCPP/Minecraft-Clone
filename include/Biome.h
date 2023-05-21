#ifndef BIOME_H
#define BIOME_H

#include "../vendor/fastnoiselite.h"

namespace World {

    struct Biome {
        float minTemp, maxTemp;
        int minHeight, maxHeight;
        FastNoiseLite noiseGenerator;

        Biome();

        // returns true if the temp is between minTemp and maxTemp
        bool isTempRange(float temp);

        // sets the noise generation algorithm
        void setNoiseType(FastNoiseLite::NoiseType noiseType);

        // sets the frequency, e.g. how coarse the patterns are
        void setFrequency(float frequency);

        // sets the seed
        void setSeed(int seed);
        
        // gets noise at specified coordinates
        float getNoise(float x, float y);
        
        // gets the noise, and interpolates it to a value between minHeight and maxHeight
        int getNoiseInterpolate(float x, float y);
    };

}

#endif
