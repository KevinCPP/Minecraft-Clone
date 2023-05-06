#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Shader.h"

class Renderer {
private:

public:
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

    void clear() const;
};

#endif
