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

    void Chunk::setOffsetCoordinates(int16_t X, int16_t Y, int16_t Z) {
        
        
        chunkX = X;
        chunkY = Y;
        chunkZ = Z;
    }

    // sets a block at a given x, y, and z chunk coordinate. Returns false if
    // x, y, and z are out of bounds, otherwise sets the block and returns true
    bool Chunk::setBlock(uint16_t x, uint16_t y, uint16_t z, const Blocks::Block& b) {
        if(!isInsideChunkSize(x, y, z))
            return false;

        volume[x][y][z] = b;
        updateBlockVisibility(x, y, z);
        return true;
    }
    
    // removes a block at a given x, y, and z coordinate (effectively sets it to air)
    bool Chunk::removeBlock(uint16_t x, uint16_t y, uint16_t z) {
        if(!isInsideChunkSize(x, y, z)) 
            return false;

        volume[x][y][z].mat = Blocks::AIR;
        updateBlockVisibility(x, y, z);
        return true;
    }
    
    // checks if a block at a given x, y, and z coordinate is transparent. Contains an assertion that
    // x, y, and z are inside chunk boundaries, because unlike setBlock and removeBlock, there would be
    // ambiguity if we just returned true/false (was it actually transparent or was xyz out of bounds?)
    bool Chunk::isBlockTransparent(uint16_t x, uint16_t y, uint16_t z) const {
        assert(isInsideChunkSize(x, y, z) && "Attempted to check if a block was transparent, outside of chunk bounds!");
        
        return Blocks::isTransparent(volume[x][y][z].mat);
    }

    // simply sets pointers to the adjacent chunks. NULL is acceptable
    void Chunk::setAdjacentChunks(Chunk* top, Chunk* left, Chunk* back, Chunk* right, Chunk* front, Chunk* bottom) {
        adjTop = top;
        adjLeft = left;
        adjBack = back;
        adjRight = right;
        adjFront = front;
        adjBottom = bottom;
    }

    void Chunk::removeFacesAt(uint16_t x, uint16_t y, uint16_t z) {
        // get relative coordinates to use for the quad data
        uint32_t rx = chunkX + x;
        uint32_t ry = chunkY + y;
        uint32_t rz = chunkZ + z;
        
        // material of the block at x, y ,z
        Blocks::Material cm = volume[x][y][z].mat;
         
        // if x, y, z is not transparent, that means it is solid. Therefore, the adjacent quads are occluded
        // This if statement will handle all quads that are inside this chunk and are adjacent to the solid block
        if(!Blocks::isTransparent(cm)) {
            if(x != 0)
                visibleQuads.erase(visibleQuadData(rx-1, ry, rz, Geometry::RIGHT));
            if(y != 0)
                visibleQuads.erase(visibleQuadData(rx, ry-1, rz, Geometry::TOP));
            if(z != 0)
                visibleQuads.erase(visibleQuadData(rx, ry, rz-1, Geometry::BACK));
            if(x != CHUNK_SIZE - 1)
                visibleQuads.erase(visibleQuadData(rx+1, ry, rz, Geometry::LEFT));
            if(y != CHUNK_SIZE - 1)
                visibleQuads.erase(visibleQuadData(rx, ry+1, rz, Geometry::BOTTOM));
            if(z != CHUNK_SIZE - 1)
                visibleQuads.erase(visibleQuadData(rx, ry, rz+1, Geometry::FRONT));
        } else if (cm == Blocks::AIR) {
            visibleQuads.erase(visibleQuadData(rx, ry, rz, Geometry::TOP));
            visibleQuads.erase(visibleQuadData(rx, ry, rz, Geometry::LEFT));
            visibleQuads.erase(visibleQuadData(rx, ry, rz, Geometry::BACK));
            visibleQuads.erase(visibleQuadData(rx, ry, rz, Geometry::RIGHT));
            visibleQuads.erase(visibleQuadData(rx, ry, rz, Geometry::FRONT));
            visibleQuads.erase(visibleQuadData(rx, ry, rz, Geometry::BOTTOM));
        }

        bool cleftTransparent   = (adjLeft   == NULL || adjLeft->isBlockTransparent(CHUNK_SIZE - 1, y, z));
        bool cbottomTransparent = (adjBottom == NULL || adjBottom->isBlockTransparent(x, CHUNK_SIZE - 1, z));
        bool cfrontTransparent  = (adjFront  == NULL || adjFront->isBlockTransparent(x, y, CHUNK_SIZE - 1));
        bool crightTransparent  = (adjRight  == NULL || adjRight->isBlockTransparent(0, y, z));
        bool ctopTransparent    = (adjTop    == NULL || adjTop->isBlockTransparent(x, 0, z));
        bool cbackTransparent   = (adjBack   == NULL || adjBack->isBlockTransparent(x, y, 0));
        
        // if we're at the edge and the adjacent chunk does not have a transparent block, erase the face on this block which is
        // facing that solid block, since it would be occluded
        if((x == 0) && !cleftTransparent)
            visibleQuads.erase(visibleQuadData(rx, ry, rz, Geometry::LEFT));
        if((y == 0) && !cbottomTransparent)
            visibleQuads.erase(visibleQuadData(rx, ry, rz, Geometry::BOTTOM));
        if((z == 0) && !cfrontTransparent)
            visibleQuads.erase(visibleQuadData(rx, ry, rz, Geometry::FRONT));
        if((x == CHUNK_SIZE - 1) && !crightTransparent)
            visibleQuads.erase(visibleQuadData(rx, ry, rz, Geometry::RIGHT));
        if((y == CHUNK_SIZE - 1) && !ctopTransparent) 
            visibleQuads.erase(visibleQuadData(rx, ry, rz, Geometry::TOP));
        if((z == CHUNK_SIZE - 1) && !cbackTransparent)
            visibleQuads.erase(visibleQuadData(rx, ry, rz, Geometry::BACK));
    }

    void Chunk::addFacesAt(uint16_t x, uint16_t y, uint16_t z) {
        uint32_t rx = chunkX + x;
        uint32_t ry = chunkY + y;
        uint32_t rz = chunkZ + z;
    
        Blocks::Material cm = volume[x][y][z].mat;
        
        // first, if this block is transparent, add all faces that are facing it since those would all be visible
        if(Blocks::isTransparent(cm)) {
            // we'll deal with edges later, for now, just check the adjacent block in this chunk
            // and add it's corresponding face if it isn't AIR.
            if(x != 0 && volume[x-1][y][z].mat != AIR)
                visibleQuads.insert(std::move(visibleQuadData(rx-1, ry, rz, Geometry::RIGHT)));
            if(y != 0 && volume[x][y-1][z].mat != AIR)
                visibleQuads.insert(std::move(visibleQuadData(rx, ry-1, rz, Geometry::TOP)));
            if(z != 0 && volume[x][y][z-1].mat != AIR)
                visibleQuads.insert(std::move(visibleQuadData(rx, ry, rz-1, Geometry::BACK)));
            if(x != CHUNK_SIZE - 1 && volume[x+1][y][z].mat != AIR)
                visibleQuads.insert(std::move(visibleQuadData(rx+1, ry, rz, Geometry::LEFT)));
            if(y != CHUNK_SIZE - 1 && volume[x][y+1][z].mat != AIR)
                visibleQuads.insert(std::move(visibleQuadData(rx, ry+1, rz, Geometry::BOTTOM)));
            if(z != CHUNK_SIZE - 1 && volume[x][y][z+1].mat != AIR)
                visibleQuads.insert(std::move(visibleQuadData(rx, ry, rz+1, Geometry::FRONT)));
            
            // the rest of this function just adds this blocks' faces. If it's air, it will never
            // have a visible face, so we can end the function here.
            if(cm == Blocks::AIR)
                return;
        }
      
        // check if the adjacent block is transparent
        bool leftTransparent    = (x != 0              && Blocks::isTransparent(volume[x-1][y][z].mat));
        bool bottomTransparent  = (y != 0              && Blocks::isTransparent(volume[x][y-1][z].mat));
        bool frontTransparent   = (z != 0              && Blocks::isTransparent(volume[x][y][z-1].mat));
        bool rightTransparent   = (x != CHUNK_SIZE - 1 && Blocks::isTransparent(volume[x+1][y][z].mat));
        bool topTransparent     = (y != CHUNK_SIZE - 1 && Blocks::isTransparent(volume[x][y+1][z].mat));
        bool backTransparent    = (z != CHUNK_SIZE - 1 && Blocks::isTransparent(volume[x][y][z+1].mat));
        
        // if we're at the edge, check if the corresponding block in the adjacent chunk is transparent
        bool cleftTransparent   = (x == 0)              && (adjLeft   == NULL || adjLeft->isBlockTransparent(CHUNK_SIZE - 1, y, z));
        bool cbottomTransparent = (y == 0)              && (adjBottom == NULL || adjBottom->isBlockTransparent(x, CHUNK_SIZE - 1, z));
        bool cfrontTransparent  = (z == 0)              && (adjFront  == NULL || adjFront->isBlockTransparent(x, y, CHUNK_SIZE - 1));
        bool crightTransparent  = (x == CHUNK_SIZE - 1) && (adjRight  == NULL || adjRight->isBlockTransparent(0, y, z));
        bool ctopTransparent    = (y == CHUNK_SIZE - 1) && (adjTop    == NULL || adjTop->isBlockTransparent(x, 0, z));
        bool cbackTransparent   = (z == CHUNK_SIZE - 1) && (adjBack   == NULL || adjBack->isBlockTransparent(x, y, 0));

        // at this point, the block cannot be AIR since the function would return if it was air.
        // every other block is visible, so if this block has any adjacent transparent blocks,
        // add the quad that is facing that transparent block to the list of visible quads
        if(leftTransparent || cleftTransparent)
            visibleQuads.insert(std::move(visibleQuadData(rx, ry, rz, Geometry::LEFT)));
        if(bottomTransparent || cbottomTransparent)
            visibleQuads.insert(std::move(visibleQuadData(rx, ry, rz, Geometry::BOTTOM)));
        if(frontTransparent || cfrontTransparent)
            visibleQuads.insert(std::move(visibleQuadData(rx, ry, rz, Geometry::FRONT)));
        if(rightTransparent || crightTransparent)
            visibleQuads.insert(std::move(visibleQuadData(rx, ry, rz, Geometry::RIGHT)));
        if(topTransparent || ctopTransparent)
            visibleQuads.insert(std::move(visibleQuadData(rx, ry, rz, Geometry::TOP)));
        if(backTransparent || cbackTransparent)
            visibleQuads.insert(std::move(visibleQuadData(rx, ry, rz, Geometry::BACK))); 
    }

    void Chunk::updateBlockVisibility(uint16_t x, uint16_t y, uint16_t z) {
        removeFacesAt(x, y, z); 
        addFacesAt(x, y, z);
    }

    void Chunk::findVisible() {
        if(isDirty == false)
            std::clog << "NOTE: calling findVisible on a chunk that isn't marked as dirty. Continuing anyways." << std::endl;

        // iterate through all blocks to cull invisible ones
        for(size_t x = 0; x < CHUNK_SIZE; x++)
        for(size_t y = 0; y < CHUNK_SIZE; y++)
        for(size_t z = 0; z < CHUNK_SIZE; z++) {
            addFacesAt(x, y, z);
        }
        
        // finally, move vq into visibleQuads and mark the chunk as not dirty 
        std::cout << "finished culling invisible quads. set size: " << visibleQuads.size() << std::endl;

        isDirty = false;
    }

    void Chunk::fill(const Material& mat) {
        for(size_t x = 0; x < CHUNK_SIZE; x++)
        for(size_t y = 0; y < CHUNK_SIZE; y++)
        for(size_t z = 0; z < CHUNK_SIZE; z++)
            volume[x][y][z].mat = mat;
    
        findVisible();
    }
}

