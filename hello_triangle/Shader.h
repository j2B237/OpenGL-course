#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
    
    /*[constructors]*/
    // Shader for vertex and fragment stage in OpenGL pipeline
    Shader (const char *vertexPath, const char *fragmentPath);
    ~Shader();

    /*[Methods]*/
    inline GLuint getId() const {return m_id;}
    void setInt (const std::string &name, GLint value);
    void setFloat (const std::string &name, GLfloat value);
    void setBool (const std::string &name, bool value);
    //void setMat (std::string &name, glm::mat4 matrix);
    void activate();

private:

    std::string loadShaderFromFile (const char *filePath);
    GLuint createProgram(const char *vertexSource, const char *fragmenSource);
    GLuint createShader(const char *shaderSource, GLenum type);

    GLuint m_id;
};