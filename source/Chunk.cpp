#include "../include/Chunk.h"
#include "../include/Settings.h"

using namespace Blocks;
using namespace Geometry;

namespace World {
    
    // default constructor
    Chunk::Chunk() {
        // by default, if no adjacent chunks are provided,
        // NULL chunks will be used for all operations
        adjTop = NULL;
        adjLeft = NULL;
        adjBack = NULL;
        adjRight = NULL;
        adjFront = NULL;
        adjBottom = NULL;
        
        // since the findVisible() operation has not been executed for this chunk
        // mark the chunk as dirty initially.
        isDirty = true;
        
        // if no offset coordinates are provided, default to 0, in which case the
        // vertex data for the Quads placed in visibleQuads will just be relative to
        // this specific chunk.
        chunkX = 0;
        chunkY = 0;
        chunkZ = 0;
    }
    
    // defer to default constructor to initialize the chunk,
    // then set the X Y and Z offsets
    Chunk::Chunk(int16_t X, int16_t Y, int16_t Z) : Chunk() {
        setOffsetCoordinates(X, Y, Z);
    }

    // defer to the Chunk(X, Y, Z) constructor to initialize all default
    // member variables as well as the X Y and Z offsets, then set the
    // adjacent chunks
    Chunk::Chunk(int16_t X, int16_t Y, int16_t Z, Chunk* top, Chunk* left, Chunk* back, Chunk* right, Chunk* front, Chunk* bottom) : Chunk(X, Y, Z) {
        setAdjacentChunks(top, left, back, right, front, bottom);    
    }

    bool Chunk::isInsideChunkSize(uint16_t x, uint16_t y, uint16_t z) const {
        return (x < CHUNK_SIZE && y < CHUNK_SIZE && z < CHUNK_SIZE); 
    }
   
    Blocks::Material Chunk::getBlockMaterial(uint16_t x, uint16_t y, uint16_t z) const {
        if(!isInsideChunkSize(x, y, z))
            return Blocks::AIR;

        return volume[x][y][z].mat;
    }
    
    // sets a block at a given x, y, and z chunk coordinate. Returns false if
    // x, y, and z are out of bounds, otherwise sets the block and returns true
    bool Chunk::setBlock(uint16_t x, uint16_t y, uint16_t z, const Blocks::Block& b) {
        if(!isInsideChunkSize(x, y, z))
            return false;

        volume[x][y][z] = b;
        return true;
    }
    
    // removes a block at a given x, y, and z coordinate (effectively sets it to air)
    bool Chunk::removeBlock(uint16_t x, uint16_t y, uint16_t z) {
        if(!isInsideChunkSize(x, y, z)) 
            return false;

        volume[x][y][z].mat = Blocks::AIR;
        return true;
    }
    
    // checks if a block at a given x, y, and z coordinate is transparent. Contains an assertion that
    // x, y, and z are inside chunk boundaries, because unlike setBlock and removeBlock, there would be
    // ambiguity if we just returned true/false (was it actually transparent or was xyz out of bounds?)
    bool isBlockTransparent(uint16_t x, uint16_t y, uint16_t z) const {
        assert(isInsideChunkSize(x, y, z) && "Attempted to check if a block was transparent, outside of chunk bounds!");
        
        return Blocks::isTransparent(volume[x][y][z].mat);
    }

    // simply sets pointers to the adjacent chunks. NULL is acceptable
    void setAdjacentChunks(Chunk* top, Chunk* left, Chunk* back, Chunk* right, Chunk* front, Chunk* bottom) {
        adjTop = top;
        adjLeft = left;
        adjBack = back;
        adjRight = right;
        adjFront = front;
        adjBottom = bottom;
    }

    void Chunk::updateBlockVisibility(uint16_t x, uint16_t y, uint16_t z, bool NDC, uint32_t NDCfactor) {
        // we can't perform this operation if the x, y, and z values are out of bounds. that is a fatal error
        assert(isInsideChunkSize(x, y, z) && "Attempted to update block visibility for a block that was outside the chunk!");

        // get the relative coordinates of the block (using chunk offset coords)
        uint32_t rx = chunkX + x;
        uint32_t ry = chunkY + y;
        uint32_t rz = chunkZ + z;

        // if the relative coords (that we're using for the actual vertex data) is larger than the
        // maximum distance we are rendering, that means the division operation would end up being
        // outside of the NDC. That is a fatal error.
        if(NDC) {
            assert(rx <= NDCfactor && "attempting to create cube outside of NDC!");
            assert(ry <= NDCfactor && "attempting to create cube outside of NDC!");
            assert(rz <= NDCfactor && "attempting to create cube outside of NDC!");
        }

        // start by getting cube from the current block
        std::optional<Geometry::Cube> currentCube = volume[x][y][z].getCube(rx, ry, rz);
        
        // if the cube has a value and we're using NDC, set it's NDC.
        if(NDC && currentCube.has_value())
            currentCube.value().setNormalizedDeviceCoordinates(NDCfactor);

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
                adjacentCube = volume[x-1][y][z].getCube(rx-1, ry, rz);
                if(NDC)
                    adjacentCube.setNormalizedDeviceCoordinates(NDCfactor);

                if(adjacentCube.has_value())
                    vq.push_back(std::move(adjacentCube.value().copyRightQuad()));
            }
            
            // check adjacent block on the bottom
            if(y != 0) {
                adjacentCube = volume[x][y-1][z].getCube(rx, ry-1, rz);
                if(NDC)
                    adjacentCube.setNormalizedDeviceCoordinates(NDCfactor);

                if(adjacentCube.has_value())
                    vq.push_back(std::move(adjacentCube.value().copyTopQuad()));
            }
            
            // check adjacent block in front (north)
            if(z != 0) {
                adjacentCube = volume[x][y][z-1].getCube(rx, ry, rz-1);
                if(NDC)
                    adjacentCube.setNormalizedDeviceCoordinates(NDCfactor);

                if(adjacentCube.has_value())
                    vq.push_back(std::move(adjacentCube.value().copyBackQuad()));
            }

            // check adjacent block to the right
            if(x != CHUNK_SIZE - 1) {
                adjacentCube = volume[x+1][y][z].getCube(rx+1, ry, rz);
                if(NDC)
                    adjacentCube.setNormalizedDeviceCoordinates(NDCfactor);

                if(adjacentCube.has_value())
                    vq.push_back(std::move(adjacentCube.value().copyLeftQuad()));
            }

            // check adjacent block on the top
            if(y != CHUNK_SIZE - 1) {
                adjacentCube = volume[x][y+1][z].getCube(rx, ry+1, rz);
                if(NDC)
                    adjacentCube.setNormalizedDeviceCoordinates(NDCfactor);

                if(adjacentCube.has_value())
                    vq.push_back(std::move(adjacentCube.value().copyBottomQuad()));
            }

            // check adjacent cube in the back (south)
            if(z != CHUNK_SIZE - 1) {
                adjacentCube = volume[x][y][z+1].getCube(rx, ry, rz+1);
                if(NDC)
                    adjacentCube.setNormalizedDeviceCoordinates(NDCfactor);

                if(adjacentCube.has_value())
                    vq.push_back(std::move(adjacentCube.value().copyBottomQuad()));
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

       
        // if we are on the chunk's edge, and the adjacent chunk is either NULL (in which case we'll treat it as if it's transparent)
        // or if the adjacent chunk is valid AND the corresponding block is transparent -- add the quad facing it to the list of visible quads
        bool topTransparent    = (y == CHUNK_SIZE - 1) && ((top    == NULL) || ((top    != NULL) && top->isBlockTransparent(x, 0, z)));
        bool leftTransparent   = (x == 0)              && ((left   == NULL) || ((left   != NULL) && left->isBlockTransparent(CHUNK_SIZE - 1, y, z)));
        bool backTransparent   = (z == CHUNK_SIZE - 1) && ((back   == NULL) || ((back   != NULL) && back->isBlockTransparent(x, y, 0)));
        bool rightTransparent  = (x == CHUNK_SIZE - 1) && ((right  == NULL) || ((right  != NULL) && right->isBlockTransparent(0, y, z)));
        bool frontTransparent  = (z == 0             ) && ((front  == NULL) || ((front  != NULL) && front->isBlockTransparent(x, y, CHUNK_SIZE - 1)));
        bool bottomTransparent = (y == 0             ) && ((bottom == NULL) || ((bottom != NULL) && bottom->isBlockTransparent(x, CHUNK_SIZE - 1, z)));


        // if the adjacent chunk has a transparent block, add the face of the
        // current block that is facing that transparent block to the list of
        // visible quads
        if(topTransparent)
            vq.push_back(std::move(currentCube.value().copyTopQuad()));
        if(leftTransparent)
            vq.push_back(std::move(currentCube.value().copyLeftQuad()));
        if(backTransparent)
            vq.push_back(std::move(currentCube.value().copyBackQuad()));
        if(rightTransparent)
            vq.push_back(std::move(currentCube.value().copyRightQuad()));
        if(frontTransparent)
            vq.push_back(std::move(currentCube.value().copyFrontQuad()));
        if(bottomTransparent)
            vq.push_back(std::move(currentCube.value().copyBottomQuad()));

    }

    void Chunk::findVisible(Chunk* top, Chunk* left, Chunk* back, Chunk* right, Chunk* front, Chunk* bottom) {
        // store every unique quad that we need to render
        std::vector<Geometry::Quad> vq;
        if(isDirty == false)
            std::clog << "NOTE: calling findVisible on a chunk that isn't marked as dirty. Continuing anyways." << std::endl;

        // iterate through all blocks to cull invisible ones
        for(size_t x = 0; x < CHUNK_SIZE; x++)
        for(size_t y = 0; y < CHUNK_SIZE; y++)
        for(size_t z = 0; z < CHUNK_SIZE; z++) {
            // start by getting cube from the current block
            std::optional<Geometry::Cube> currentCube = volume[x][y][z].getCube(x, y, z);

            if(currentCube.has_value())
                currentCube.value().setNormalizedDeviceCoordinates(CHUNK_SIZE * Settings::renderDistance);
            
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
                        vq.push_back(std::move(adjacentCube.value().copyRightQuad()));
                }
                
                // check adjacent block on the bottom
                if(y != 0) {
                    adjacentCube = volume[x][y-1][z].getCube(x, y-1, z);
                    if(adjacentCube.has_value())
                        vq.push_back(std::move(adjacentCube.value().copyTopQuad()));
                }
                
                // check adjacent block in front (north)
                if(z != 0) {
                    adjacentCube = volume[x][y][z-1].getCube(x, y, z-1);
                    if(adjacentCube.has_value())
                        vq.push_back(std::move(adjacentCube.value().copyBackQuad()));
                }

                // check adjacent block to the right
                if(x != CHUNK_SIZE - 1) {
                    adjacentCube = volume[x+1][y][z].getCube(x+1, y, z);
                    if(adjacentCube.has_value())
                        vq.push_back(std::move(adjacentCube.value().copyLeftQuad()));
                }

                // check adjacent block on the top
                if(y != CHUNK_SIZE - 1) {
                    adjacentCube = volume[x][y+1][z].getCube(x, y+1, z);
                    if(adjacentCube.has_value())
                        vq.push_back(std::move(adjacentCube.value().copyBottomQuad()));
                }

                // check adjacent cube in the back (south)
                if(z != CHUNK_SIZE - 1) {
                    adjacentCube = volume[x][y][z+1].getCube(x, y, z+1);
                    if(adjacentCube.has_value())
                        vq.push_back(std::move(adjacentCube.value().copyBottomQuad()));
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

           
            // if we are on the chunk's edge, and the adjacent chunk is either NULL (in which case we'll treat it as if it's transparent)
            // or if the adjacent chunk is valid AND the corresponding block is transparent -- add the quad facing it to the list of visible quads
            bool topTransparent    = (y == CHUNK_SIZE - 1) && ((top    == NULL) || ((top    != NULL) && top->isBlockTransparent(x, 0, z)));
            bool leftTransparent   = (x == 0)              && ((left   == NULL) || ((left   != NULL) && left->isBlockTransparent(CHUNK_SIZE - 1, y, z)));
            bool backTransparent   = (z == CHUNK_SIZE - 1) && ((back   == NULL) || ((back   != NULL) && back->isBlockTransparent(x, y, 0)));
            bool rightTransparent  = (x == CHUNK_SIZE - 1) && ((right  == NULL) || ((right  != NULL) && right->isBlockTransparent(0, y, z)));
            bool frontTransparent  = (z == 0             ) && ((front  == NULL) || ((front  != NULL) && front->isBlockTransparent(x, y, CHUNK_SIZE - 1)));
            bool bottomTransparent = (y == 0             ) && ((bottom == NULL) || ((bottom != NULL) && bottom->isBlockTransparent(x, CHUNK_SIZE - 1, z)));


            // if the adjacent chunk has a transparent block, add the face of the
            // current block that is facing that transparent block to the list of
            // visible quads
            if(topTransparent)
                vq.push_back(std::move(currentCube.value().copyTopQuad()));
            if(leftTransparent)
                vq.push_back(std::move(currentCube.value().copyLeftQuad()));
            if(backTransparent)
                vq.push_back(std::move(currentCube.value().copyBackQuad()));
            if(rightTransparent)
                vq.push_back(std::move(currentCube.value().copyRightQuad()));
            if(frontTransparent)
                vq.push_back(std::move(currentCube.value().copyFrontQuad()));
            if(bottomTransparent)
                vq.push_back(std::move(currentCube.value().copyBottomQuad()));
        }
        
        // finally, move vq into visibleQuads and mark the chunk as not dirty 
        std::cout << "finished culling invisible quads. Vector size: " << vq.size() << std::endl;

        visibleQuads = std::move(vq);
        isDirty = false;
    }

    void Chunk::fill(const Material& mat) {
        for(size_t x = 0; x < CHUNK_SIZE; x++)
        for(size_t y = 0; y < CHUNK_SIZE; y++)
        for(size_t z = 0; z < CHUNK_SIZE; z++)
            volume[x][y][z].mat = mat;
    }
}

