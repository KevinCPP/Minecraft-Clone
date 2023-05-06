#include "Shader.h"

Shader::Shader(const std::string& filePath) {
    m_fileName = filePath;

    shaderProgramSource source = parseShader(filePath);
    m_RendererID = createShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader() {
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::bind() const {
    GLCall(glUseProgram(m_RendererID));
}

void Shader::unbind() const {
    GLCall(glUseProgram(0));
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4& mat) {
    GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}

void Shader::setUniform1i(const std::string& name, int v0) {
    GLCall(glUniform1i(getUniformLocation(name), v0));
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

int Shader::getUniformLocation(const std::string& name) {
    
    if(m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) {
        return m_uniformLocationCache[name];
    }

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if(location == -1)
        std::cerr << "Warning: uniform " << name << " doesn't exist!" << std::endl;
    
    
    m_uniformLocationCache[name] = location;
    return location;
}


shaderProgramSource Shader::parseShader(const std::string& filepath) {
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line)) {
        if(line.find("#shader") != std::string::npos) {
            if(line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else if(line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        } else {
            ss[(int)type] << line << '\n';
        }
    }
    
    return { ss[0].str(), ss[1].str() };
}



unsigned int Shader::compileShader(const std::string& source, unsigned int type) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        
        std::cout << "Failed to compile shader" << std::endl;
        if(type == GL_VERTEX_SHADER) {
            std::cout << "Type: vertex\n";
        }
        
        if(type == GL_FRAGMENT_SHADER) {
            std::cout << "Type: fragment\n";
        }

        glDeleteShader(id);
        return 0;
    }

    return id;
}



// the strings will be the actual source code for the shaders
unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
    // randomly returns an unsigned int instead of accepting a reference as parameter
    unsigned int program = glCreateProgram();
    
    unsigned int vs = compileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

