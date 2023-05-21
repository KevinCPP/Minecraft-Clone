#include "../include/ChunkGenerator.h"

namespace World {
    void ChunkGenerator::generateChunk(Chunk* chunk, int64_t chunkX, int64_t chunkY, int64_t chunkZ) {
        for(size_t x = 0; x < CHUNK_SIZE; x++) {
            for(size_t z = 0; z < CHUNK_SIZE; z++) {
                for(size_t y = 0; y < CHUNK_SIZE; y++) {
                    int64_t worldX = chunkX + x;
                    int64_t worldY = chunkY + y;
                    int64_t worldZ = chunkZ + z;
                    
                    int height = b.getNoiseInterpolate(worldX, worldZ);

                    if(worldY < height - 3) {
                        chunk->setBlock(chunkX, chunkY, chunkZ, Blocks::Block(Blocks::STONE));
                    } else if (worldY < height - 1) {
                        chunk->setBlock(chunkX, chunkY, chunkZ, Blocks::Block(Blocks::DIRT));
                    } else if (worldY == height) {
                        chunk->setBlock(chunkX, chunkY, chunkZ, Blocks::Block(Blocks::GRASS_BLOCK));
                    }
                }
            }
        }
    }
}
