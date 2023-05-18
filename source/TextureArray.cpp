#include <filesystem>
#include <iostream>
#include <vector>
#include <string>

#include "../include/TextureArray.h"
#include "../include/Settings.h"

#include "../vendor/stb_image.h"

TextureArray::TextureArray() {
    glGenTextures(1, &m_TextureID);
}

TextureArray::~TextureArray() {
    glDeleteTextures(1, &m_TextureID);
}

void TextureArray::bind(uint8_t slot) {
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, m_TextureID));
}

void TextureArray::unbind() {
    GLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, 0));
}

int TextureArray::getIndex(const std::string& fileName) const {
    auto it = indices.find(fileName);
    if(it != indices.end())
        return it->second;

    it = indices.find(Settings::TEXTURE_DIRECTORY + fileName);
    if(it != indices.end()) {
        std::cout << "file found: " << it->first << " array index: " << it->second << std::endl;
        return it->second;
    }
    std::cout << "FAILED TO GET: " << fileName << std::endl;
    std::cout << "List of available textures: " << std::endl;

    for(const auto& pair : indices) {
        std::cout << pair.first << " index: " << pair.second << '\n';
    }

    return -1;
}

bool TextureArray::loadTextures(const std::string& directory, GLenum format) {
    std::vector<std::string> files;
    for(const auto& entry : std::filesystem::directory_iterator(directory))
        files.push_back(entry.path().string());
    
    // flip the images vertically since OpenGL expects it to start at
    // bottom left, not top left.
    stbi_set_flip_vertically_on_load(1);

    int width, height, bpp;
    unsigned char* data = stbi_load(files[0].c_str(), &m_Width, &m_Height, &m_BPP, 0);

    if(!data) {
        std::cerr << "Failed to load texture file " << files[0] << std::endl;
        return false;
    }

    stbi_image_free(data);

    GLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, m_TextureID));
    GLCall(glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, format, m_Width, m_Height, files.size()));

    for(unsigned int i = 0; i < files.size(); i++) {
        data = stbi_load(files[i].c_str(), &width, &height, &bpp, 0);
        
        indices[files[i]] = i;
        if(!data) {
            std::cerr << "Failed to load texture file " << files[i] << std::endl;
            return false;
        }

        GLCall(glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, m_Width, m_Height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data));
        stbi_image_free(data);
    }

    GLCall(glEnable(GL_LINE_SMOOTH));

    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f));
    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glGenerateMipmap(GL_TEXTURE_2D_ARRAY));

    return true;
}
