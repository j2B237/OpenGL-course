/**
 * @file main.cxx
 * @author Y. BINYOUM
 * @brief Use custom shader class to load shader source code
 * from file and draw a simple colored triangle.
 * @version 1.0
 * 
*/


#define GLAD_IMPLEMENTATION_NONE
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include "Shader.h"

#define NUMVAOS 1
#define NUMVBOS 2
#define MAIN "MAIN::"

/*====== Global variables ====== */

GLuint vaos[NUMVAOS];
GLuint vbos[NUMVBOS];

const GLint WIDTH {800};
const GLint HEIGHT {600};
const char *TITLE {"LearnOpenGL - Shader"};

GLfloat vertices[] = {
    // position             // color
    -0.5f,  -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
    0.5f,   -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,
    0.0f,    0.5f, 0.0f,    0.0f, 0.0f, 1.0f
};

GLfloat offset {0.0f};
GLfloat inc {0.01f};
int direction {1};

/*======= Function declaration ======*/

void
framebufferSibeCB(GLFWwindow *window, int width, int height);

void
processInput(GLFWwindow *window);

int
main()
{
    // ====== GLFW INIT ======
    int result = glfwInit();

    if(!result){
        std::cerr << MAIN << "glfwInit() failed!\n";
        exit (EXIT_FAILURE);
    }

    // Set Window hint
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create GLFW window
    GLFWwindow *window = glfwCreateWindow (WIDTH, HEIGHT, TITLE, NULL, NULL);
    if(window == nullptr){
        std::cerr << MAIN << "glfwCreateWindow() failed!\n";
        glfwTerminate();
        exit (EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSibeCB);

    //====== GLAD ===========
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << MAIN << "glad failed loading openGL functions's pointer\n";
        glfwTerminate();
        exit (EXIT_FAILURE);
    }

    Shader *program = new Shader("vertex.glsl", "fragment.glsl");

    // Vertex Buffer Objects

    glGenVertexArrays(NUMVAOS, vaos);
    glBindVertexArray(vaos[0]);
    {
        glGenBuffers(NUMVBOS, vbos);
        glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);           // safely unbind
    }
    glBindVertexArray(0);


    // ==== Game Loop ======
    while (!glfwWindowShouldClose(window)){

        // Clear background color

        glClearColor (0.6f, 0.6f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Process Input
        processInput(window);

        // Drawing commands
        program->use();

        offset += inc * direction;

        if (offset >= 1.0f || offset <= -1.0f){
            direction *= -1;        // on inverse la direction
        }
       
        program->setFloat("offset", offset);


        glBindVertexArray(vaos[0]);
        {
            glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);

            // Define struct of data for position of vertices
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(0);

            // Define struct of data for the color
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(1);

            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        glBindVertexArray(0);

        // Poll events
        glfwPollEvents();

        // Swap buffers
        glfwSwapBuffers(window);
    }


    // Free unused resources
    delete program;
    glfwTerminate();

    exit (EXIT_SUCCESS);    
}

/* ========= Functions definition ========= */

void
framebufferSibeCB(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void
processInput(GLFWwindow *window)
{
    // if escape key pressed close window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}