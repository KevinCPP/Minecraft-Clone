#include "../include/CubeFactory.h"
#include "../include/Settings.h"

namespace Blocks {

    CubeFactory::CubeFactory() {
        using namespace Settings;
        atlas = new TextureAtlas(TEXTURE_ATLAS_FILE_PATH, TEXTURE_ATLAS_SIZE_X, TEXTURE_ATLAS_SIZE_Y);

        cubes[STONE]        .setAllTextureCoords        (atlas, 1, 3, 1, 1);
        cubes[COBBLESTONE]  .setAllTextureCoords        (atlas, 2, 3, 1, 1);
        cubes[DIRT]         .setAllTextureCoords        (atlas, 2, 2, 1, 1);
        cubes[GRASS_BLOCK]  .setTopTextureCoords        (atlas, 0, 2, 1, 1);
        cubes[GRASS_BLOCK]  .setSidesTextureCoords      (atlas, 1, 2, 1, 1);
        cubes[GRASS_BLOCK]  .setBottomTextureCoords     (atlas, 2, 2, 1, 1);
        cubes[SAND]         .setAllTextureCoords        (atlas, 3, 2, 1, 1);
        cubes[GRAVEL]       .setAllTextureCoords        (atlas, 3, 3, 1, 1);
        cubes[LOG]          .setSidesTextureCoords      (atlas, 0, 1, 1, 1);
        cubes[LOG]          .setTopBottomTextureCoords  (atlas, 1, 1, 1, 1);
        cubes[LEAVES]       .setAllTextureCoords        (atlas, 2, 1, 1, 1);
        cubes[PLANKS]       .setAllTextureCoords        (atlas, 3, 1, 1, 1);
        cubes[BRICKS]       .setAllTextureCoords        (atlas, 0, 0, 1, 1);
        cubes[OBSIDIAN]     .setAllTextureCoords        (atlas, 1, 0, 1, 1);
        cubes[WATER]        .setAllTextureCoords        (atlas, 2, 0, 1, 1);
        cubes[GLASS]        .setAllTextureCoords        (atlas, 3, 0, 1, 1);
    }

    CubeFactory::~CubeFactory() {
        delete atlas; // since this is a singleton, could just leave this out
    }

    Geometry::Cube* CubeFactory::getMaterialCube(const Material& mat) {
        if(mat >= NUM_MATERIALS) return nullptr;

        return &cubes[mat];
    }

    Geometry::Cube CubeFactory::makeMaterialCube(const Material& mat) {
        return Geometry::Cube(cubes[mat]);
    }

}
