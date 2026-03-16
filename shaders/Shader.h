#pragma once

#define GLAD_IMPLEMENTATION_NONE
#include <glad/glad.h>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

class Shader 
{
public:
    Shader (const char *vertexPath, const char *fragmentpath);
    ~Shader();

    void use();
    void setInt (const std::string &name, GLint value);
    void setFloat (const std::string &name, GLfloat value);
    void setBool (const std::string &name, bool value);

    inline GLuint getId() const {return m_id;}

private:

    GLuint createProgram (const char *vertexPath, const char *fragmentPath);
    GLuint createShader (const char *shaderSource, GLenum type);
    std::string loadShaderFromFile (const char *filePath);

    /*[Private member variables]*/
    GLuint m_id;
};