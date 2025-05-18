#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

//Atrybuty
layout (location=0) in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location=1) in vec4 normal; //wektor normalny w wierzcholku
layout (location=2) in vec2 texCoord; //wsp�rz�dne teksturowania

uniform vec4 camera_position;
uniform float light_power;
out float d;
out vec2 i_tc;

void main(void) {
    d = distance(camera_position, M*vertex);
    d = clamp(pow(light_power, 1.5)/pow(d, 1.5), 0.01, 1.0);

    i_tc=texCoord;
    gl_Position=P*V*M*vertex;
}