#include "BiomeCharacteristics.h"

namespace World {
    Blocks::Block plains_characteristic(const FastNoiseLite& noiseGen, const BiomeFactory& biomeFactory, int64_t worldX, int64_t worldY, int64_t worldZ) {
        float noise = noiseGen.GetNoise((float)worldX, (float)worldZ);
        int height = biomeFactory.getBiome(Biomes::PLAINS).getHeight(noise);

        if(height - worldY < 0)
            return Blocks::Block(Blocks::AIR);
        
        if(height - worldY < 1)
            return Blocks::Block(Blocks::GRASS_BLOCK);

        if(height - worldY < 4)
            return Blocks::Block(Blocks::DIRT);

        return Blocks::Block(Blocks::STONE);
    }

    Blocks::Block desert_characteristic(const FastNoiseLite& noiseGen, const BiomeFactory& biomeFactory, int64_t worldX, int64_t worldY, int64_t worldZ) {
        float noise = noiseGen.GetNoise((float)worldX, (float)worldZ);
        int height = biomeFactory.getBiome(Biomes::DESERT).getHeight(noise);
        
        if(height - worldY < 0)
            return Blocks::Block(Blocks::AIR);
        
        if(height - worldY < 1)
            return Blocks::Block(Blocks::GRASS_BLOCK);

        if(height - worldY < 4)
            return Blocks::Block(Blocks::DIRT);

        return Blocks::Block(Blocks::STONE);
    }

    Blocks::Block forest_characteristic(const FastNoiseLite& noiseGen, const BiomeFactory& biomeFactory, int64_t worldX, int64_t worldY, int64_t worldZ) {
        float noise = noiseGen.GetNoise((float)worldX, (float)worldZ);
        int height = biomeFactory.getBiome(Biomes::FOREST).getHeight(noise);

        if(height - worldY < 0)
            return Blocks::Block(Blocks::AIR);
        
        if(height - worldY < 1)
            return Blocks::Block(Blocks::GRASS_BLOCK);

        if(height - worldY < 4)
            return Blocks::Block(Blocks::DIRT);

        return Blocks::Block(Blocks::STONE);
    }

    Blocks::Block mountain_characteristic(const FastNoiseLite& noiseGen, const BiomeFactory& biomeFactory, int64_t worldX, int64_t worldY, int64_t worldZ) {
        float noise = noiseGen.GetNoise((float)worldX, (float)worldZ);
        int height = biomeFactory.getBiome(Biomes::MOUNTAIN).getHeight(noise);

        if(height - worldY < 0)
            return Blocks::Block(Blocks::AIR);
        
        if(height - worldY < 1)
            return Blocks::Block(Blocks::GRASS_BLOCK);

        if(height - worldY < 4)
            return Blocks::Block(Blocks::DIRT);

        return Blocks::Block(Blocks::STONE);
    }

    Blocks::Block ocean_characteristic(const FastNoiseLite& noiseGen, const BiomeFactory& biomeFactory, int64_t worldX, int64_t worldY, int64_t worldZ) {
        float noise = noiseGen.GetNoise((float)worldX, (float)worldZ);
        int height = biomeFactory.getBiome(Biomes::OCEAN).getHeight(noise);

        if(height - worldY < 0)
            return Blocks::Block(Blocks::AIR);
        
        if(height - worldY < 1)
            return Blocks::Block(Blocks::GRASS_BLOCK);

        if(height - worldY < 4)
            return Blocks::Block(Blocks::DIRT);

        return Blocks::Block(Blocks::STONE);
    }
}
