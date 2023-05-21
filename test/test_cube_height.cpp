#include "test.h"
#include "../include/Parallelepiped.h"

void testCubeHeight(TextureArray* texArray, std::vector<float>& vertexSrc, std::vector<unsigned int>& indexSrc) {
    using namespace Blocks;
    using namespace Geometry;
    
    texArray->loadTextures(Settings::TEXTURE_DIRECTORY);

    Parallelepiped p;
    p.setTextureArrayIndex(TOP, texArray->getIndex("test_top.bmp"));
    p.setTextureArrayIndex(LEFT, texArray->getIndex("test_left.bmp"));
    p.setTextureArrayIndex(BACK, texArray->getIndex("test_back.bmp"));
    p.setTextureArrayIndex(RIGHT, texArray->getIndex("test_right.bmp"));
    p.setTextureArrayIndex(FRONT, texArray->getIndex("test_front.bmp"));
    p.setTextureArrayIndex(BOTTOM, texArray->getIndex("test_bottom.bmp"));
    p.setDimensions(glm::vec3(1.0, 0.5, 1.0));

    for(auto& q : p.m_Quads) {
        Quad quad = q;
        float* ptr = (float*)(&quad);
        std::copy(ptr, ptr + FLOATS_PER_QUAD, std::back_inserter(vertexSrc));
    }

    makeIndicesFromQuads(6, indexSrc);

    std::cout << vertexSrc.size() << " " << indexSrc.size() << std::endl;
}
