#ifndef WALL_H
#define WALL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "shaderprogram.h"


class Wall{
    protected:
        glm::vec3 DBL; // punkt dolny bliższy lewy
        float l;
        float w;
        float h;
        float angle_horizontal = 0;

        unsigned int VERTEX_COUNT=36;
        float *VERTICES;
        float *TEX_COORDS;
        float *NORMALS;

        void wall_initializer();
        void skaluj(float tab[], unsigned int start, unsigned int stop, unsigned int step, float mnoznik);

    public:
        Wall();
        Wall(glm::vec3 DBL, glm::vec3 LHW);
        Wall(float xl, float yd, float zb, float dlugosc, float wysokosc, float szerokosc);
        ~Wall();
        void setAngle_horizontal(float alpha);
        void draw(glm::mat4 P, glm::mat4 V, GLuint tex);

        bool is_within(glm::vec3 punkt, float radius);
};

class Wall_triangular{
    protected:
        glm::vec3 C;
        float h;
        float a;
        float b;
        float gamma;

        float angle_horizontal = 0;

        unsigned int VERTEX_COUNT=24;
        float *VERTICES;
        float *TEX_COORDS;
        float *NORMALS;

        void shape_triangle(float vertices[], float normals[]);
        void wall_initializer();
        void skaluj(float tab[], unsigned int start, unsigned int stop, unsigned int step, float mnoznik);

    public:
        Wall_triangular();
        Wall_triangular(glm::vec3 punkt, float a, float b, float h, float gamma, float angle_horizontal);
        void draw(glm::mat4 P, glm::mat4 V, GLuint tex);
        bool is_within(glm::vec3 punkt, float radius);
};

#endif