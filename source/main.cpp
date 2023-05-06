#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "../include/stb_image.h"
#include "../include/shader.h"

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

    // layout: x y z u v
    float vertices[] = {
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

    /* 
    int indices[] = {
         0,  1,  2,  3,
         4,  5,  6,  7,
         8,  9, 10, 11,
        12, 13, 14, 15,
        16, 17, 18, 19,
        20, 21, 22, 23
    };
    */
    
    int indices[] = {
        0, 1, 2, 2, 1, 3,
        4, 5, 6, 6, 5, 7,
        8, 9, 10, 10, 9, 11,
        12, 13, 14, 14, 13, 15,
        16, 17, 18, 18, 17, 19,
        20, 21, 22, 22, 21, 23
    };
    

    // create and bind vao
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // create and bind VBO
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // allocate memory for VBO and copy vertex data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // specify format of vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    // enable vertex attributes
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // create and bind IBO
    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    // allocate memory for ibo and copy index data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // unbind vbo and vao
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //later
    //glBindVertexArray(vao)
    //glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
    //glBindVertexArray(0);

    // load texture data from file
    int width, height, channels;
    unsigned char* image_data = stbi_load("resources/textures/Bricks.png", &width, &height, &channels, STBI_rgb_alpha);
    
    if(!image_data)
        std::cout << "error, image data null\n";

    // create and bind texture object
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

        // set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // upload texture data to texture object
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    
    // after uploading texture, enable mipmapping to ensure it is rendered correctly at different LOD
    glGenerateMipmap(GL_TEXTURE_2D);

    // free image data
    stbi_image_free(image_data);

    // later:
    // glBindTexture(GL_TEXTURE_2D, texture);

    // load and compile vertex and fragment shaders
    unsigned int vertexShader = loadShader(GL_VERTEX_SHADER, "resources/shaders/basic.vert");
    unsigned int fragmentShader = loadShader(GL_FRAGMENT_SHADER, "resources/shaders/basic.frag");

    // create shader program and link vertex and fragment shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // ensure shader linked properly
    int status;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if(status != GL_TRUE) {
        char log[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, log);
        std::cerr << "ERROR: Failed to link shader program: " << log << std::endl;
        return -1;
    }

    // bind shader program
    glUseProgram(shaderProgram);

    unsigned int uTextureLocation = glGetUniformLocation(shaderProgram, "uTexture");
    glUniform1i(uTextureLocation, 0); // Assuming you're using texture unit 0

    glEnable(GL_DEPTH_TEST);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 mvp = projection * view * model;

    unsigned int uMVPMatrixLocation = glGetUniformLocation(shaderProgram, "uMVPMatrix");

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

        // rotate model matrix
        model = glm::rotate(model, glm::radians(2.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        // update MVP matrix
        mvp = projection * view * model;

        glUniformMatrix4fv(uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(mvp));        

        glBindVertexArray(vao);
        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}







































