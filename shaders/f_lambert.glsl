#version 330


out vec4 pixelColor;

//Zmienne interpolowane
// in vec2 TexCoords;
in vec4 i_color;

// uniform sampler2D material_texture_diffuse1;

void main(void) {
	// vec4 texColor = texture(material_texture_diffuse1, TexCoords);
	pixelColor = i_color;
}
