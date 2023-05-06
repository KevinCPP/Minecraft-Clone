#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "../include/Texture.h"
#include "../include/Renderer.h"
#include "../include/IndexBuffer.h"
#include "../include/VertexArray.h"
#include "../include/VertexBuffer.h"
#include "../include/VertexBufferLayout.h"

#include "../include/stb_image.h"

int main() {
    // window object
    GLFWwindow *window;

    // initialize glfw, terminate if failure to initialize
    if(!glfwInit())
        return -1;

    // create new window with 800x600 resolution titled "OpenGL Window"
    window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);

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

    const size_t nVertices = 4 * 6;
    const size_t vertexSize = 5;

    // layout: x y z u v
    float vertices[nVertices * vertexSize] = {
        // face 1 (front)
        -0.5,  0.5, -0.5, 0, 1, // top left
        -0.5, -0.5, -0.5, 0, 0, // bottom left
         0.5,  0.5, -0.5, 1, 1, // top right
         0.5, -0.5, -0.5, 1, 0, // bottom right
    
        // face 2 (right side)
         0.5,  0.5, -0.5, 0, 1, // top left
         0.5, -0.5, -0.5, 0, 0, // bottom left
         0.5,  0.5,  0.5, 1, 1, // top right
         0.5, -0.5,  0.5, 1, 0, // bottom right

        // face 3 (back) <same as front, but positive z coords
        -0.5,  0.5,  0.5, 0, 1, // top left
        -0.5, -0.5,  0.5, 0, 0, // bottom left
         0.5,  0.5,  0.5, 1, 1, // top right
         0.5, -0.5,  0.5, 1, 0, // bottom right

        // face 4 (left side)
        -0.5,  0.5, -0.5, 0, 1, // top left
        -0.5, -0.5, -0.5, 0, 0, // bottom left
        -0.5,  0.5,  0.5, 1, 1, // top right
        -0.5, -0.5,  0.5, 1, 0, // bottom right

        // face 5 (bottom)
        -0.5, -0.5,  0.5, 0, 1, // top left
        -0.5, -0.5, -0.5, 0, 0, // bottom left
         0.5, -0.5,  0.5, 1, 1, // top right
         0.5, -0.5, -0.5, 1, 0, // bottom right

        // face 6 (top)
        -0.5,  0.5,  0.5, 0, 1, // top left
        -0.5,  0.5, -0.5, 0, 0, // bottom left
         0.5,  0.5,  0.5, 1, 1, // top right
         0.5,  0.5, -0.5, 1, 0 // bottom right
    };
    
    const size_t nIndices = 6 * 6;

    unsigned int indices[nIndices] = {
         0,  1,  2,  2,  1,  3,
         4,  5,  6,  6,  5,  7,
         8,  9, 10, 10,  9, 11,
        12, 13, 14, 14, 13, 15,
        16, 17, 18, 18, 17, 19,
        20, 21, 22, 22, 21, 23
    };
    

    VertexArray va;
    VertexBuffer vb(vertices, nVertices * vertexSize * sizeof(float));

    VertexBufferLayout layout;
    layout.push_float(3);
    layout.push_float(2);
    va.addBuffer(vb, layout);

    IndexBuffer ib(indices, nIndices);

    Shader shader("resources/shaders/basic.shader");
    shader.bind();

    Renderer renderer;

    Texture texture("resources/textures/Bricks.png");
    texture.bind(0); 
    
    shader.setUniform1i("uTexture", 0);

    glEnable(GL_DEPTH_TEST);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 mvp = projection * view * model;

    while(!glfwWindowShouldClose(window)) {
        renderer.clear();
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    
        // rotate model matrix
        model = glm::rotate(model, glm::radians(2.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        // update MVP matrix
        mvp = projection * view * model;
        
        shader.setUniformMat4f("uMVPMatrix", mvp);

        //glBindVertexArray(vao);
        //glBindTexture(GL_TEXTURE_2D, texture);
        //glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
        //glBindVertexArray(0);

        renderer.draw(va, ib, shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}














