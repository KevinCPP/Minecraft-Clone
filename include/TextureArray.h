#ifndef TEXTUREARRAY_H
#define TEXTUREARRAY_H

#include <GL/glew.h>

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
    unsigned int getWidth() const { return m_width; }
    unsigned int getHeight() const { return m_height; }

private:
    unsigned int m_TextureID;
    unsigned int m_Width, m_Height, m_BPP;
}

#endif
