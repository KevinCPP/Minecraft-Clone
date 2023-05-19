#include "../include/CubeFactory.h"
#include "../include/Settings.h"

namespace Blocks {
    
    // initializes all of the cube types
    CubeFactory::CubeFactory() {
        using namespace Settings;
        texArray = new TextureArray();
        texArray->loadTextures(Settings::TEXTURE_DIRECTORY); 
         
        cubes[STONE]      .setAllTextureArrayIndex(       (float)texArray->getIndex("stone.bmp"               ));
        
//        cubes[DEV]        .setTopTextureArrayIndex(       (float)texArray->getIndex("test_top.bmp"            ));
//        cubes[DEV]        .setLeftTextureArrayIndex(      (float)texArray->getIndex("test_left.bmp"           ));
//        cubes[DEV]        .setBackTextureArrayIndex(      (float)texArray->getIndex("test_back.bmp"           ));
//        cubes[DEV]        .setFrontTextureArrayIndex(     (float)texArray->getIndex("test_front.bmp"          ));
//        cubes[DEV]        .setRightTextureArrayIndex(     (float)texArray->getIndex("test_right.bmp"          ));
//        cubes[DEV]        .setBottomTextureArrayIndex(    (float)texArray->getIndex("test_bottom.bmp"         ));

        cubes[COBBLESTONE].setAllTextureArrayIndex(       (float)texArray->getIndex("cobblestone.bmp"         ));
        cubes[DIRT]       .setAllTextureArrayIndex(       (float)texArray->getIndex("dirt.bmp"                ));
        cubes[GRASS_BLOCK].setTopTextureArrayIndex(       (float)texArray->getIndex("grass_block_top.bmp"     ));
        cubes[GRASS_BLOCK].setSidesTextureArrayIndex(     (float)texArray->getIndex("grass_block_sides.bmp"   ));
        cubes[GRASS_BLOCK].setBottomTextureArrayIndex(    (float)texArray->getIndex("dirt.bmp"                ));
        cubes[SAND]       .setAllTextureArrayIndex(       (float)texArray->getIndex("sand.bmp"                ));
        cubes[GRAVEL]     .setAllTextureArrayIndex(       (float)texArray->getIndex("gravel.bmp"              ));
        cubes[LOG]        .setSidesTextureArrayIndex(     (float)texArray->getIndex("log_sides.bmp"           ));
        cubes[LOG]        .setTopBottomTextureArrayIndex( (float)texArray->getIndex("log_top_bottom.bmp"      ));
        cubes[LEAVES]     .setAllTextureArrayIndex(       (float)texArray->getIndex("leaves.bmp"              ));
        cubes[PLANKS]     .setAllTextureArrayIndex(       (float)texArray->getIndex("planks.bmp"              ));
        cubes[BRICKS]     .setAllTextureArrayIndex(       (float)texArray->getIndex("bricks.bmp"              ));
        cubes[OBSIDIAN]   .setAllTextureArrayIndex(       (float)texArray->getIndex("obsidian.bmp"            ));
        cubes[WATER]      .setAllTextureArrayIndex(       (float)texArray->getIndex("water.bmp"               ));
        cubes[GLASS]      .setAllTextureArrayIndex(       (float)texArray->getIndex("glass.bmp"               ));
    }
    
    CubeFactory::~CubeFactory() {
        delete texArray; // since this is a singleton, could just leave this out
    }
    
    // returns a cube if it is a valid cube
    std::optional<Geometry::Cube> CubeFactory::makeMaterialCube(const Material& mat) {
        if(mat >= NUM_MATERIALS) return std::nullopt;
        
        std::optional<Geometry::Cube> tempCube = Geometry::Cube(cubes[mat]);

        return tempCube;
    }

}
