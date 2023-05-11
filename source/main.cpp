#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <cstdio>

#include "../include/Cube.h"
#include "../include/Quad.h"
#include "../include/Vertex.h"
#include "../include/Camera.h"
#include "../include/Texture.h"
#include "../include/Renderer.h"
#include "../include/IndexBuffer.h"
#include "../include/VertexArray.h"
#include "../include/TextureAtlas.h"
#include "../include/VertexBuffer.h"
#include "../include/VertexBufferLayout.h"

#include "../include/stb_image.h"

#include "../test/test.h"

using namespace Geometry;

int main() {

#ifdef ENABLE_TESTS
    testQuads();
#endif

    // window object
    GLFWwindow *window;

    // initialize glfw, terminate if failure to initialize
    if(!glfwInit())
        return -1;

    const size_t resX = 1600;
    const size_t resY = 900;

    // create new window with 800x600 resolution titled "OpenGL Window"
    window = glfwCreateWindow(resX, resY, "OpenGL Window", NULL, NULL);

    // ensure that window successfully initialized
    if(!window) {
        glfwTerminate();
        return -1;
    }

    // Set OpenGL context to this window
    glfwMakeContextCurrent(window);

    // draw 1 frame before swapping front and back frame buffer
    glfwSwapInterval(1);

    // ensure that glew initialized successfully
    if(glewInit() != GLEW_OK) {
        glfwTerminate();
        return -1;
    }

    // print the OpenGL version
    std::cout << glGetString(GL_VERSION) << std::endl;

    const size_t radius = 32;

    Cube cubes[radius * radius];
    TextureAtlas texture("resources/textures/atlas.bmp", 4, 4);

    int xs[] = {
        1, 2, 2, 3, 3
    };

    int ys[] = {
        3, 3, 2, 1, 0
    };

    for(size_t i = 0; i < radius * radius; i++) {
        size_t pass = i / radius;
        cubes[i].setPosition(i % radius, 1.0f, pass);
        cubes[i].setNormalizedDeviceCoordinates((float)radius);
        size_t randomNum = rand() % 5;
        cubes[i].setAllTextureCoords(&texture, xs[randomNum], ys[randomNum], 1, 1);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);

    VertexArray va;
    VertexBuffer vb(std::get<0>(getFloatArray(cubes, radius * radius)), std::get<1>(getFloatArray(cubes, radius * radius)) * sizeof(float));

    VertexBufferLayout layout;
    layout.push_float(3);
    layout.push_float(2);
    va.addBuffer(vb, layout);

    IndexBuffer ib(std::get<0>(getIndicesArray(radius * radius)), std::get<1>(getIndicesArray(radius * radius)));

    Shader shader("resources/shaders/basic.shader");
    shader.bind();

    Renderer renderer;

    //Texture texture("resources/textures/atlas.bmp");
    //texture.bind(0); 

    shader.setUniform1i("uTexture", 0);

    glEnable(GL_DEPTH_TEST);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)resX / (float)resY, 0.01f, 100.0f);
    glm::mat4 mvp = projection * view * model;

    Camera cam;
    cam.setSensitivity(4.0f);
    cam.setMovementSpeed(0.5f);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    while(!glfwWindowShouldClose(window)) {
        renderer.clear();
        glClearColor(0.35f, 0.8f, 0.95f, 1.0f);
        
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
}
