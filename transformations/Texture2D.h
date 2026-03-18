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

#include <string>
#include <iostream>

#define DEBUG 1
#define TEXTURE_TAG "TEXTURE::"

class Texture2D
{
public:

    /*[Constructor]*/
    Texture2D (const char *filename, GLenum wrapParams = GL_REPEAT, GLenum filterParams = GL_LINEAR);
    ~Texture2D();
    void activate(GLenum textureUnit);
    inline void deactivate(){
        glBindTexture(GL_TEXTURE_2D, 0);
    }

private:

    /*[Private methods]*/

    std::string getFileExtension(const char *filename);
    void loadImageFromFile(const char *filename);
    void createTexture (GLenum wrapParams, GLenum filterParams);

    /*[Private member variables]*/

    GLuint m_Id;

    int m_width;
    int m_height;
    int m_nrChannels;
};