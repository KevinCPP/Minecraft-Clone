#ifndef TEST_H
#define TEST_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <cstdio>

#include "../vendor/fastnoiselite.h"

#include "../include/Cube.h"
#include "../include/Quad.h"
#include "../include/Chunk.h"
#include "../include/Vertex.h"
#include "../include/Camera.h"
#include "../include/Region.h"
#include "../include/Texture.h"
#include "../include/Settings.h"
#include "../include/Renderer.h"
#include "../include/IndexBuffer.h"
#include "../include/VertexArray.h"
#include "../include/TextureAtlas.h"
#include "../include/VertexBuffer.h"
#include "../include/VertexBufferLayout.h"

void testQuads();
void testChunk(std::vector<float>& vertexSrc, std::vector<unsigned int>& indexSrc, int offsetX = 0, int offsetZ = 0);
void testCubeHeight(TextureArray* texArray, std::vector<float>& vertexSrc, std::vector<unsigned int>& indexSrc);

#endif
