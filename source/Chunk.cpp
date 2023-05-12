#include "Chunk.h"

using namespace Blocks;

Chunk::Chunk() {

    volume = new Block**[sizex];
    for(size_t x = 0; x < sizex; x++) {
        volume[x] = new Block*[sizey];
        for(size_t y = 0; y < sizey; y++) {
            volume[x][y] = new Block[sizez];
            for(size_t z = 0; z < sizez; z++) {
                if(y < sizey - 8)
                    volume[x][y][z].mat = STONE;
                else if(y < sizey - 1)
                    volume[x][y][z].mat = DIRT;
                else
                    volume[x][y][z].mat = GRASS_BLOCK;
            }
        }
    }
}

std::tuple<std::vector<float>, std::vector<unsigned int>> Chunk::getFloatsAndIndices() {

    std::vector<float> cubes;
    std::vector<unsigned int> indices;

    size_t currentCube = 0;

    // Iterate over each block
    for (size_t x = 0; x < sizex; x++) {
        for (size_t y = 0; y < sizey; y++) {
            for (size_t z = 0; z < sizez; z++) {
                bool visible = false;
                const Block& currentBlock = volume[x][y][z];

                // Check if block is visible
                if (x == 0 || x == sizex - 1 ||
                    y == 0 || y == sizey - 1 ||
                    z == 0 || z == sizez - 1) {
                    visible = true;
                }

                if(visible) {
                    Geometry::Cube c = CubeFactory::getInstance().makeMaterialCube(currentBlock.mat);
                    c.setPosition(x, y, z);
                    c.setNormalizedDeviceCoordinates(128);
                    
                    auto floats = c.floats();
                    for(size_t i = 0; i < std::get<1>(floats); i++)
                        cubes.push_back(std::get<0>(floats)[i]);

                    for(unsigned int i : Geometry::Cube::indices)
                        indices.push_back(i + (24 * currentCube));

                    currentCube++;
                }
            }
        }
    } 

    return std::make_tuple(cubes, indices);
}
