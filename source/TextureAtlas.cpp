#include "../include/TextureAtlas.h"

TextureAtlas::TextureAtlas(const std::string& filePath, unsigned int cols, unsigned int rows) {
    numCols = cols;
    numRows = rows;
    texAtlas = Texture(filePath);
    texAtlas.bind(0);
}

TextureAtlas::~TextureAtlas() {
    texAtlas.unbind();
}

glm::vec2 TextureAtlas::getTextureCoords(unsigned int x, unsigned int y) const {
    glm::vec2 coords(0.0f, 0.0f);

    if(x < numCols && y < numRows) {
        coords.x = (1.0f/numCols) * x;
        coords.y = (1.0f/numRows) * y;
    }

    return Coords;
}
