/**
 * @file main.cxx
 * @author youssouf BINYOUM
 * @brief Transformation using matrix operations
 * @version 0.1
 * @date 2026-03-18
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#define GLAD_IMPLEMENTATION_NONE
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


#include <iostream>

#define TAG "MAIN::"

// ========= FUNCTIONS PROTOTYPES =========== //

void
framebufferSizeCB(GLFWwindow *window, int width, int height);


// ========= GLOBALES VARIABLES ============= //

const int WIDTH {800};
const int HEIGHT {600};
const char *TITLE {"LearnOpenGL - Transformations"};


int
main(int argc, char *argv[])
{
    //============ GLFW INITIALIZATION ============= //
    
    int result = glfwInit();
    if (result != GLFW_TRUE){
        std::cerr << TAG << "glfwInit() failed\n";
        exit (EXIT_FAILURE);
    }

    // GLFW Window hint
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // GLFW Window
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    if (window == nullptr){
        std::cerr << TAG << "glfwCreateWindow() failed\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCB);


    // Shaders 
    

    return EXIT_SUCCESS;
}

// ========= FUNCTIONS IMPLEMENTATION =========== //

void
framebufferSizeCB(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}