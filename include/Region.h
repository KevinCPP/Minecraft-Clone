#ifndef REGION_H
#define REGION_H

#include <glm/glm.hpp>

#include "Quad.h"
#include "Cube.h"
#include "World.h"
#include "Chunk.h"
#include "Settings.h"
#include "CubeFactory.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "../vendor/fastnoiselite.h"

namespace World {
    class Region {
    private:
        const size_t rd;
        Chunk*** loadedChunks;
        FastNoiseLite noiseGenerator; 
    public:
        
        Region();
        ~Region();
        
        void initializeOffsets();
        void generateChunks(size_t x, size_t y, size_t z, int seed = 0);
        std::vector<float> getVertexData(); 
        
    };
}

#endif
