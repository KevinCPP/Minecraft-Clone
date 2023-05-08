#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H

#include "Texture.h"

class TextureAtlas {
private:
    Texture texAtlas;
    unsigned int numCols, numRows;

public:
    TextureAtlas(const std::string& filePath);
    ~TextureAtlas();

    glm::vec2 getTextureCoords(unsigned int x, unsigned int y) const; 
};

#endif
