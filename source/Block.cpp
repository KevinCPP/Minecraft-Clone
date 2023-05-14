#include "../include/Block.h"
#include "../include/CubeFactory.h"

namespace Blocks {
    
    using namespace Geometry;
    
    Block::Block(Material material, Direction direction) {
        mat = material;
        dir = direction;
    }

    Block::Block(const Block& other) {
        memcpy(this, &other, sizeof(Block));
    }

    Block& Block::operator=(const Block& other) {
        if(this != &other)
            memcpy(this, &other, sizeof(Block));
        
        return *this;
    }

    std::optional<Cube> Block::getCube(float x, float y, float z) {
        std::optional<Cube> c = CubeFactory::getInstance().makeMaterialCube(mat);
        
        if(c.has_value())
            c.value().setPosition(x, y, z);

        return c;
    }
}
