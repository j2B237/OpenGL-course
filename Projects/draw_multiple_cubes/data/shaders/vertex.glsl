#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoord;

out vec2 texCoord;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

void main()
{
    gl_Position = projectionMat * viewMat * modelMat * vec4(position.x, position.y, position.z, 1.0f);
    texCoord = textureCoord;
}