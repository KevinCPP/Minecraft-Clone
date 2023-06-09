#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "../vendor/fastnoiselite.h"

#include "../include/Cube.h"
#include "../include/Quad.h"
#include "../include/Chunk.h"
#include "../include/Vertex.h"
#include "../include/Camera.h"
#include "../include/Region.h"
#include "../include/Frustum.h"
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

    glm::mat4 model = glm::mat4(1.0f);
    //glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)Settings::ResolutionX / (float)Settings::ResolutionY, 0.001f, 100.0f);

    shader.setUniformMat4f("uModelMatrix", model);
    shader.setUniformMat4f("uProjectionMatrix", projection);
    shader.setUniform1f("uScaleFactor", World::CHUNK_SIZE * Settings::renderDistance);

    Chunk c;
    c.fill();

    Camera cam;
    cam.setSensitivity(60.0f);
    cam.setMovementSpeed(0.2f);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float lastPrint = 0.0f;

    Region r;
    r.reload(); 

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
        shader.setUniformMat4f("uViewMatrix", cam.getViewMatrix()); 

        r.render(renderer, shader, Geometry::Frustum(projection * cam.getViewMatrix() * model), true);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
