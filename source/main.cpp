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
#include "../include/ChunkGenerator.h"

#include "../test/test.h"

using namespace Geometry;
using namespace Blocks;
using namespace World;

void getChunkData(World::Chunk* c, size_t chunkX, size_t chunkY, size_t chunkZ, std::vector<float>& vertexSrc, std::vector<unsigned int>& indexSrc) {
    size_t quadCount = 0;
    int offsetX = chunkX * 16;
    int offsetY = chunkY * 16;
    int offsetZ = chunkZ * 16;
    for(auto it = c->visibleQuadsBegin(); it != c->visibleQuadsEnd(); it++) {
        ++quadCount;

        Blocks::Material mat = c->getBlockMaterial(it->x, it->y, it->z);
        Cube thisCube = *Blocks::Block(mat).getCube(offsetX + it->x, offsetY + it->y, offsetZ + it->z);
        Quad quad = thisCube.copyQuad((Geometry::Direction)it->face);
        float* ptr = (float*)(&quad);
        std::copy(ptr, ptr + Geometry::FLOATS_PER_QUAD, std::back_inserter(vertexSrc));
    }

//    for(size_t x = 0; x < CHUNK_SIZE; x++)
//    for(size_t y = 0; y < CHUNK_SIZE; y++)
//    for(size_t z = 0; z < CHUNK_SIZE; z++) {
//        Blocks::Material mat = c->getBlockMaterial(x, y, z);
//        Cube thisCube = *Blocks::Block(mat).getCube(offsetX + x, offsetY + y, offsetZ + z);
//        
//        for(auto& q : thisCube.m_Quads) {
//            quadCount++;
//            float* ptr = (float*)(&q);
//            std::copy(ptr, ptr + Geometry::FLOATS_PER_QUAD, std::back_inserter(vertexSrc));
//        }
//    }
//
    makeIndicesFromQuads(quadCount, indexSrc);
}

int main() {
    // set up game default settings
    Settings::defaultSettings();

    // window object
    GLFWwindow *window;

    // initialize glfw, terminate if failure to initialize
    if(!glfwInit())
        return -1;

    // create new window with 800x600 resolution titled "OpenGL Window"
    window = glfwCreateWindow(Settings::ResolutionX, Settings::ResolutionY, "OpenGL Window", NULL, NULL);

    // ensure that window successfully initialized
    if(!window) {
        glfwTerminate();
        return -1;
    }

    // Set OpenGL context to this window
    glfwMakeContextCurrent(window);

    // draw 1 frame before swapping front and back frame buffer
    glfwSwapInterval(0);

    // ensure that glew initialized successfully
    if(glewInit() != GLEW_OK) {
        glfwTerminate();
        return -1;
    }

    // print the OpenGL version
    std::cout << glGetString(GL_VERSION) << std::endl;
    
#ifdef ENABLE_TESTS
//    TextureArray texArr;
//    testCubeHeight(&texArr, vertexData, indexData);
//    testChunk(vertexData, indexData);
//    std::cout << "test executed" << std::endl;
#endif
    
//    VertexArray va;
    //VertexBuffer vb(vertexData.data(), vertexData.size() * sizeof(float));
    
//    VertexBufferLayout layout;
//    layout.push_float(3);
//    layout.push_float(3);
//    va.addBuffer(vb, layout);

    GLCall(glEnable(GL_CULL_FACE));
    GLCall(glCullFace(GL_BACK));

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);


    Shader shader("resources/shaders/basic_array.shader");
    shader.bind();

    Renderer renderer;

    shader.setUniform1i("uTexture", 0);

    glEnable(GL_DEPTH_TEST);

    size_t nc = 8;
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(1 / ((float)nc * 16.0f)));
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)Settings::ResolutionX / (float)Settings::ResolutionY, 0.001f, 100.0f);
    glm::mat4 mvp = projection * view * model;


    ChunkGenerator generator;
    Chunk*** chunks;
    
    Chunk* top;
    Chunk* left;
    Chunk* back;
    Chunk* right;
    Chunk* front;
    Chunk* bottom;

    chunks = new Chunk**[nc];
    for(size_t x = 0; x < nc; x++) {
        chunks[x] = new Chunk*[nc];
        for(size_t y = 0; y < nc; y++) {
            chunks[x][y] = new Chunk[nc];
            for(size_t z = 0; z < nc; z++) {
                

                if(x != 0)
                    left = &chunks[x-1][y][z];
                if(x != nc - 1)
                    right = &chunks[x+1][y][z];
                if(y != 0)
                    bottom = &chunks[x][y-1][z];
                if(y != nc - 1)
                    top = &chunks[x][y+1][z];
                if(z != 0)
                    front = &chunks[x][y][z-1];
                if(z != nc - 1)
                    back = &chunks[x][y][z+1];
                
                chunks[x][y][z].setAdjacentChunks(top, left, back, right, front, bottom);
                chunks[x][y][z].setChunkPosition(x, y, z);
                generator.generateChunk(&chunks[x][y][z], x, y, z);
            }
        }
    }

//    shader.setUniformMat4f("uModelMatrix", model);
//    shader.setUniformMat4f("uViewMatrix", view); 
//    shader.setUniformMat4f("uProjectionMatrix", projection);
//    shader.setUniform1f("uScaleFactor", 1.0f);

    Camera cam;
    cam.setSensitivity(60.0f);
    cam.setMovementSpeed(0.2f);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float lastPrint = 0.0f;
    while(!glfwWindowShouldClose(window)) {
        renderer.clear();
        glClearColor(0.35f, 0.8f, 0.95f, 1.0f);
        
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastPrint += deltaTime;
        if(lastPrint >= 2.0f) {
            lastPrint = 0.0f;
            std::cout << 1.0f / deltaTime << '\n';
        }
        lastFrame = currentFrame;

        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cam.processKeyboardInput(Camera::Direction::FRONT, deltaTime);
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cam.processKeyboardInput(Camera::Direction::RIGHT, deltaTime);
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cam.processKeyboardInput(Camera::Direction::BACK, deltaTime);
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cam.processKeyboardInput(Camera::Direction::LEFT, deltaTime);
        if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            cam.processKeyboardInput(Camera::Direction::UP, deltaTime);
        if(glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
            cam.processKeyboardInput(Camera::Direction::DOWN, deltaTime);
        
        if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            cam.processMouseMovement(0, deltaTime);
        if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            cam.processMouseMovement(deltaTime, 0);
        if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            cam.processMouseMovement(0, -deltaTime);
        if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            cam.processMouseMovement(-deltaTime, 0);
        
        // update mvp matrix
        shader.setUniformMat4f("uMVPmatrix", projection * cam.getViewMatrix() * model); 

        for(size_t x = 0; x < nc; x++)
        for(size_t y = 0; y < nc; y++)
        for(size_t z = 0; z < nc; z++)
            chunks[x][y][z].render(renderer, shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
