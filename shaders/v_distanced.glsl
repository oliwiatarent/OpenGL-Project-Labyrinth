#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

uniform vec4 torches[10];

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

    float torch_distance, nearest_torch_distance = 999.9;
    for(int i=0;i<torches.length();i++){
        torch_distance = distance(torches[i], M*vertex);
        if(nearest_torch_distance > torch_distance) nearest_torch_distance = torch_distance;
    }

    d = clamp(pow(light_power, 1.7)/pow(d, 1.7), 0.01, 1.0);
    d = d + clamp(pow(light_power, 1.9)/pow(nearest_torch_distance, 1.9), 0.01, 1.0);

    i_tc=texCoord;
    gl_Position=P*V*M*vertex;
}