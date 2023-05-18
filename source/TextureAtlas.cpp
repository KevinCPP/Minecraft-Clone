#include "../include/TextureAtlas.h"
#include <iomanip>

const unsigned int DEFAULT_COLS = 1;
const unsigned int DEFAULT_ROWS = 1;
const std::string DEFAULT_TEXTURE_ATLAS_PATH = "resources/textures/atlas.bmp";

TextureAtlas::TextureAtlas() {
    setTextureAtlasImage(DEFAULT_TEXTURE_ATLAS_PATH, DEFAULT_COLS, DEFAULT_ROWS);
}

TextureAtlas::TextureAtlas(const std::string& filePath, unsigned int cols, unsigned int rows) {
    setTextureAtlasImage(filePath, cols, rows); 
}

TextureAtlas::~TextureAtlas() {
    texAtlas->unbind();
}

void TextureAtlas::setTextureAtlasImage(const std::string& filePath, unsigned int cols, unsigned int rows) {
    numCols = cols;
    numRows = rows;
    texAtlas = std::make_unique<Texture>(filePath);
    texAtlas->bind(0);

    if(numCols == 0) {
        std::cerr << "ERROR: Texture atlas initialized with 0 columns!" << std::endl;
        numCols = DEFAULT_COLS;
    }

    if(numRows == 0) {
        std::cerr << "ERROR: Texture atlas initialized with 0 rows!" << std::endl;
        numRows = DEFAULT_ROWS;
    }
}

glm::vec2 TextureAtlas::getTextureCoords(unsigned int x, unsigned int y) const {
    glm::vec2 coords(0.0f, 0.0f);

    if(x <= numCols && y <= numRows) {
        coords.x = (1.0f / numCols) * x;
        coords.y = (1.0f / numRows) * y;
    }

    return coords;
}
