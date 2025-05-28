#version 330 core

// Uniforms
uniform mat4 P; 
uniform mat4 V; 
uniform mat4 M;

// Atrybuty
layout (location = 0) in vec3 vertex;    
layout (location = 1) in vec3 normal;  
layout (location = 2) in vec2 texCoords;

out vec2 i_tex;

void main() {
    gl_Position = P * V * M * vec4(vertex, 1.0);
    i_tex = texCoords;
}
