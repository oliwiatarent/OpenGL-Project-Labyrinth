#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

//Atrybuty
layout (location=0) in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location=1) in vec4 normal; //wektor normalny w wierzcholku
layout (location=2) in vec2 texCoord; //wsp�rz�dne teksturowania

uniform vec4 lp;
out vec4 l;
out vec4 l1;
out vec4 l2;
out vec4 l3;
out vec4 l4;
out vec4 n;
out vec4 v;
out vec2 i_tc;

void main(void) {
    vec4 lp = vec4(10000, 1000, 0, 1); // w przestrzeni świata
    vec4 lp1 = vec4(-10000, 1000, -10000, 1); // w przestrzeni świata
    vec4 lp2 = vec4(-10000, 1000, 10000, 1); // w przestrzeni świata
    vec4 lp3 = vec4(0, -1000, 0, 1);
    vec4 lp4 = vec4(0, 1000, 0, 1);

    l = normalize(lp - M*vertex);
    l1 = normalize(lp1 - M*vertex);
    l2 = normalize(lp2 - M*vertex);
    l3 = normalize(lp3 - M*vertex);
    l4 = normalize(lp4 -M*vertex);
    n = normalize(M*normal);
    v = normalize(vec4(0, 0, 0, 1) - M*vertex);

    i_tc=texCoord;
    gl_Position=P*V*M*vertex;
}