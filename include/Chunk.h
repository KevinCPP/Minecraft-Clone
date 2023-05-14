#ifndef CHUNK_H
#define CHUNK_H

#include "Cube.h"
#include "World.h"
#include "Block.h"
#include "CubeFactory.h"
#include "BlockFactory.h"
#include "AxisAlignedBoundingBox.h"

#include <vector>
#include <optional>
#include <unordered_set>

namespace World {

    struct Chunk {
        // stores the blocks in the chunk
        Blocks::Block volume[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
        std::unordered_set<Geometry::Quad> visibleQuads;
        bool isDirty; 
        // stores the chunk's position in world space. Uses 1 chunk = 1 unit.
        // can be converted to block coordinates by multiplying by CHUNK_SIZE.
        int64_t chunkX, chunkY, chunkZ;

        // stores the chunk's AABB in region space.
        Geometry::AxisAlignedBoundingBox AABB;
        
        // constructors
        Chunk();
        Chunk(const Geometry::AxisAlignedBoundingBox& aabb);
        Chunk(int64_t worldChunkX, int64_t worldChunkY, int64_t worldChunkZ);
        
        // returns a block given chunk coordinates. MARKS CHUNK AS DIRTY
        Blocks::Block* getBlock(uint16_t x, uint16_t y, uint16_t z);
        
        // returns a copy of the block, or nullopt if it's air or if the xyz are out of bounds
        std::optional<Blocks::Block> copyBlock(uint16_t x, uint16_t y, uint16_t z) const;

        // returns the block material at x, y, z, or air if xyz are out of bounds
        Blocks::Material getBlockMaterial(uint16_t x, uint16_t y, uint16_t z) const;

        // sets a block, relative to chunk coordinates. MARKS CHUNK AS DIRTY
        bool setBlock(uint16_t x, uint16_t y, uint16_t z, const Blocks::Block& b);
        
        // effectively sets the block to AIR. MARKS CHUNK AS DIRTY
        bool removeBlock(uint16_t x, uint16_t y, uint16_t z);

        bool isBlockTransparent(uint16_t x, uint16_t y, uint16_t z) const;

        // sets the Axis Aligned Bounding Box (IN WORLDSPACE)
        void setAABB(const Geometry::AxisAlignedBoundingBox& aabb);
        void setAABB(const glm::vec3& min, const glm::vec3& max);
        void setAABB(float minx, float miny, float minz, float maxx, float maxy, float maxz);
        
        // sets the world chunk coordinates (chunkX, chunkY, chunkZ)
        void setWorldChunkCoords(int64_t worldChunkX, int64_t worldChunkY, int64_t worldChunkZ);
        
        void findVisible(Chunk* top = NULL, Chunk* left = NULL, Chunk* back = NULL, Chunk* right = NULL, Chunk* front = NULL, Chunk* bottom = NULL);

        // takes the camera's position and culls faces that do not have an adjacent air block,
        // as well as performs back face culling based on the camera's position. The camera's position
        // and axis aligned bounding box should both be in "region space", as in, relative to the camera
        // and the space that's being rendered.
        std::vector<Geometry::Quad*> cullFacesUsingAABB(float CameraPosX, float CameraPosY, float CameraPosZ, Chunk* top = NULL, Chunk* left = NULL, Chunk* back = NULL, Chunk* right = NULL, Chunk* front = NULL, Chunk* bottom = NULL);
        std::vector<Geometry::Quad*> cullFacesUsingAABB(const glm::vec3& cameraPos, Chunk* top = NULL, Chunk* left = NULL, Chunk* back = NULL, Chunk* right = NULL, Chunk* front = NULL, Chunk* bottom = NULL);

        // fills the chunk with stone
        void makeStone();

        // temporary function to get floats and indices
        std::tuple<std::vector<float>, std::vector<unsigned int>> getFloatsAndIndices();
    };

}

#endif
