#ifndef CUBEFACTORY_H
#define CUBEFACTORY_H

#include "Cube.h"
#include "Block.h"
#include "TextureArray.h"

namespace Blocks {


    class CubeFactory {
    public:
          
        static CubeFactory& getInstance() {
            static CubeFactory instance;
            return instance;
        }

        Geometry::Cube* getMaterialCube(const Material& mat);
        Geometry::Cube makeMaterialCube(const Material& mat);

    private:
        TextureArray* texArray;

        CubeFactory();
        ~CubeFactory();
        CubeFactory(const CubeFactory&) = delete;
        CubeFactory& operator=(const CubeFactory&) = delete;

        Geometry::Cube cubes[NUM_MATERIALS];
    };

}

#endif
