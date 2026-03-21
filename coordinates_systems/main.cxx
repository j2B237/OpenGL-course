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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


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
const char *TITLE {"LearnOpenGL - Coordinates Systems"};

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

glm::mat4 projectionMat;

GLfloat zOffset {-3.0f};
GLfloat inc {0.01f};

// ======== MAIN PROGRAM ENTRY POINT ======= //


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
        std::cerr << TAG << "Container texture instantiation failed!\n";
    }

    Texture2D *emojiTex = new Texture2D("./data/textures/emoji.png");
    if(emojiTex == nullptr){
        std::cerr << TAG << "Emoji texture instantiation failed!\n";
    }


    // Projection matrix is defined once there is no need to
    // create it the game loop

    program->use();

    projectionMat = glm::mat4(1.0f);
    projectionMat = glm::perspective(glm::radians(60.0f), (float)(WIDTH/HEIGHT), 0.1f, 100.0f);

    program->setMat4("projectionMat", projectionMat);

    // ====== Game loop ========== //

    while (!glfwWindowShouldClose(window)){

        // Clear background color
        glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        // Process Input
        processInput(window);


        // ===  Update World ==== //

        // TODO: EXERCISE 1
        /*
            zOffset += inc;

            if(zOffset > 3.0f){
                inc = -0.01f;
            }
            
            if(zOffset < -10.0f){
                inc = 0.01f;
            }
        */
       
        program->use();

        glm::mat4 modelMat = glm::mat4(1.0f);
        modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        glm::mat4 viewMat = glm::mat4(1.0f);
        viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, zOffset));


        // Assign a texture unit to individual uniform sampler2D objects

        containertex->activate(GL_TEXTURE0);
        emojiTex->activate(GL_TEXTURE1);
        

        // Get a reference to uniform OpenGL objects and then copy data
        // from C++ to GPU Memory

        program->setInt("containerTex", 0);
        program->setInt("emojiTex", 1);

        program->setMat4("modelMat", modelMat);
        program->setMat4("viewMat", viewMat);

        
        // ======== Drawing commands ======= //

        render(program);

        containertex->deactivate();
        emojiTex->deactivate();

        // Poll events
        glfwPollEvents();

        // Swap buffers
        glfwSwapBuffers(window);

    }

    // Free unused resources
    delete containertex;
    delete emojiTex;
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
    GLint direction = 1.0f;

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    // TODO: EXERCISE 2
    // Move the scene forward
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        
        direction *= -1;

        if(zOffset > 3.0f){
            inc = 0.00f;
        }
        else{
            inc = 0.01f;
        }

        zOffset -= inc * direction;
    }
    // Move the scene backward
    if(glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS){

        direction *= -1;

        if(zOffset < -10.0f){
            inc = 0.00f;
        }
        else{
            inc = 0.01f;
        }
        zOffset += inc * direction;
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
        
        glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);                                                 // Make the 0th buffer (array buffer) active
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos[0]);                                         // Make the 0th element array buffer active

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);       // Associate the 0th vertex attribute with the 0th array buffer 
        glEnableVertexAttribArray(0);                                                           // Enable the 0th vertex attribute

        // We do the same for the texture
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);                           // Data stored in the 0th VBO will be transmitted to the vertex attribute
                                                                                                // that has layout qualifier with location = 0 in the vertex shader.
                                                                                                // Those data are sent the respecting the order define by index stored
                                                                                                // the indices C++ array objects.

        // Unbind buffers
        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    }
    glBindVertexArray(0);
}