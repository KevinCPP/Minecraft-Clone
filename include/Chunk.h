#ifndef CHUNK_H
#define CHUNK_H

#include "Cube.h"
#include "World.h"
#include "Block.h"
#include "Settings.h"
#include "CubeFactory.h"

#include <vector>
#include <optional>
#include <ankerl/unordered_dense.h>

namespace World {
    
    // will store data about the visible quad, within the chunk
    struct visibleQuadData {
        int16_t x, y, z;
        uint8_t face;

        visibleQuadData(int16_t cx, int16_t cy, int16_t cz, Geometry::Direction dir) : x(cx), y(cy), z(cz), face((uint8_t)dir) { }
        visibleQuadData(int16_t cx, int16_t cy, int16_t cz, uint8_t dir) : x(cx), y(cy), z(cz), face(dir) { } 
        
        bool operator==(const visibleQuadData& other) const { return x == other.x && y == other.y && z == other.z && face == other.face; }
        
        void addOffset(int16_t ox, int16_t oy, int16_t oz) { x += ox; y += oy; z += oz; }
    };
    
    // hashing function implementation 
    struct vqd_hash_avalanching {
        using is_avalanching = void;

        auto operator()(const visibleQuadData& obj) const noexcept -> uint64_t {
            uint64_t result = 0;
            result ^= ankerl::unordered_dense::detail::wyhash::hash(obj.x);
            result ^= ankerl::unordered_dense::detail::wyhash::hash(obj.y);
            result ^= ankerl::unordered_dense::detail::wyhash::hash(obj.z);
            result ^= ankerl::unordered_dense::detail::wyhash::hash((uint8_t)obj.face);
            return result;
        }
    };

    class Chunk {
    private:
        // stores the blocks in the chunk
        Blocks::Block volume[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
        
        // store a list of all the available quads in a chunk
        ankerl::unordered_dense::set<visibleQuadData, vqd_hash_avalanching> visibleQuads;

        // store pointers to adjacent chunks
        Chunk* adjTop;
        Chunk* adjLeft;
        Chunk* adjBack;
        Chunk* adjRight;
        Chunk* adjFront;
        Chunk* adjBottom;
        
        // will add/remove faces from visibleQuads at x, y, and z. Should both be used when a block is modified.
        void addFacesAt(uint16_t x, uint16_t y, uint16_t z);
        void removeFacesAt(uint16_t x, uint16_t y, uint16_t z);
    public:
        // default constructor
        Chunk();
        
        // initializes adjacent chunks
        Chunk(Chunk* top, Chunk* left, Chunk* back, Chunk* right, Chunk* front, Chunk* bottom);

        // returns true if a set of x, y, and z values are within the bounds of 0, CHUNK_SIZE - 1
        bool isInsideChunkSize(uint16_t x, uint16_t y, uint16_t z) const;

        // returns the block material at x, y, z, or air if xyz are out of bounds
        Blocks::Material getBlockMaterial(uint16_t x, uint16_t y, uint16_t z) const;

        // returns a copy of the block at x, y, z
        Blocks::Block copyBlock(uint16_t x, uint16_t y, uint16_t z) const;

        // sets a block, relative to chunk coordinates. 
        bool setBlock(uint16_t x, uint16_t y, uint16_t z, const Blocks::Block& b);
        
        // effectively sets the block to AIR. 
        bool removeBlock(uint16_t x, uint16_t y, uint16_t z);
        
        // will check to see if a given block in the chunk is transparent
        bool isBlockTransparent(uint16_t x, uint16_t y, uint16_t z) const;

        // sets the adjacent chunk pointers
        void setAdjacentChunks(Chunk* top, Chunk* left, Chunk* back, Chunk* right, Chunk* front, Chunk* bottom);

        // updates the visibility at one specific block coordinate. Essentially findVisible() except on one block at x, y, z
        void updateBlockVisibility(uint16_t x, uint16_t y, uint16_t z);

        // iterates through all of the blocks in the chunk and fills the visibleQuads set with quads that have adjacent transparent blocks
        void findVisible();

        // fills the chunk with a given material
        void fill(const Blocks::Material& mat = Blocks::STONE);
    
        auto visibleQuadsBegin() const { return visibleQuads.begin(); }
        auto visibleQuadsEnd() const { return visibleQuads.end(); }
    };
}

#endif
