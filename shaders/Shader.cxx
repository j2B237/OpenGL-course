#include "Shader.h"

//#define DEBUG 
#define SHADER "SHADER::"

Shader::Shader(const char *vertexPath, const char *fragmentpath) : m_id (0)
{
    // 1. Load shader source code from file
    std::string vertexCode, fragmentCode;

    vertexCode = loadShaderFromFile(vertexPath);
    fragmentCode = loadShaderFromFile (fragmentpath);

    if (vertexCode.empty() || fragmentCode.empty()){
        return;
    }

    // 2. Convert c++ string to C-like string
    const char *vertexSource = vertexCode.c_str();
    const char *fragmentSource = fragmentCode.c_str();

#ifdef DEBUG
    std::cerr << "vertex shader source:\n" << vertexSource << "\n";
    std::cerr << "fragment shader source:\n" << fragmentSource << "\n";
#endif

    // 3. create shader program
    m_id = createProgram (vertexSource, fragmentSource);
    if (m_id == 0){
        std::cerr << SHADER << "createProgram() failed!\n";
        return;
    }
}

Shader::~Shader()
{
    if (m_id != 0)
        glDeleteProgram (m_id);

    std::cerr << SHADER << "DESTRUCTOR::CALL\n";
}

void Shader::use()
{
    if (m_id != 0)
        glUseProgram (m_id);
}

void Shader::setInt(const std::string &name, GLint value)
{
    GLint location = glGetUniformLocation (m_id, name.c_str());
    glUniform1i(location, value);
}

void Shader::setFloat(const std::string &name, GLfloat value)
{
    GLint location = glGetUniformLocation (m_id, name.c_str());
    glUniform1f (location, value);
}

void Shader::setBool(const std::string &name, bool value)
{
    GLint location = glGetUniformLocation (m_id, name.c_str());
    glUniform1i (location, (GLint)value);
}

GLuint Shader::createProgram(const char *vertexPath, const char *fragmentPath)
{
    GLuint vertex = createShader (vertexPath, GL_VERTEX_SHADER);
    GLuint fragment = createShader (fragmentPath, GL_FRAGMENT_SHADER);

    if (vertex == 0 || fragment == 0){
        return 0;
    }

    m_id = glCreateProgram();

    glAttachShader(m_id, vertex);
    glAttachShader(m_id, fragment);
    glLinkProgram(m_id);

    GLint link_ok;
    char infoLog[1024];

    glGetProgramiv(m_id, GL_LINK_STATUS, &link_ok);
    if(!link_ok){
        glGetProgramInfoLog(m_id, 1024, NULL, infoLog);
        std::cerr << SHADER << "PROGRAM: " << infoLog << "\n";
        return 0;
    }

    glDetachShader(m_id, vertex);
    glDetachShader(m_id, fragment);
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return m_id;
}

GLuint Shader::createShader(const char *shaderSource, GLenum type)
{
    GLuint shader = glCreateShader(type);

#ifdef DEBUG
    std::cerr << SHADER << "shader id : " << shader << '\n';
#endif

    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    GLint compile_ok;
    char infoLog[1024];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_ok);
    if (!compile_ok){
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cerr << SHADER << type << ": " << infoLog << '\n';
        return 0;
    }

    return shader;
}

std::string Shader::loadShaderFromFile(const char *filePath)
{
    std::string shaderCode;

    // 1. Ensure ifstream object raise exceptions
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try{
        // 2. Open file
        shaderFile.open(filePath);

        // 3. Store buffer contents into string stream
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();

        // Close file
        shaderFile.close();

        // convert string stream into normal string
        shaderCode = shaderStream.str();
    }
    catch(...){
        std:: cerr << SHADER << "ERROR:FAILED_OPEN_FILE\n";
        return std::string();
    }

    return shaderCode;
}
