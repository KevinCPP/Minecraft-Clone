#include "../include/Block.h"
#include "../include/Utility.h"
#include "../include/CubeFactory.h"

namespace Blocks {
    
    // iterates through the transparent materials and returns true if mat is transparent
    bool isTransparent(const Material& mat) {
        for(auto& m : TRANSPARENT_MATERIALS_ARRAY)
            if(mat == m)
                return true;

        return false;
    }

    // creates a new block from a material and direction. parameters are optional, defaults to AIR
    Block::Block(Material material, Geometry::Direction direction) {
        if(Utility::warn(material > NUM_MATERIALS, "attempted to make a block with an unknown material. defaulting to AIR.")) {
            material = AIR;
        }

        mat = material;
        dir = direction;
    }
    
    // copy constructor. uses memcpy since a Block just contains primitives. Chose this because
    // memcpy is a low level/fast operation, and I can guarantee that it will always be a valid approach
    // for copying one block to another, since blocks will never contain anything other than primitive data
    Block::Block(const Block& other) {
        memcpy(this, &other, sizeof(Block));
    }
    
    // same concept as the copy constructor
    Block& Block::operator=(const Block& other) {
        if(this != &other)
            memcpy(this, &other, sizeof(Block));
        
        return *this;
    }
    
    // returns a cube at the specified position
    std::optional<Geometry::Cube> Block::getCube(float x, float y, float z) { 
        std::optional<Geometry::Cube> c = CubeFactory::getInstance().makeMaterialCube(mat);
        
        if(c.has_value())
            c.value().setPosition(glm::vec3(x, y, z));

        return c;
    }
}
