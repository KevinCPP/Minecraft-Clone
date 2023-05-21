#ifndef CHUNKRENDERER_H
#define CHUNKRENDERER_H

#include "Renderer.h"

class ChunkRenderer {
private:
    Renderer renderer;

public:
    void renderChunk(int64_t chunkX, int64_t chunkY, int64_t chunkZ, Chunk* chunk) {
        std::vector<float> vertexData;
        std::vector<unsigned int> indexData;


    }
}



#endif
