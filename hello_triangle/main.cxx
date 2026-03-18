/**
 * @file main.cxx
 * @author Yossep BINYOUM
 * @brief  A simple c++ program to render a triangle
 * @version 1.0
 * @date 06/03/2026
 */

#define GLAD_IMPLEMENTATION_NONE
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.h"

#define NUM_VAOS 3
#define NUM_VBOS 1

//========= Function prototypes ===========//

void 
framebuffer_size_callback(GLFWwindow *window, int width, int height);
void
processInput(GLFWwindow *window);

// ======== Global variables  =============//

GLfloat vertices[] = {
    -0.5f,  -0.5f, 0.0f,
    0.5f,   -0.5f, 0.0f,
    0.0f,    0.5f, 0.0f
};

// OpenGL Objects 

GLuint vaos[NUM_VAOS];
GLuint vbos[NUM_VBOS];

int
main(int argc, char *argv[])
{
    //========
    // GLFW 
    //=========

    int result = glfwInit();
    if(!result){
        std::cerr << "glfwInit() failed!\n";
        exit(EXIT_FAILURE);
    }

    // Define glfw window hint
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // GLFW Window
    GLFWwindow *window = glfwCreateWindow(
                                    800,                          // width  
                                    600,                                // Height
                                    "Learn OpenGL - Hello Triangle",    // Title
                                    NULL, NULL);                        // monitor and share    
    
    if (window == nullptr){
        std::cerr << "glfwCreateWindow() failed!\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //=============
    // GLAD 
    //=============

    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "glad failed to load openGL functions's pointers\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    //===============
    // SHADERS
    //===============

    Shader *prog = new Shader("./vertex.glsl", "./fragment.glsl");

    //======================
    // BUFFER OBJECTS 
    //======================

    /*
        Send the defined vertex data as input to the first stage of the graphic
        pipeline : vertex shader. 
        1. Creating memory on the GPU where we stored vertex data.
        2. Configure how OpenGL should interpret the memory.
        3. Specify how to send the data to the graphic card.
    */

    glGenVertexArrays(1, vaos);
    glBindVertexArray(vaos[0]);
    {
        glGenBuffers(1, vbos);
        glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
        // Copy the user-defined data into the currently bound buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Set vertex attribute pointer for the position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    glBindVertexArray(0);

    //============
    // Game Loop 
    //============

    while(!glfwWindowShouldClose(window)){

        // Clear window with a color
        glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //===============
        // Process Input
        //===============
        processInput(window);

        //========================
        // OpenGL Drawing commands
        //========================
        
        prog->activate();

        glBindVertexArray(vaos[0]);
        {
            glDrawArrays(GL_TRIANGLES, 0, 3);           // send data to
            //glBindBuffer(GL_ARRAY_BUFFER, 0);           // Unbind current VBO
        }
        glBindVertexArray(0);                           // Unbind current VAO

        // Poll Events
        glfwPollEvents();

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Free unused resources (window)
    delete prog;

    glfwTerminate();
    return 0;
}

//====== Functions definition ==============//

void 
framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void
processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}