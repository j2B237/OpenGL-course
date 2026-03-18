#version 460 core

in vec2 texCoord;
out vec4 fragColor;

uniform sampler2D containerTex;
uniform sampler2D emojiTex;

void main()
{
    fragColor = mix(texture(containerTex, texCoord), texture(emojiTex, texCoord), 0.2);
}