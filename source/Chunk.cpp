#include "../include/Chunk.h"
#include "../include/Settings.h"

using namespace Blocks;
using namespace Geometry;

namespace World {
    
    Chunk::Chunk() { }

    Chunk::Chunk(const Geometry::AxisAlignedBoundingBox& aabb) {
        AABB = aabb;
    }

    Chunk::Chunk(int64_t worldChunkX, int64_t worldChunkY, int64_t worldChunkZ) {
        chunkX = worldChunkX;
        chunkY = worldChunkY;
        chunkZ = worldChunkZ;
    }

    void Chunk::makeStone() {
        for(auto& row : volume) 
            for(auto& col : row)
                for(auto& block : col)
                    block = Block(STONE);
    }

    Block* Chunk::getBlock(uint16_t x, uint16_t y, uint16_t z) {
        if(x >= CHUNK_SIZE || y >= CHUNK_SIZE || z >= CHUNK_SIZE)
            return nullptr; 

        return &volume[x][y][z];
    }

    bool Chunk::setBlock(uint16_t x, uint16_t y, uint16_t z, const Block& b) {
        if(x >= CHUNK_SIZE || y >= CHUNK_SIZE || z >= CHUNK_SIZE)
            return false;

        volume[x][y][z] = b;
        return true;
    }
    
    bool Chunk::removeBlock(uint16_t x, uint16_t y, uint16_t z) {
        if(x >= CHUNK_SIZE || y >= CHUNK_SIZE || z >= CHUNK_SIZE)
            return false;

        volume[x][y][z].mat = Blocks::AIR;
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

    std::vector<Geometry::Quad*> Chunk::cullFacesUsingAABB(float CameraPosX, float CameraPosY, float CameraPosZ) {
        return std::move(cullFacesUsingAABB(glm::vec3(CameraPosX, CameraPosY, CameraPosZ)));
    }

    std::vector<Geometry::Quad*> Chunk::cullFacesUsingAABB(const glm::vec3& cameraPos) {
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

