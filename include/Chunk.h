#ifndef CHUNK_H
#define CHUNK_H

#include "Cube.h"
#include "World.h"
#include "Block.h"
#include "CubeFactory.h"
#include "AxisAlignedBoundingBox.h"

#include <vector>
#include <optional>
#include <ankerl/unordered_dense.h>

namespace World {

    class Chunk {
    private:
        // stores the blocks in the chunk
        Blocks::Block volume[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
        
        // store a list of all the available quads in a chunk
        std::vector<Geometry::Quad> visibleQuads;
        

        // store pointers to adjacent chunks
        Chunk* adjTop;
        Chunk* adjLeft;
        Chunk* adjBack;
        Chunk* adjRight;
        Chunk* adjFront;
        Chunk* adjBottom;

        // marks if a chunk needs to redo the findVisible() operation
        bool isDirty; 
        
        // stores the offsets of the chunk which will be used when performing findVisible()
        // to offset the positions of the cubes. Should be relative to the rendered space 
        int16_t chunkX, chunkY, chunkZ;
    
    public:
        // default constructor
        Chunk();
        
        // initializes chunkX, chunkY, chunkZ
        Chunk(int16_t X, int16_t Y, int16_t Z);
        
        // initializes X, Y, and Z coordinates as well as adjacent chunks
        Chunk(int16_t X, int16_t Y, int16_t Z, Chunk* top, Chunk* left, Chunk* back, Chunk* right, Chunk* front, Chunk* bottom);

        // returns true if a set of x, y, and z values are within the bounds of 0, CHUNK_SIZE - 1
        bool isInsideChunkSize(uint16_t x, uint16_t y, uint16_t z);

        // returns the block material at x, y, z, or air if xyz are out of bounds
        Blocks::Material getBlockMaterial(uint16_t x, uint16_t y, uint16_t z) const;

        // sets a block, relative to chunk coordinates. 
        bool setBlock(uint16_t x, uint16_t y, uint16_t z, const Blocks::Block& b);
        
        // effectively sets the block to AIR. 
        bool removeBlock(uint16_t x, uint16_t y, uint16_t z);
        
        // will check to see if a given block in the chunk is transparent
        bool isBlockTransparent(uint16_t x, uint16_t y, uint16_t z) const;

        // sets the adjacent chunk pointers
        void setAdjacentChunks(Chunk* top, Chunk* left, Chunk* back, Chunk* right, Chunk* front, Chunk* bottom);

        // updates the visibility at one specific block coordinate. Essentially findVisible() except on one block at x, y, z
        void updateBlockVisibility(uint16_t x, uint16_t y, uint16_t z, bool NDC = true, uint32_t NDCfactor = CHUNK_SIZE * Settings::renderDistance);

        // iterates through all of the blocks in the chunk and fills the visibleQuads set with quads that have adjacent transparent blocks
        void findVisible(bool NDC = true, uint32_t NDCfactor = CHUNK_SIZE * Settings::renderDistance);

        // fills the chunk with a given material
        void fill(const Material& mat = Blocks::STONE);

    };

}

#endif
