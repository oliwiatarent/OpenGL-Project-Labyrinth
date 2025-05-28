#version 330 core

in vec2 i_tex;

out vec4 pixelColor;

uniform sampler2D material_diffuse1;

void main() {
    pixelColor = texture(material_diffuse1, i_tex);
}