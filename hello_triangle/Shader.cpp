#include "Shader.h"

//#define DEBUG

Shader::Shader(const char *vertexPath, const char *fragmentPath) :
    m_id (0)
{
    // 1. Retrieve vertex and fragment source code from file
    std::string vertexCode, fragmentCode;
    vertexCode      = loadShaderFromFile(vertexPath);
    fragmentCode    = loadShaderFromFile(fragmentPath);

    if (vertexCode.empty() || fragmentCode.empty()){
        std::cerr << "ERROR::SHADER::Failed to create shader\n";
        return;
    }

    // 2. convert string to const char * bc OpenGL is a C-string API
    const char *vertexSource = vertexCode.c_str();
    const char *fragmenSource = fragmentCode.c_str();

#ifdef DEBUG
    std::cout << vertexSource << '\n';
    std::cout << fragmenSource << '\n';
#endif

    // 3. shader program
    m_id = createProgram(vertexSource, fragmenSource);
    if (m_id == 0){return;}
}

Shader::~Shader()
{
    glDeleteProgram(m_id);
    std::cerr << "SHADER::DESTRUCTOR::CALL\n";
}

void Shader::setInt(const std::string &name, GLint value)
{
    GLint location = glGetUniformLocation(m_id, name.c_str());
    glUniform1i(location, value);
}

void Shader::setFloat(const std::string &name, GLfloat value)
{
    GLint location = glGetUniformLocation (m_id, name.c_str());
    glUniform1f(location, value);
}

void Shader::setBool(const std::string &name, bool value)
{
    GLint location = glGetUniformLocation(m_id, name.c_str());
    glUniform1i(location, GLint(value));
}

void Shader::activate()
{
    glUseProgram(m_id);
}

std::string Shader::loadShaderFromFile(const char *filePath)
{
    std::ifstream shaderFile;    
    std::string shaderCode;

    // Ensure ifstream object can throw exceptions
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try{
        // Open files
        shaderFile.open(filePath);

        // read the file's buffer contents into a stream
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();

        // close file handler
        shaderFile.close();

        // convert stream into string
        shaderCode = shaderStream.str();

    }
    catch (...){
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << '\n';
        return "";
    }

    return shaderCode;
}

GLuint Shader::createProgram(const char *vertexSource, const char *fragmenSource)
{
    GLuint vertex   = createShader(vertexSource, GL_VERTEX_SHADER);

#ifdef DEBUG
    std::cerr << "VERTEX ID : " << vertex << '\n';
#endif

    GLuint fragment = createShader(fragmenSource, GL_FRAGMENT_SHADER);

#ifdef DEBUG
    std::cerr << "FRAGMENT ID : " << fragment << '\n';
#endif

    if (vertex == 0 || fragment == 0){
        std::cerr << "createShader() failed!\n";
        return 0;
    }

    GLuint id = glCreateProgram();

#ifdef DEBUG
    std::cerr << "PROGRAM ID : " << id << '\n';
#endif

    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);

    GLint link_ok;
    char infoLog[1024];

    glGetProgramiv(id, GL_LINK_STATUS, &link_ok);
    if (!link_ok){
        glGetProgramInfoLog(id, 1024, NULL, infoLog);
        std::cerr << "ERROR::PROGRAM:" << infoLog << "\n";
    }

    glDetachShader(id, vertex);
    glDetachShader(id, fragment);
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return id;
}

GLuint Shader::createShader(const char *shaderSource, GLenum type)
{
    GLint compile_ok;
    char infoLog[1024];

    GLuint shader = glCreateShader (type);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    if (type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER){

        glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_ok);
        if (!compile_ok){
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::" << type << "::" << infoLog << '\n';
            return 0;
        }
    }

    return shader;
}
