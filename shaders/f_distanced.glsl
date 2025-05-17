#version 330

uniform sampler2D tex;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela
in vec2 i_tc;
in float d;

void main(void) {
    vec4 color = texture(tex,i_tc);
	pixelColor = color * d;
}