
// project headers
#include "Quad.h"


Quad::Quad(std::initializer_list<Vertex<VERTEX_SIZE>> list) {
    if(list.size() == 4) {
        auto it = list.begin();
        for(size_t i = 0; i < 4 && it != list.end(); ++i, ++it) {
            vertices[i] = *it;
        }
    }
}

void Quad::setTextureCoordsFromAtlas(TextureAtlas* a, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    vertices[0].setTexCoords(a->getTextureCoords(x, y + height));
    vertices[1].setTexCoords(a->getTextureCoords(x, y));
    vertices[2].setTexCoords(a->getTextureCoords(x + width, y + height));
    vertices[3].setTexCoords(a->getTextureCoords(x + width, y));
}

std::array<unsigned int, 6> getIndices() {
    return {0, 1, 2, 2, 1, 3};
}
