#version 460 core

out vec4 fragColor;
in vec3 texColor;
in vec2 textureCoord;

uniform sampler2D containerTex;

void main()
{
    fragColor = texture(containerTex, textureCoord);
}