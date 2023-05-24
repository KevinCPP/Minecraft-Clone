#ifndef BIOMECHARACTERISTICS_H
#define BIOMECHARACTERISTICS_H

#include <functional>

#include "../vendor/fastnoiselite.h"

#include "Block.h"
#include "Biome.h"
#include "BiomeFactory.h"

namespace World {
    Blocks::Block plains_characteristic   (const FastNoiseLite& noiseGen, const BiomeFactory& biomeFactory, int64_t worldX, int64_t worldY, int64_t worldZ);
    Blocks::Block desert_characteristic   (const FastNoiseLite& noiseGen, const BiomeFactory& biomeFactory, int64_t worldX, int64_t worldY, int64_t worldZ);
    Blocks::Block forest_characteristic   (const FastNoiseLite& noiseGen, const BiomeFactory& biomeFactory, int64_t worldX, int64_t worldY, int64_t worldZ);
    Blocks::Block mountain_characteristic (const FastNoiseLite& noiseGen, const BiomeFactory& biomeFactory, int64_t worldX, int64_t worldY, int64_t worldZ);
    Blocks::Block ocean_characteristic    (const FastNoiseLite& noiseGen, const BiomeFactory& biomeFactory, int64_t worldX, int64_t worldY, int64_t worldZ);
}

#endif
