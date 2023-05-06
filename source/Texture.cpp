#include "Texture.h"

#include "../include/stb_image.h"

Texture::Texture(const std::string& path) {
    m_FilePath = path;
    m_LocalBuffer = nullptr;
    m_Width = 0;
    m_Height = 0;
    m_BPP = 0;
    m_RendererID = 0;

    // flips the texture vertically, since OpenGL expects pixels to
    // start at the bottom left, not top left.
    stbi_set_flip_vertically_on_load(1);

    m_LocalBuffer = stbi_load(path.data(), &m_Width, &m_Height, &m_BPP, 0);
    if(!m_LocalBuffer){
        std::cout << "error loading texture" << std::endl;
    }

    GLCall(glGenTextures(1, &m_RendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    //_S will stretch, _T will tile
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if(m_LocalBuffer)
        stbi_image_free(m_LocalBuffer); 
}

Texture::~Texture() {
    GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::bind(unsigned int slot) const {
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::unbind() const {
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
