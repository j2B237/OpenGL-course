/**
 * @file main.cxx
 * @author Youssouf BINYOUM (bonobostudio)
 * @brief  Render texture on square shape using openGL
 * @version 0.1
 * @date 2026-03-16
 * 
 * @copyright Copyright (c) 2026
 * 
 */


#define GLAD_IMPLEMENTATION_NONE
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Shader.h"

#define MAIN "MAIN::"
#define DEBUG 1
#define NUMVAOS 1
#define NUMVBOS 1

// ========= Global variables ============

const int WIDTH {800};
const int HEIGHT {600};
const char *TITLE {"Learn OpenGL - Textures"};

GLuint vaos[NUMVAOS];
GLuint vbos[NUMVBOS];
GLuint ebos[NUMVBOS];

GLfloat vertices [] = {
    // Position              // Color            // Texture coordinates
     0.5f,  0.5f, 0.0f,      1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
     0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,      0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
    -0.5f,  0.5f, 0.0f,      1.0f, 0.0f, 1.0f,   0.0f, 1.0f
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

// ====== Function prototypes ========
void 
framebuffer_SizeCB (GLFWwindow *window, int width, int height);
void
processInput (GLFWwindow *window);


// Main program entry point

int
main(int argc, char *argv[])
{
    // ===== GLFW INITIALIZATION ======
    int result = glfwInit();

    if(result == GLFW_FALSE){
        std::cerr << MAIN << "glfwInit() failed!\n";
        exit (EXIT_FAILURE);
    }

    // Set window hint
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create GLFW window
    GLFWwindow *window = glfwCreateWindow (WIDTH, HEIGHT, TITLE, NULL, NULL);
    if (window == nullptr){
        std::cerr << MAIN << "glfwCreateWindow() failed\n";
        glfwTerminate();
        exit (EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_SizeCB);

    // ==== GLAD =========

    if (!gladLoadGLLoader ((GLADloadproc)glfwGetProcAddress)){
        std::cerr << MAIN << "glad failed to load openGL function's pointer\n";
        glfwTerminate();
        exit (EXIT_FAILURE);
    }

    // Shaders
    Shader *program = new Shader("./data/vertex.glsl", "./data/fragment.glsl");

    // Buffers Objects
    glGenVertexArrays (NUMVAOS, vaos);
    glBindVertexArray(vaos[0]);
    {
        glGenBuffers (NUMVBOS, vbos);
        glBindBuffer (GL_ARRAY_BUFFER, vbos[0]);
        glBufferData (GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);

        glGenBuffers(NUMVBOS, ebos);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos[0]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }

    // Loading and creating textures
    /*GLuint textureID;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Wrapping params
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Filtering params
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   // Smooth texture when object is far
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // show individual pixel when object is close

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char *data = stbi_load("./data/textures/container.jpg", &width, &height, &nrChannels, 0);
    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cerr << MAIN << "failed to load image\n";
    }

    stbi_image_free(data);
    */
   
    // ==== Game loop ======

    while (!glfwWindowShouldClose (window)){

        // clear background color
        glClearColor (0.2f, 0.3f, 0.3f, 1.0f);
        glClear (GL_COLOR_BUFFER_BIT);

        // processInput
        processInput (window);

        // Update world
        program->use();
        
        // Activate texture
        /*glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);*/
        program->setInt("containerID", 0);

        // TODO:

        glBindVertexArray(vaos[0]);
        {
            // Defines how vertex position are received in GPU
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(0);

            // Defines how fragment color are transmit
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(1);

            // Defines how texture coords are transmit
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
            glEnableVertexAttribArray(2);

            //glDrawArrays (GL_TRIANGLES, 0, 6);

            glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos[0]);
            
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);
        }
        
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);            // deactivate texture


        // Poll events
        glfwPollEvents();

        // Swap buffers
        glfwSwapBuffers (window);
    }

    // Free unused resources

    delete program;
    glfwTerminate();

    return EXIT_SUCCESS;
}

// Function definitions

void 
framebuffer_SizeCB (GLFWwindow *window, int width, int height)
{
    glViewport (0, 0, width, height);
}

void
processInput (GLFWwindow *window)
{
    if (glfwGetKey (window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose (window, GLFW_TRUE);
    }
}