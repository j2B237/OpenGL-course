/**
 * @file Texture.h
 * @author Youssouf BINYOUM
 * @brief Wrapper class for all C++ code.
 * @version 0.1
 * @date 2026-03-16
 * 
 * @copyright Copyright (c) 2026
 * 
*/

#pragma once

#define GLAD_IMPLEMENTATION_NONE
#include <glad/glad.h>
#include <iostream>

#define DEBUG 1
#define TAG "TEXTURE::"

class Texture2D
{
public:

    /*[Constructor]*/
    Texture2D (const char *filename, GLenum wrapParams = GL_REPEAT, GLenum filterParams = GL_LINEAR);
    ~Texture2D();
    void activate(GLenum textureUnit);

private:

    /*[Private methods]*/

    void loadImageFromFile(const char *filename);
    void createTexture (GLenum wrapParams, GLenum filterParams);

    /*[Private member variables]*/

    GLuint m_Id;
    int m_width, m_height, m_nrChannels;
    unsigned char *m_data;
};