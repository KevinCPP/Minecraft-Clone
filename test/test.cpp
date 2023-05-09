#include "test.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <iomanip>

#include "../include/VertexBufferLayout.h"
#include "../include/TextureAtlas.h"
#include "../include/VertexBuffer.h"
#include "../include/IndexBuffer.h"
#include "../include/VertexArray.h"
#include "../include/Renderer.h"
#include "../include/Shader.h"
#include "../include/Vertex.h"
#include "../include/Camera.h"
#include "../include/Macros.h"
#include "../include/Quad.h"

void testQuads() {
    GLFWwindow *window;

    if(!glfwInit())
        exit(EXIT_FAILURE);

    window = glfwCreateWindow(800, 600, "testQuads", NULL, NULL);

    if(!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if(glewInit() != GLEW_OK) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    std::cout << "TESTQUADS | " << glGetString(GL_VERSION) << std::endl;

    TextureAtlas tAtlas("resources/textures/atlas.bmp", 4, 4);
   
    float scale = 0.2f;

    const size_t verticesPerQuad = 4;
    const size_t vertexSize = 5;
    const size_t nVertices = 24;
    const size_t nIndices = 36;
    const size_t nQuads = 6;

    Vertex<vertexSize> vertices[nVertices] = {
        Vertex<vertexSize>(-0.5 * scale,  0.5 * scale, -0.5 * scale, 0, 1),
        Vertex<vertexSize>(-0.5 * scale, -0.5 * scale, -0.5 * scale, 0, 0),
        Vertex<vertexSize>( 0.5 * scale,  0.5 * scale, -0.5 * scale, 1, 1),
        Vertex<vertexSize>( 0.5 * scale, -0.5 * scale, -0.5 * scale, 1, 0),
        
        Vertex<vertexSize>( 0.5 * scale,  0.5 * scale, -0.5 * scale, 0, 1),
        Vertex<vertexSize>( 0.5 * scale, -0.5 * scale, -0.5 * scale, 0, 0),
        Vertex<vertexSize>( 0.5 * scale,  0.5 * scale,  0.5 * scale, 1, 1),
        Vertex<vertexSize>( 0.5 * scale, -0.5 * scale,  0.5 * scale, 1, 0),
        
        Vertex<vertexSize>(-0.5 * scale,  0.5 * scale,  0.5 * scale, 0, 1),
        Vertex<vertexSize>(-0.5 * scale, -0.5 * scale,  0.5 * scale, 0, 0),
        Vertex<vertexSize>( 0.5 * scale,  0.5 * scale,  0.5 * scale, 1, 1),
        Vertex<vertexSize>( 0.5 * scale, -0.5 * scale,  0.5 * scale, 1, 0),
        
        Vertex<vertexSize>(-0.5 * scale,  0.5 * scale, -0.5 * scale, 0, 1),
        Vertex<vertexSize>(-0.5 * scale, -0.5 * scale, -0.5 * scale, 0, 0),
        Vertex<vertexSize>(-0.5 * scale,  0.5 * scale,  0.5 * scale, 1, 1),
        Vertex<vertexSize>(-0.5 * scale, -0.5 * scale,  0.5 * scale, 1, 0),
        
        Vertex<vertexSize>(-0.5 * scale, -0.5 * scale,  0.5 * scale, 0, 1),
        Vertex<vertexSize>(-0.5 * scale, -0.5 * scale, -0.5 * scale, 0, 0),
        Vertex<vertexSize>( 0.5 * scale, -0.5 * scale,  0.5 * scale, 1, 1),
        Vertex<vertexSize>( 0.5 * scale, -0.5 * scale, -0.5 * scale, 1, 0),
        
        Vertex<vertexSize>(-0.5 * scale,  0.5 * scale,  0.5 * scale, 0, 1),
        Vertex<vertexSize>(-0.5 * scale,  0.5 * scale, -0.5 * scale, 0, 0),
        Vertex<vertexSize>( 0.5 * scale,  0.5 * scale,  0.5 * scale, 1, 1),
        Vertex<vertexSize>( 0.5 * scale,  0.5 * scale, -0.5 * scale, 1, 0),
    };
    
    Quad quads[nQuads];

    for(size_t i = 0; i < nQuads; i++) {
        quads[i] = Quad(vertices + (i * verticesPerQuad));
    }

    unsigned int indices[nIndices] = {
         0,  1,  2,  2,  1,  3,
         4,  5,  6,  6,  5,  7,
         8,  9, 10, 10,  9, 11,
        12, 13, 14, 14, 13, 15,
        16, 17, 18, 18, 17, 19,
        20, 21, 22, 22, 21, 23
    };
     
    for(size_t i = 0; i < nQuads; i++) {
        switch(i) {
            case 0:
            case 1:
            case 2:
            case 3:
                quads[i].setTextureCoordsFromAtlas(&tAtlas, 0, 1, 1, 1);
                break;
            case 4:
            case 5:
                quads[i].setTextureCoordsFromAtlas(&tAtlas, 1, 1, 1, 1);
                break;
        }
    }

    float* quadsToFloatPtr = &quads[0].vertices[0].data[0];

    const size_t padding = 6;
    for(size_t i = 0; i < nQuads * verticesPerQuad * vertexSize; i++) {
        std::cout << std::setw(padding) << quadsToFloatPtr[i];

        if((i + 1) % 5 == 0)
            std::cout << std::endl;
    }

    VertexArray va;
    VertexBuffer vb(quadsToFloatPtr, nQuads * verticesPerQuad * vertexSize * sizeof(float));

    VertexBufferLayout layout;
    layout.push_float(3);
    layout.push_float(2);
    va.addBuffer(vb, layout);

    IndexBuffer ib(indices, nIndices);
    
    Shader shader("resources/shaders/basic.shader");
    shader.bind();

    Renderer renderer;

    shader.setUniform1i("uTexture", 0);
    glEnable(GL_DEPTH_TEST);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 mvp = projection * view * model;

    Camera cam;
    cam.setSensitivity(4.0f);
    cam.setMovementSpeed(0.5f);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    while(!glfwWindowShouldClose(window)) {
        renderer.clear();
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
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
            cam.processMouseMovement(0, 1);
        if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            cam.processMouseMovement(1, 0);
        if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            cam.processMouseMovement(0, -1);
        if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            cam.processMouseMovement(-1, 0);

        // update MVP matrix
        mvp = projection * cam.getViewMatrix() * model;
        
        shader.setUniformMat4f("uMVPMatrix", mvp);

        renderer.draw(va, ib, shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    exit(EXIT_SUCCESS);
}




