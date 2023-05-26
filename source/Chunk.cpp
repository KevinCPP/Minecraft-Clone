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
        
        // when a chunk is first generated, it is full of air.
        // That means it won't be rendered, and since the VBO is
        // initially empty, that means it is not dirty.
        isDirty = false;
    } 
    
    // constructor that also initializes adjacent chunks
    Chunk::Chunk(Chunk* top, Chunk* left, Chunk* back, Chunk* right, Chunk* front, Chunk* bottom) {
        isDirty = false;
        setAdjacentChunks(top, left, back, right, front, bottom); 
    }
    
    // returns true if x, y, and z are inside the bounds of the chunk (less than CHUNK_SIZE)
    bool Chunk::isInsideChunkSize(uint16_t x, uint16_t y, uint16_t z) const {
        return (x < CHUNK_SIZE && y < CHUNK_SIZE && z < CHUNK_SIZE); 
    }
   
    // gets the material of a block at a specific location
    Blocks::Material Chunk::getBlockMaterial(uint16_t x, uint16_t y, uint16_t z) const {
        if(!isInsideChunkSize(x, y, z))
            return Blocks::AIR;

        return volume[x][y][z].mat;
    }
    
    // returns a copy of the block at a specific location
    Blocks::Block Chunk::copyBlock(uint16_t x, uint16_t y, uint16_t z) const {
        if(!isInsideChunkSize(x, y, z))
            return Blocks::Block(Blocks::AIR);

        return volume[x][y][z];
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
   
    // pretty much the only function that marks it as dirty
    bool Chunk::setBlockRaw(uint16_t x, uint16_t y, uint16_t z, const Blocks::Block& b) {
        if(!isInsideChunkSize(x, y, z))
            return false;
        
        isDirty = true;
        volume[x][y][z] = b;
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
        
        // material of the block at x, y ,z
        Blocks::Material cm = volume[x][y][z].mat;
         
        // if x, y, z is not transparent, that means it is solid. Therefore, the adjacent quads are occluded
        // This if statement will handle all quads that are inside this chunk and are adjacent to the solid block
        if(!Blocks::isTransparent(cm)) {
            if(x != 0)
                visibleQuads.erase(Geometry::QuadLocation(x-1, y, z, Geometry::RIGHT));
            if(y != 0)
                visibleQuads.erase(Geometry::QuadLocation(x, y-1, z, Geometry::TOP));
            if(z != 0)
                visibleQuads.erase(Geometry::QuadLocation(x, y, z-1, Geometry::BACK));
            if(x != CHUNK_SIZE - 1)
                visibleQuads.erase(Geometry::QuadLocation(x+1, y, z, Geometry::LEFT));
            if(y != CHUNK_SIZE - 1)
                visibleQuads.erase(Geometry::QuadLocation(x, y+1, z, Geometry::BOTTOM));
            if(z != CHUNK_SIZE - 1)
                visibleQuads.erase(Geometry::QuadLocation(x, y, z+1, Geometry::FRONT));
        } else if (cm == Blocks::AIR) {
            visibleQuads.erase(Geometry::QuadLocation(x, y, z, Geometry::TOP));
            visibleQuads.erase(Geometry::QuadLocation(x, y, z, Geometry::LEFT));
            visibleQuads.erase(Geometry::QuadLocation(x, y, z, Geometry::BACK));
            visibleQuads.erase(Geometry::QuadLocation(x, y, z, Geometry::RIGHT));
            visibleQuads.erase(Geometry::QuadLocation(x, y, z, Geometry::FRONT));
            visibleQuads.erase(Geometry::QuadLocation(x, y, z, Geometry::BOTTOM));
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
            visibleQuads.erase(Geometry::QuadLocation(x, y, z, Geometry::LEFT));
        if((y == 0) && !cbottomTransparent)
            visibleQuads.erase(Geometry::QuadLocation(x, y, z, Geometry::BOTTOM));
        if((z == 0) && !cfrontTransparent)
            visibleQuads.erase(Geometry::QuadLocation(x, y, z, Geometry::FRONT));
        if((x == CHUNK_SIZE - 1) && !crightTransparent)
            visibleQuads.erase(Geometry::QuadLocation(x, y, z, Geometry::RIGHT));
        if((y == CHUNK_SIZE - 1) && !ctopTransparent) 
            visibleQuads.erase(Geometry::QuadLocation(x, y, z, Geometry::TOP));
        if((z == CHUNK_SIZE - 1) && !cbackTransparent)
            visibleQuads.erase(Geometry::QuadLocation(x, y, z, Geometry::BACK));
    }

    void Chunk::addFacesAt(uint16_t x, uint16_t y, uint16_t z) {
        Blocks::Material cm = volume[x][y][z].mat;
        
        // first, if this block is transparent, add all faces that are facing it since those would all be visible
        if(Blocks::isTransparent(cm)) {
            // we'll deal with edges later, for now, just check the adjacent block in this chunk
            // and add it's corresponding face if it isn't AIR.
            if(x != 0 && volume[x-1][y][z].mat != AIR)
                visibleQuads.insert(std::move(Geometry::QuadLocation(x-1, y, z, Geometry::RIGHT)));
            if(y != 0 && volume[x][y-1][z].mat != AIR)
                visibleQuads.insert(std::move(Geometry::QuadLocation(x, y-1, z, Geometry::TOP)));
            if(z != 0 && volume[x][y][z-1].mat != AIR)
                visibleQuads.insert(std::move(Geometry::QuadLocation(x, y, z-1, Geometry::BACK)));
            if(x != CHUNK_SIZE - 1 && volume[x+1][y][z].mat != AIR)
                visibleQuads.insert(std::move(Geometry::QuadLocation(x+1, y, z, Geometry::LEFT)));
            if(y != CHUNK_SIZE - 1 && volume[x][y+1][z].mat != AIR)
                visibleQuads.insert(std::move(Geometry::QuadLocation(x, y+1, z, Geometry::BOTTOM)));
            if(z != CHUNK_SIZE - 1 && volume[x][y][z+1].mat != AIR)
                visibleQuads.insert(std::move(Geometry::QuadLocation(x, y, z+1, Geometry::FRONT)));
            
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
            visibleQuads.insert(std::move(Geometry::QuadLocation(x, y, z, Geometry::LEFT)));
        if(bottomTransparent || cbottomTransparent)
            visibleQuads.insert(std::move(Geometry::QuadLocation(x, y, z, Geometry::BOTTOM)));
        if(frontTransparent || cfrontTransparent)
            visibleQuads.insert(std::move(Geometry::QuadLocation(x, y, z, Geometry::FRONT)));
        if(rightTransparent || crightTransparent)
            visibleQuads.insert(std::move(Geometry::QuadLocation(x, y, z, Geometry::RIGHT)));
        if(topTransparent || ctopTransparent)
            visibleQuads.insert(std::move(Geometry::QuadLocation(x, y, z, Geometry::TOP)));
        if(backTransparent || cbackTransparent)
            visibleQuads.insert(std::move(Geometry::QuadLocation(x, y, z, Geometry::BACK))); 
    }

    void Chunk::updateBlockVisibility(uint16_t x, uint16_t y, uint16_t z) {
        removeFacesAt(x, y, z); 
        addFacesAt(x, y, z);
        generateRendererInfo();
    }

    void Chunk::findVisible() {
        visibleQuads.clear();
        // iterate through all blocks to cull invisible ones
        for(size_t x = 0; x < CHUNK_SIZE; x++)
        for(size_t y = 0; y < CHUNK_SIZE; y++)
        for(size_t z = 0; z < CHUNK_SIZE; z++) {
            // if we clear the set, only this function is needed since there
            // won't be any blocks that need removing, since we'll be adding
            // all the visible faces in for the first time.
            addFacesAt(x, y, z);
        }
    }

    void Chunk::fill(const Material& mat) {
        // fill the chunk with a specific block
        for(size_t x = 0; x < CHUNK_SIZE; x++)
        for(size_t y = 0; y < CHUNK_SIZE; y++)
        for(size_t z = 0; z < CHUNK_SIZE; z++)
            volume[x][y][z].mat = mat;
        
        // run findVisible
        findVisible();
    }

    void Chunk::generateRendererInfo() {
        // need to check this because if there are no visible quads and we try to make a VAO/VBO/IBO,
        // we can get an OpenGL error since it expects a VBO to contain an amount of data greater than 0.
        if(visibleQuads.size() == 0) {
            return;
        }

        // initialize vectors to store the data, and pre-allocate the correct amount of memory
        // to avoid unnecessary reallocation operations
        std::vector<float> vertexData(visibleQuads.size() * Geometry::FLOATS_PER_QUAD);
        std::vector<unsigned int> indexData(visibleQuads.size() * Geometry::Quad::indices.size());
        vertexData.clear();
        indexData.clear();

        // initialize variables to be used in the loop, so they don't have to
        // be unnecessarily re-created each time, simply assigned.
        Blocks::Material mat;
        std::optional<Geometry::Cube> thisCube;
        Quad thisQuad;

        // iterate through all of the visible quad data
        for(auto& vqd : visibleQuads) {
            mat = getBlockMaterial(vqd.x, vqd.y, vqd.z);
            thisCube = Blocks::Block(mat).getCube(vqd.x, vqd.y, vqd.z);
            
            if(Utility::error(!thisCube.has_value(), "Got a \"Visible Quad\" which is AIR!")) {
                continue;
            }
            
            thisQuad = thisCube->copyQuad((Geometry::Direction)vqd.face);

            float* ptr = (float*)(&thisQuad);
            std::copy(ptr, ptr + Geometry::FLOATS_PER_QUAD, std::back_inserter(vertexData));
        }
        
        // fill the indexData vector with the proper index data
        Geometry::makeIndicesFromQuads(visibleQuads.size(), indexData);         
        
        // if the vao has not been initialized
        if(!vao) {
            // create the vao
            vao = std::make_unique<VertexArray>();
            // get the vertex buffer layout
            VertexBufferLayout layout = Geometry::makeVertexLayout();
            
            // generate the vbo and ibo
            vbo = std::make_unique<VertexBuffer>(vertexData.data(), vertexData.size() * sizeof(float)); 
            ibo = std::make_unique<IndexBuffer>(indexData.data(), indexData.size());
            
            // bind the vbo and layout to the vao
            vao->addBuffer(*vbo, layout);
            // unbind the vao
            vao->unbind();
        }
        else {
            // if the VAO has already been initialized, we just need to
            // substitute new data into the vbo and ibo.
            vbo->subData(vertexData.data(), vertexData.size() * sizeof(float));
            ibo->subData(indexData.data(), indexData.size());
        }
    }
    
    // the chunk maintains it's own IBO and VAO, so it just needs a renderer
    // and a shader to use for rendering. This function simply renders the chunk's
    // associated vertex data
    void Chunk::render(const Renderer& renderer, Shader& shader, glm::vec3 offset) {
        // if it's dirty, find the visible quads and generate renderer info
        if(isDirty) {
            findVisible();
            generateRendererInfo();
            isDirty = false;
        }
        // if these don't exist, we can't render (the chunk is probably empty)
        // so simply return without doing anything
        if(!vao || !vbo || !ibo) {
            return;
        }

        shader.setUniform4f("uOffset", offset.x * CHUNK_SIZE, offset.y * CHUNK_SIZE, offset.z * CHUNK_SIZE, 0.0f);
        
        // draw the chunk
        renderer.draw(*vao, *ibo, shader); 
    }
}

