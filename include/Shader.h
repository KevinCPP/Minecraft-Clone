#ifndef SHADER_H
#define SHADER_H

#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glm/glm.hpp>

#include "Macros.h"

struct shaderProgramSource {
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader {
private:
    std::string m_fileName;
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_uniformLocationCache;

    unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
    unsigned int compileShader(const std::string& source, unsigned int type);
    int getUniformLocation(const std::string& name);
   
    shaderProgramSource parseShader(const std::string& filepath);    

public:
    // constructor
    Shader(const std::string& filePath);
    // destructor
    ~Shader();

    void bind() const;
    void unbind() const;

    void setUniformMat4f(const std::string& name, const glm::mat4& mat);
    void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void setUniform1i(const std::string& name, int v0);
};

#endif

