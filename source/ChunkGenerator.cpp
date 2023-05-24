#include "../include/ChunkGenerator.h"
#include "../vendor/fastnoiselite.h"

namespace World {
    ChunkGenerator::ChunkGenerator() {
        biomeGenerator.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        noiseGenerator.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        
    }

//    void ChunkGenerator::generateChunk(Chunk* chunk, int64_t chunkX, int64_t chunkY, int64_t chunkZ) {
//        //chunk->fill();
//
//        for(size_t x = 0; x < CHUNK_SIZE; x++) {
//            for(size_t z = 0; z < CHUNK_SIZE; z++) {
//                for(size_t y = 0; y < CHUNK_SIZE; y++) {
//                    int64_t worldX = CHUNK_SIZE*chunkX + x;
//                    int64_t worldY = CHUNK_SIZE*chunkY + y;
//                    int64_t worldZ = CHUNK_SIZE*chunkZ + z;
//                    
//                    int height = b.getNoiseInterpolate(worldX, worldZ);
//
//                    if(worldY < height - 3) {
//                        chunk->setBlock(x, y, z, Blocks::Block(Blocks::STONE));
//                    } else if (worldY < height - 1) {
//                        chunk->setBlock(x, y, z, Blocks::Block(Blocks::DIRT));
//                    } else if (worldY == height - 1) {
//                        chunk->setBlock(x, y, z, Blocks::Block(Blocks::GRASS_BLOCK));
//                    }
//                }
//            }
//        }
//
//        
//        chunk->generateRendererInfo();
//    }


    std::shared_ptr<Chunk> generateChunk(const Geometry::Location& ck) {
        std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
        
        for(size_t x = 0; x < CHUNK_SIZE; x++)
        for(size_t y = 0; y < CHUNK_SIZE; y++)
        for(size_t z = 0; z < CHUNK_SIZE; z++) {
                   
        }
    }











}
