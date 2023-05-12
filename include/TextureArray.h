#ifndef TEXTUREARRAY_H
#define TEXTUREARRAY_H

#include <GL/glew.h>

#include "Macros.h"

class TextureArray {
public:
    TextureArray();
    ~TextureArray();

    TextureArray(const TextureArray&) = delete;
    TextureArray& operator=(const TextureArray&) = delete;

    void bind(uint8_t slot);
    void unbind();

    bool loadTextures(const std::string& directory, GLenum format = GL_RGBA);

    unsigned int getID() const { return m_TextureID; }
    unsigned int getWidth() const { return m_Width; }
    unsigned int getHeight() const { return m_Height; }

private:
    unsigned int m_TextureID;
    int m_Width, m_Height, m_BPP;
};

#endif
