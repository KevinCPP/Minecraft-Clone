#include "../include/Block.h"
#include "../include/Utility.h"
#include "../include/CubeFactory.h"

namespace Blocks {

    bool isTransparent(const Material& mat) {
        for(auto& m : TRANSPARENT_MATERIALS_ARRAY)
            if(mat == m)
                return true;

        return false;
    }

    Block::Block(Material material, Geometry::Direction direction) {
        if(Utility::warn(material > NUM_MATERIALS, "attempted to make a block with an unknown material. defaulting to AIR.")) {
            material = AIR;
        }

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

    std::optional<Geometry::Cube> Block::getCube(float x, float y, float z) { 
        std::optional<Geometry::Cube> c = CubeFactory::getInstance().makeMaterialCube(mat);
        
        if(c.has_value())
            c.value().setPosition(x, y, z);

        return c;
    }
}