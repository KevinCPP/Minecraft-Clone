#include "../include/ChunkGenerator.h"
#include "../vendor/fastnoiselite.h"

namespace World {
    ChunkGenerator::ChunkGenerator(int seed) : biomeFactory(seed) {
        biomeGenerator.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        noiseGenerator.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
       
        // we want the noise generator and biome generator
        // to be different even if they use the same algorithm,
        // but still reliant on the same seed. So, just shift em over arbitrarily
        biomeGenerator.SetSeed(seed);
        noiseGenerator.SetSeed(seed << 1);
    }

    std::shared_ptr<Chunk> ChunkGenerator::generate_base(const Geometry::Location& ck, 
            std::function<Blocks::Block(const FastNoiseLite&, const BiomeFactory&, int64_t, int64_t, int64_t)> characteristic) 
    {
        int64_t chunkOffsetX = ck.x * CHUNK_SIZE;
        int64_t chunkOffsetY = ck.y * CHUNK_SIZE;
        int64_t chunkOffsetZ = ck.z * CHUNK_SIZE;
        
        std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
        
        // iterate through each block of the chunk, use the biome characteristic
        // function to set the block at x, y, z:
        int64_t worldX, worldY, worldZ;
        for(size_t x = 0; x < CHUNK_SIZE; x++)
        for(size_t y = 0; y < CHUNK_SIZE; y++)
        for(size_t z = 0; z < CHUNK_SIZE; z++) {
            worldX = chunkOffsetX + x;
            worldY = chunkOffsetY + y;
            worldZ = chunkOffsetZ + z;
            chunk->setBlockRaw(x, y, z, characteristic(noiseGenerator, biomeFactory, worldX, worldY, worldZ));
        }
        chunk->findVisible();
        return chunk;
    }

    std::shared_ptr<Chunk> ChunkGenerator::generateChunk(const Geometry::Location& ck) {
        //std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
        //float temp = biomeGenerator.GetNoise((float)ck.x, (float)ck.z);
        //temp *= 50;
        //Biomes biome = biomeFactory.getBiomeFromTemp(temp);
        
        switch(PLAINS) {
            case PLAINS:
                return generate_base(ck, plains_characteristic);
            case DESERT:
                return generate_base(ck, desert_characteristic);
            case FOREST:
                return generate_base(ck, forest_characteristic);
            case MOUNTAIN:
                return generate_base(ck, mountain_characteristic);
            case OCEAN:
                return generate_base(ck, ocean_characteristic);
            default:
                return generate_base(ck, plains_characteristic);
        }
    }










}
