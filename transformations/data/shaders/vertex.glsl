#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoord;

out vec2 texCoord;
uniform mat4 trans;

void main()
{
    gl_Position = trans * vec4(position, 1.0f);
    texCoord = textureCoord;
}