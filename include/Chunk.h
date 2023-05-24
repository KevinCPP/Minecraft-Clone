#ifndef CHUNK_H
#define CHUNK_H

#include "Quad.h"
#include "World.h"
#include "Block.h"
#include "Shader.h"
#include "Location.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include <vector>
#include <optional>
#include <ankerl/unordered_dense.h>

namespace World {
    
    class Chunk {
    private:
        // stores the blocks in the chunk
        Blocks::Block volume[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
        
        // store a list of all the available quads in a chunk
        ankerl::unordered_dense::set<Geometry::QuadLocation, Geometry::QuadLocation_hash_avalanching> visibleQuads;
        
        // stores the renderer data to be used to render this chunk
        std::unique_ptr<VertexBuffer> vbo;
        std::unique_ptr<IndexBuffer> ibo;
        std::unique_ptr<VertexArray> vao;

        // store pointers to adjacent chunks
        Chunk* adjTop;
        Chunk* adjLeft;
        Chunk* adjBack;
        Chunk* adjRight;
        Chunk* adjFront;
        Chunk* adjBottom;
        
        bool isDirty;

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
        
        // sets a block, but does not call updateBlockVisibility; rather, marks it as dirty.
        // This function is primarily for use in generating chunks where many blocks will be
        // manipulated to avoid calling updateBlockVisibility each time, but could also be tried
        // later with player interactions to see if it perfoms better.
        bool setBlockRaw(uint16_t x, uint16_t y, uint16_t z, const Blocks::Block& b);

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

        void generateRendererInfo(); 

        auto visibleQuadsBegin() const { return visibleQuads.begin(); }
        auto visibleQuadsEnd() const { return visibleQuads.end(); }
        
        void render(const Renderer& renderer, Shader& shader, glm::vec3 offset = glm::vec3(0.0f, 0.0f, 0.0f));
    };
}

#endif
