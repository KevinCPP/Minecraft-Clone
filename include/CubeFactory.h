#ifndef CUBEFACTORY_H
#define CUBEFACTORY_H

#include "Cube.h"
#include "Block.h"
#include "TextureAtlas.h"

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
        TextureAtlas* atlas;
        
        CubeFactory();
        ~CubeFactory();
        CubeFactory(const Material&) = delete;
        CubeFactory& operator=(const Material&) = delete;

        static constexpr size_t enumSize = AIR;

        Geometry::Cube cubes[enumSize];
    };

}

#endif
