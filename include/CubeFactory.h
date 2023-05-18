#ifndef CUBEFACTORY_H
#define CUBEFACTORY_H

#include <optional>

#include "Cube.h"
#include "Block.h"
#include "TextureArray.h"

namespace Blocks {

    // factory for creating a cube from a material.
    class CubeFactory {
    public:
         
        // is a singleton, only need one instance of this
        static CubeFactory& getInstance() {
            static CubeFactory instance;
            return instance;
        }
        
        // can make a copy of any cube.
        std::optional<Geometry::Cube> makeMaterialCube(const Material& mat);
    private:
        // manages all the textures for the different cubes
        TextureArray* texArray;

        CubeFactory();
        ~CubeFactory();
        CubeFactory(const CubeFactory&) = delete;
        CubeFactory& operator=(const CubeFactory&) = delete;
        
        // stores a list of all the cubes
        Geometry::Cube cubes[NUM_MATERIALS];
    };

}

#endif
