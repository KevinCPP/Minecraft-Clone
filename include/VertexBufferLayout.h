#ifndef VERTEXBUFFERLAYOUT
#define VERTEXBUFFERLAYOUT

#include <GL/glew.h>
#include <vector>

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    bool normalized;

    static unsigned int getTypeSize(unsigned int type){
        switch(type) {
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_INT:   return 4;
            case GL_UNSIGNED_BYTE:  return 1;
        }
        return 0;
    }

};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
public:
    
    VertexBufferLayout() : m_Stride(0) {}

    template<typename T>
    void push(int count) {
        
    }

    void push_float(unsigned int count) {
        m_Elements.push_back( {GL_FLOAT, count, false} );
        m_Stride += sizeof(GLfloat) * count;
    }

    void push_uint(unsigned int count) {
        m_Elements.push_back( {GL_UNSIGNED_INT, count, true} );
        m_Stride += sizeof(GLuint) * count;
    }

    void push_byte(unsigned int count) {
        m_Elements.push_back( {GL_UNSIGNED_BYTE, count, true} );
        m_Stride += sizeof(GLbyte) * count;
    }

    inline unsigned int getStride() const { return m_Stride; }
    inline const std::vector<VertexBufferElement> getElements() const { return m_Elements; }
};

#endif
