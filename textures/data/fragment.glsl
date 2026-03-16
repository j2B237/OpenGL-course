#version 460 core

out vec4 fragColor;
in vec3 texColor;
in vec2 textureCoord;

void main()
{
    fragColor = vec4(texColor, 1.0f);
}