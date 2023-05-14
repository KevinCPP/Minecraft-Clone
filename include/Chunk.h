#ifndef CHUNK_H
#define CHUNK_H

#include "Cube.h"
#include "World.h"
#include "Block.h"
#include "CubeFactory.h"
#include "AxisAlignedBoundingBox.h"

#include <vector>

namespace World {

    struct Chunk {
        // stores the blocks in the chunk
        Blocks::Block volume[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
        
        // stores the chunk's position in world space. Uses 1 chunk = 1 unit.
        // can be converted to block coordinates by multiplying by CHUNK_SIZE.
        int64_t chunkX, chunkY, chunkZ;

        // stores the chunk's AABB in region space.
        Geometry::AxisAlignedBoundingBox AABB;
        
        // constructors
        Chunk();
        Chunk(const Geometry::AxisAlignedBoundingBox& aabb);
        Chunk(int64_t worldChunkX, int64_t worldChunkY, int64_t worldChunkZ);
        
        // returns a block given chunk coordinates
        Blocks::Block* getBlock(uint16_t x, uint16_t y, uint16_t z);
        
        // sets a block, relative to chunk coordinates
        bool setBlock(uint16_t x, uint16_t y, uint16_t z, const Blocks::Block& b);
        
        // effectively sets the block to AIR
        bool removeBlock(uint16_t x, uint16_t y, uint16_t z);

        // sets the Axis Aligned Bounding Box (IN WORLDSPACE)
        void setAABB(const Geometry::AxisAlignedBoundingBox& aabb);
        void setAABB(const glm::vec3& min, const glm::vec3& max);
        void setAABB(float minx, float miny, float minz, float maxx, float maxy, float maxz);
        
        // sets the world chunk coordinates (chunkX, chunkY, chunkZ)
        void setWorldChunkCoords(int64_t worldChunkX, int64_t worldChunkY, int64_t worldChunkZ);

        // takes the camera's position and culls faces that do not have an adjacent air block,
        // as well as performs back face culling based on the camera's position. The camera's position
        // and axis aligned bounding box should both be in "region space", as in, relative to the camera
        // and the space that's being rendered.
        std::vector<Geometry::Quad*> cullFacesUsingAABB(float CameraPosX, float CameraPosY, float CameraPosZ);
        std::vector<Geometry::Quad*> cullFacesUsingAABB(const glm::vec3& cameraPos);

        // fills the chunk with stone
        void makeStone();

        // temporary function to get floats and indices
        std::tuple<std::vector<float>, std::vector<unsigned int>> getFloatsAndIndices();
    };

}

#endif
