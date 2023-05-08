#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H

#include "Texture.h"

#include <glm/glm.hpp>

class TextureAtlas {
private: 
    // member variables
    Texture texAtlas;                   // stores the actual image that will be used as the atlas
    unsigned int numCols, numRows;      // stores how many columns and rows of individual textures are in the atlas
public:
    // default constructor (will initialize member variables to defaults)
    TextureAtlas();

    // constructor (sets member variables, sets up texture atlas image, binds it to slot 0)
    TextureAtlas(const std::string& filePath, unsigned int cols, unsigned int rows);

    // destructor (unbinds the texture atlas image from slot 0
    ~TextureAtlas();

    // sets up member variables, sets up texture atlas image, binds it to slot 0
    void setTextureAtlasImage(const std::string& filePath, unsigned int cols, unsigned int rows);

    // get texture coordinates of the texture at (x, y) in the atlas
    glm::vec2 getTextureCoords(unsigned int x, unsigned int y) const; 
};

#endif
