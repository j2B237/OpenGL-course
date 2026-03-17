#version 460 core

out vec4 fragColor;
in vec3 texColor;
in vec2 textureCoord;

uniform sampler2D containerTex;
uniform sampler2D emojiTex;

void main()
{
    // emoji texture will be visible at 80% while container texture at 20%
    fragColor = mix(texture(containerTex, textureCoord), texture(emojiTex, textureCoord), 0.2);
}