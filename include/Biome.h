#ifndef BIOME_H
#define BIOME_H

#include <map>
#include <string>
#include <vector>

#include "../vendor/fastnoiselite.h"

namespace World {

    struct Biome {
        float minTemp, maxTemp;
        int minHeight, maxHeight;
        
        std::string name;

        Biome();
        Biome(float mintemp, float maxtemp, int minheight, int maxheight, const std::string& n)
            : minTemp(mintemp), maxTemp(maxtemp), minHeight(minheight), maxHeight(maxheight), name(n) { }

        // returns true if the temp is between minTemp and maxTemp
        bool isTempRange(float temp) const;
         
        // gets the noise, and interpolates it to a value between minHeight and maxHeight
        int getHeight(float noise) const;
    };
    
    
    
}

#endif
