#include "Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture2D::Texture2D(const char *filename, GLenum wrapParams, GLenum filterParams) 
    : m_width (0), 
    m_height (0), 
    m_nrChannels (0)
{
    // 1. Generate the texture ID
    createTexture(wrapParams, filterParams);

    if (m_Id == 0){return;}
    loadImageFromFile(filename);
}

Texture2D::~Texture2D()
{
    if (m_Id != 0){
        glDeleteTextures (1, &m_Id);
        std::cerr << TAG << "DESTRUCTOR::CALL\n";
    }    
}

void Texture2D::activate(GLenum textureUnit)
{
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, m_Id);
}

std::string Texture2D::getFileExtension(const char *filename)
{
    if (!filename)
        return std::string();

    std::string path(filename);

    // Find the last path separator and the last dot
    size_t lastSlash = path.find_last_of("/\\");
    size_t lastDot = path.find_last_of('.');

    // No extension found
    if (lastDot == std::string::npos)
        return std::string();

    // Dot is part of a directory (e.g. ".config/file"), not the filename
    if (lastSlash != std::string::npos && lastDot < lastSlash)
        return std::string();

    return path.substr(lastDot + 1);
}

void Texture2D::loadImageFromFile(const char *filename)
{
    // Find the file extension
    std::string extension = getFileExtension(filename);

    // Make sure image are load correctly
    stbi_set_flip_vertically_on_load(true);

    unsigned char *m_data = stbi_load(filename, &m_width, &m_height, &m_nrChannels, 0);
    if(m_data){
        
#if DEBUG == 1
    std::cerr << TAG << "Texture's size is " << m_width << " x " << m_height << " pixels\n";
#endif
        if (extension.compare("jpg") == 0){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)m_data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
       else if (extension.compare("png") == 0){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)m_data);
            glGenerateMipmap(GL_TEXTURE_2D);
       }
    }
    else{
        std::cerr << TAG << "failed to load image\n";
    }

    stbi_image_free(m_data);
}

void Texture2D::createTexture(GLenum wrapParams, GLenum filterParams)
{
    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_2D, m_Id);

#if DEBUG == 1
    std::cerr << TAG << "ID : " << m_Id << "\n";
#endif

    // Wrapping params
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapParams);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapParams);

    // Filtering params
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterParams);   // Smooth texture when object is far
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // show individual pixel when object is close
}
