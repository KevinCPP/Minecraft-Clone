#include "../include/Biome.h"

namespace World {

    Biome::Biome() {
        minHeight = 48;
        maxHeight = 96;
    }
    
    bool Biome::isTempRange(float temp) {
        return minTemp <= temp && temp <= maxTemp;
    }
    
    void Biome::setNoiseType(FastNoiseLite::NoiseType noiseType) {
        noiseGenerator.SetNoiseType(noiseType);
    }

    void Biome::setFrequency(float frequency) {
        noiseGenerator.SetFrequency(frequency);
    }

    void Biome::setSeed(int seed) {
        noiseGenerator.SetSeed(seed);
    }

    float Biome::getNoise(float x, float y) {
        return noiseGenerator.GetNoise(x, y);
    }

    int Biome::getNoiseInterpolate(float x, float y) {
        int heightDiff = maxHeight - minHeight;
        float noise = getNoise(x, y);

        // outputs are bounded from -1.0 to 1.0, this will make it
        // bounded from 0 to 1.0 which is what we need
        noise = (noise + 1.0f) / 2.0f;
        
        // returns a height value between minHeight and maxHeight based on the noise
        return minHeight + (noise * heightDiff);
    }
}
