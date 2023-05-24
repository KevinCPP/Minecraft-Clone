#include "../include/Biome.h"

namespace World {

    Biome::Biome() {
        minHeight = 48;
        maxHeight = 96;
    }
    
    bool Biome::isTempRange(float temp) const {
        return minTemp <= temp && temp <= maxTemp;
    }
    
    int Biome::getHeight(float noise) const {
        int heightDiff = maxHeight - minHeight;

        // outputs are bounded from -1.0 to 1.0, this will make it
        // bounded from 0 to 1.0 which is what we need
        noise = (noise + 1.0f) / 2.0f;
        
        // returns a height value between minHeight and maxHeight based on the noise
        return minHeight + (noise * heightDiff);
    }
}
