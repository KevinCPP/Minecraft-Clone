#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <cstdio>

#include "../vendor/fastnoiselite.h"

#include "../include/Cube.h"
#include "../include/Quad.h"
#include "../include/Chunk.h"
#include "../include/Vertex.h"
#include "../include/Camera.h"
#include "../include/Region.h"
#include "../include/Texture.h"
#include "../include/Settings.h"
#include "../include/Renderer.h"
#include "../include/IndexBuffer.h"
#include "../include/VertexArray.h"
#include "../include/TextureAtlas.h"
#include "../include/VertexBuffer.h"
#include "../include/VertexBufferLayout.h"

#include "test.h"


void testChunk(std::vector<float>& vertexSrc, std::vector<unsigned int>& indexSrc, int offsetX, int offsetZ) {
    // initialize chunk object
    World::Chunk c;
    // initialize noise generator
    FastNoiseLite noiseGenerator;
    
    noiseGenerator.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    // set the seed
    noiseGenerator.SetSeed(0);
    
    // fill in the noise map 
    uint16_t noiseMap[World::CHUNK_SIZE][World::CHUNK_SIZE];
    for(size_t x = 0; x < World::CHUNK_SIZE; x++) {
        for(size_t z = 0; z < World::CHUNK_SIZE; z++) {
            noiseMap[x][z] = World::CHUNK_SIZE * noiseGenerator.GetNoise((float)x + offsetX, (float)z + offsetZ);
            
            uint16_t thisHeight = noiseMap[x][z];
            for(size_t y = 0; y < thisHeight; y++) {
                if(y < thisHeight - 3) {
                    // set all blocks more than 3 below the max height to stone
                    c.setBlock(x, y, z, Blocks::Block(Blocks::STONE));
                } else if (y < thisHeight - 1) {
                    // set all blocks less than 3, but more than 1 block below the max to dirt
                    c.setBlock(x, y, z, Blocks::Block(Blocks::DIRT));
                } else {
                    // set the top block to grass
                    c.setBlock(x, y, z, Blocks::Block(Blocks::GRASS_BLOCK));
                }
            }
        }
    }
    
    size_t numQuads = 0;
    // iterate through the set of data for all visible quads in the chunk
    for(auto vqd = c.visibleQuadsBegin(); vqd != c.visibleQuadsEnd(); vqd++) {
        // get the block for this visible quad
        Blocks::Material mat = c.getBlockMaterial(vqd->x, vqd->y, vqd->z);
        // create a cube from that material
        Geometry::Cube thisCube = *Blocks::Block(mat).getCube(offsetX + vqd->x, vqd->y, offsetZ + vqd->z);
        
        // get the quad that is actually visible on this cube
        Geometry::Quad visibleQuad = thisCube.copyQuad((Geometry::Direction)vqd->face);
        
        // before inserting it into the vertexData vector, go ahead and place it's indices in the indexData vector
        std::cout << std::endl;

        numQuads++;
        // convert the quad to floating point vertex data:
        float* ptr = (float*)(&visibleQuad);
        for(size_t i = 0; i < Geometry::FLOATS_PER_QUAD; i++) {
            vertexSrc.push_back(ptr[i]);
        }
    }

    Geometry::makeIndicesFromQuads(numQuads, indexSrc); 
}

    
