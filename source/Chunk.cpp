#include "../include/Chunk.h"
#include "../include/Settings.h"

using namespace Blocks;
using namespace Geometry;

namespace World {
    
    Chunk::Chunk() : visibleQuads() { isDirty = true }

    Chunk::Chunk(const Geometry::AxisAlignedBoundingBox& aabb) : visibleQuads() {
        AABB = aabb;
        isDirty = true;
    }

    Chunk::Chunk(int64_t worldChunkX, int64_t worldChunkY, int64_t worldChunkZ) : visibleQuads() {
        chunkX = worldChunkX;
        chunkY = worldChunkY;
        chunkZ = worldChunkZ;
        isDirty = true;
    }

    void Chunk::makeStone() {
        isDirty = true;
        for(auto& row : volume) 
            for(auto& col : row)
                for(auto& block : col)
                    block = BlockFactory::getInstance().makeBlock(STONE).value();
    }

    Blocks::Block* Chunk::getBlock(uint16_t x, uint16_t y, uint16_t z) {
        isDirty = true;
        if(x >= CHUNK_SIZE || y >= CHUNK_SIZE || z >= CHUNK_SIZE)
            return nullptr; 

        return &volume[x][y][z];
    }

    std::optional<Blocks::Block> Chunk::copyBlock(uint16_t x, uint16_t y, uint16_t z) const {
        if(x >= CHUNK_SIZE || y >= CHUNK_SIZE || z >= CHUNK_SIZE)
            return std::nullopt; 
        
        return BlockFactory::getInstance().makeBlock(volume[x][y][z].mat);  
    }

    Blocks::Material Chunk::getBlockMaterial(uint16_t x, uint16_t y, uint16_t z) const {
        if(x >= CHUNK_SIZE || y >= CHUNK_SIZE || z >= CHUNK_SIZE)
            return AIR; 

        return volume[x][y][z].mat;
    }

    bool Chunk::setBlock(uint16_t x, uint16_t y, uint16_t z, const Block& b) {
        if(x >= CHUNK_SIZE || y >= CHUNK_SIZE || z >= CHUNK_SIZE)
            return false;

        volume[x][y][z] = b;
        isDirty = true;
        return true;
    }
    
    bool Chunk::removeBlock(uint16_t x, uint16_t y, uint16_t z) {
        if(x >= CHUNK_SIZE || y >= CHUNK_SIZE || z >= CHUNK_SIZE)
            return false;
        
        volume[x][y][z].mat = Blocks::AIR;
        isDirty = true;
        return true;
    }

    void Chunk::setAABB(const Geometry::AxisAlignedBoundingBox& aabb) {
        AABB = aabb;
    }

    void Chunk::setAABB(const glm::vec3& min, const glm::vec3& max) {
        AABB = Geometry::AxisAlignedBoundingBox(min, max);
    }

    void Chunk::setAABB(float minx, float miny, float minz, float maxx, float maxy, float maxz) {
        AABB = Geometry::AxisAlignedBoundingBox(minx, miny, minz, maxx, maxy, maxz);
    }

    std::vector<Geometry::Quad*> Chunk::cullFacesUsingAABB(float CameraPosX, float CameraPosY, float CameraPosZ, Chunk* top, Chunk* left, Chunk* back, Chunk* right, Chunk* front, Chunk* bottom) {
        return std::move(cullFacesUsingAABB(glm::vec3(CameraPosX, CameraPosY, CameraPosZ), top, left, back, right, front, bottom));
    }

    bool Chunk::isBlockTransparent(uint16_t x, uint16_t y, uint16_t z) const {
        if(x >= CHUNK_SIZE || y >= CHUNK_SIZE || z >= CHUNK_SIZE)
            return false;

        return Blocks::isTransparent(volume[x][y][z].mat);
    }

    void Chunk::findVisible(Chunk* top, Chunk* left, Chunk* back, Chunk* right, Chunk* front, Chunk* bottom) {
        // store every unique quad that we need to render
        std::unordered_set<Geometry::Quad> vq;
        
        if(isDirty == false)
            std::clog << "NOTE: calling findVisible on a chunk that isn't marked as dirty. Continuing anyways." << std::endl;

        // iterate through all blocks to cull invisible ones
        for(ptrdiff_t x = 0; x < CHUNK_SIZE; x++)
        for(ptrdiff_t y = 0; y < CHUNK_SIZE; y++)
        for(ptrdiff_t z = 0; z < CHUNK_SIZE; z++) {
            // start by getting cube from the current block
            std::optional<Geometry::Cube> currentCube = volume[x][y][z].getCube(x, y, z);
            
            // if the option is nullopt, the material is air which is transparent. If it's not
            // nullopt, it could still be another transparent material, so check to see if it's
            // one of those. If it's transparent, we will add the adjacent cube faces to the
            // list of visible quads
            if(currentCube == std::nullopt || Blocks::isTransparent(volume[x][y][z].mat)) {
                std::optional<Geometry::Cube> adjacentCube;

                // since both of those checks passed, we have to get all 6 adjacent cubes,
                // and add the faces that are adjacent to the current cube to the list of
                // visible faces. However, we also have to check all 6 to make sure they
                // are not out of bounds, since out of bounds blocks will be handled by
                // a later section of the code that will retrieve the block from the adjacent
                // chunk pointers that were passed to this function

                // check adjacent block to the left
                if(x != 0) {
                    adjacentCube = volume[x-1][y][z].getCube(x-1, y, z);
                    if(adjacentCube.has_value())
                        vq.insert(std::move(adjacentCube.value().copyRightQuad()));
                }
                
                // check adjacent block on the bottom
                if(y != 0) {
                    adjacentCube = volume[x][y-1][z].getCube(x, y-1, z);
                    if(adjacentCube.has_value())
                        vq.insert(std::move(adjacentCube.value().copyTopQuad()));
                }
                
                // check adjacent block in front (north)
                if(z != 0) {
                    adjacentCube = volume[x][y][z-1].getCube(x, y, z-1);
                    if(adjacentCube.has_value())
                        vq.insert(std::move(adjacentCube.value().copyBackQuad()));
                }

                // check adjacent block to the right
                if(x != CHUNK_SIZE - 1) {
                    adjacentCube = volume[x+1][y][z].getCube(x+1, y, z);
                    if(adjacentCube.has_value())
                        vq.insert(std::move(adjacentCube.value().copyLeftQuad()));
                }

                // check adjacent block on the top
                if(y != CHUNK_SIZE - 1) {
                    adjacentCube = volume[x][y+1][z].getCube(x, y+1, z);
                    if(adjacentCube.has_value())
                        vq.insert(std::move(adjacentCube.value().copyBottomQuad()));
                }

                // check adjacent cube in the back (south)
                if(z != CHUNK_SIZE - 1) {
                    adjacentCube = volume[x][y][z+1].getCube(x, y, z+1);
                    if(adjacentCube.has_value())
                        vq.insert(std::move(adjacentCube.value().copyBottomQuad()));
                } 
                
                // Before, we only checked to see if the block was transparent. That
                // includes blocks like glass and water, but also includes air. We
                // needed to do the previous operations no matter what if this block
                // is visible; however, if we keep going from here and the current block
                // is air, we might end up adding it to the list of visible blocks, and
                // air should never be a visible block, even though other transparent blocks
                // can. Therefore, we continue to the next iteration if it's air (nullopt)
                if(currentCube == std::nullopt)
                    continue;
            }
            
            // If the current block is AIR, it should never reach this point, since the
            // previous IF statement has a continue.
            assert(currentCube.has_value() && "current cube passed checks but is AIR!");

            // if we are on an edge, and the adjacent chunk is valid (not null), then
            // we can check the block in that chunk and mark this edge block transparent
            // if it is a transparent block
            bool topChunk       = ((y == CHUNK_SIZE - 1) && top    != NULL);
            bool leftChunk      = ((x == 0)              && left   != NULL);
            bool backChunk      = ((z == CHUNK_SIZE - 1) && back   != NULL);
            bool rightChunk     = ((x == CHUNK_SIZE - 1) && right  != NULL);
            bool frontChunk     = ((z == 0)              && front  != NULL);
            bool bottomChunk    = ((y == 0)              && bottom != NULL);
            
            // if the adjacent chunk has a transparent block, add the face of the
            // current block that is facing that transparent block to the list of
            // visible quads

            if(topChunk && top->isBlockTransparent(x, 0, z))
                vq.insert(std::move(currentCube.value().copyTopQuad()));

            if(leftChunk && left->isBlockTransparent(CHUNK_SIZE - 1, y, z))
                vq.insert(std::move(currentCube.value().copyLeftQuad()));

            if(backChunk && back->isBlockTransparent(x, y, 0))
                vq.insert(std::move(currentCube.value().copyBackQuad()));

            if(rightChunk && right->isBlockTransparent(0, y, z))
                vq.insert(std::move(currentCube.value().copyRightQuad()));

            if(frontChunk && front->isBlockTransparent(x, y, CHUNK_SIZE - 1))
                vq.insert(std::move(currentCube.value().copyFrontQuad()));

            if(bottomChunk && bottom->isBlockTransparent(x, CHUNK_SIZE - 1, z));
                vq.insert(std::move(currentCube.value().copyBottomQuad()));
        }
        
        // finally, move vq into visibleQuads and mark the chunk as not dirty 
        visibleQuads = std::move(vq);
        isDirty = false;
    }

    std::vector<Geometry::Quad*> Chunk::cullFacesUsingAABB(const glm::vec3& cameraPos, Chunk* top, Chunk* left, Chunk* back, Chunk* right, Chunk* front, Chunk* bottom) {
        if(isDirty)
            findVisible(top, left, back, right, front, bottom); 
        
        for(const auto& block : visualBlocks.value()) {
            for(const auto& face : block.getCube(
        }

        return std::vector<Geometry::Quad*>(); 
    }

    std::tuple<std::vector<float>, std::vector<unsigned int>> Chunk::getFloatsAndIndices() {
        std::vector<Geometry::Cube> cubes;
        std::vector<float> floats;
        std::vector<unsigned int> indices;

        for(size_t x = 0; x < 16; x++)
            for(size_t y = 0; y < 16; y++)
                for(size_t z = 0; z < 16; z++)
                    if(x == 0 || x == 15 || y == 0 || y == 15 || z == 0 || z == 15)
                        cubes.push_back(volume[x][y][z].getCube(x, y, z).value());

        for(auto& c : cubes)
            c.setNormalizedDeviceCoordinates((float)(Settings::renderDistance * CHUNK_SIZE));

        for(size_t i = 0; i < cubes.size(); i++) {            
            auto fl = cubes[i].floats();
            for(size_t cf = 0; cf < std::get<1>(fl); cf++)
                floats.push_back(std::get<0>(fl)[cf]);

            for(auto& index : Geometry::Cube::indices) {
                indices.push_back((24 * i) + index);
            }
        }
    
        std::cout << cubes.size() << " " << floats.size() << " " << indices.size() << '\n';
                
        return std::make_tuple(floats, indices);
    }
}

