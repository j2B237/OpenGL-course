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
#include "Shader.h"

#define MAIN "MAIN::"
#define DEBUG 1

// Global variables 

const int WIDTH {800};
const int HEIGHT {600};
const char *TITLE {"Learn OpenGL - Textures"};

// Function prototypes
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

    // ==== Game loop ======

    while (!glfwWindowShouldClose (window)){

        // clear background color
        glClearColor (0.8f, 0.8f, 0.8f, 1.0f);
        glClear (GL_COLOR_BUFFER_BIT);

        // processInput
        processInput (window);

        // Update world


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