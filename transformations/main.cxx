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
#include "Shader.h"
#include "Texture2D.h"

#define TAG "MAIN::"
#define NUMVAOS 1
#define NUMVBOS 1


// ========= FUNCTIONS PROTOTYPES =========== //

void
framebufferSizeCB(GLFWwindow *window, int width, int height);
void
processInput(GLFWwindow *window);
void
render(GLvoid *prog);

// ========= GLOBALES VARIABLES ============= //

const int WIDTH {800};
const int HEIGHT {600};
const char *TITLE {"LearnOpenGL - Transformations"};

GLuint vaos[NUMVAOS];
GLuint vbos[NUMVBOS];
GLuint ebos[NUMVBOS];


GLfloat vertices [] = {
    // Position              // Texture coordinates
     0.5f,  0.5f, 0.0f,      1.0f, 1.0f,
     0.5f, -0.5f, 0.0f,      1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,      0.0f, 0.0f,
    -0.5f,  0.5f, 0.0f,      0.0f, 1.0f
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};


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

    // ======= GLAD ======== //
    
    if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))){
        std::cerr << TAG << "glad failed load openGL function\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }


    // Shaders 
    Shader *program = new Shader("./data/shaders/vertex.glsl", "./data/shaders/fragment.glsl");
    if(program == nullptr){
        std::cerr << TAG << "Shader instantiation failed\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Buffers objects
  
    glGenVertexArrays(NUMVAOS, vaos);
    glBindVertexArray(vaos[0]);
    {
        // VBOS
        glGenBuffers(NUMVBOS, vbos);
        glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // EBOS
        glGenBuffers(NUMVBOS, ebos);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos[0]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    }
    glBindVertexArray(0);

    // Textures
    Texture2D *containertex = new Texture2D("./data/textures/container.jpg");
    if (containertex == nullptr){
        std::cerr << TAG << "Texture instantiation failed\n";
    }

    // ====== Game loop ========== //
    while (!glfwWindowShouldClose(window)){

        // Clear background color
        glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        // Process Input
        processInput(window);


        // Update World


        // Drawing commands
        
        program->use();
        containertex->activate(GL_TEXTURE0);
        program->setInt("containerTex", 0);

        render(program);


        // Poll events
        glfwPollEvents();

        // Swap buffers
        glfwSwapBuffers(window);

    }

    // Free unused resources
    delete containertex;
    delete program;
    glfwTerminate();


    std::cout << TAG << "Application close successfully...\n";
    return EXIT_SUCCESS;
}

// ========= FUNCTIONS IMPLEMENTATION =========== //

void
framebufferSizeCB(GLFWwindow *window, int width, int height)
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

void
render(GLvoid *prog)
{
    Shader *temp = (Shader*)prog;
    temp->use();

    glBindVertexArray(vaos[0]);
    {
        // Tell OpenGL how position's vertices are layed out
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        // Same but for the texture
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos[0]);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);

    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}