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
#include <vector>

class Wall{ // abstrakcyjna klasa do tworzenia graniastosłupów o różnych podstawach, równi pochyłych, itp.
    protected:
        glm::vec3 DBL; // punkt dolny bliższy lewy
        float l; // długość boku pierwszego
        float w; // długość boku drugiego
        float h; // wysokość
        float gamma; // kąt (w radianach) pomiędzy bokami l, w (używany tylko w trójkątnych bryłach)
        float angle_horizontal; // kąt (w radianach), o jaki obrócona jest bryła wokół osi OY

        unsigned int VERTEX_COUNT; // liczba wierzchołków
        float *VERTICES; // tablica z wierzchołkami
        float *TEX_COORDS; // tablia ze współrzędnymi teksturowania
        float *NORMALS; // tablica wektorów normalnych

        virtual void wall_initializer() = 0; // metoda inicjalizująca, wywoływana w konstruktorach
        virtual void skaluj(float tab[], unsigned int start, unsigned int stop, unsigned int step, float mnoznik) = 0; // metoda do modyfikacji współrzędnych teksturowania, by były odpowiednio rozciągnięte na obiekcie
        virtual void shape_triangle(float vertices[], float normals[]) = 0; // metoda nadająca odpowiedni kształt trójkątnej podstawie graniastosłupa

    public:
        virtual void setAngle_horizontal(float alpha) = 0;
        virtual void draw(glm::mat4 P, glm::mat4 V, GLuint tex, ShaderProgram* s_p) = 0; // metoda rysująca

        virtual bool is_within(glm::vec3 punkt, float radius) = 0; // metoda sprawdzająca, czy jakikolwiek punkt w odległości 'radius' od 'punkt' znajduje się wewnątrz bryły
};

class Wall_rect : public Wall{
    protected:
        void wall_initializer();
        void skaluj(float tab[], unsigned int start, unsigned int stop, unsigned int step, float mnoznik);

        void shape_triangle(float vertices[], float normals[]); // useless

    public:
        Wall_rect();
        Wall_rect(glm::vec3 DBL, glm::vec3 LHW);
        Wall_rect(float xl, float yd, float zb, float dlugosc, float wysokosc, float szerokosc);
        ~Wall_rect();
        void setAngle_horizontal(float alpha);
        void draw(glm::mat4 P, glm::mat4 V, GLuint tex, ShaderProgram* s_p);

        bool is_within(glm::vec3 punkt, float radius);
};

class Wall_trian : public Wall{
    protected:
        void shape_triangle(float vertices[], float normals[]);
        void wall_initializer();
        void skaluj(float tab[], unsigned int start, unsigned int stop, unsigned int step, float mnoznik);

    public:
        Wall_trian();
        Wall_trian(glm::vec3 punkt, float a, float b, float h, float gamma, float angle_horizontal);
        void setAngle_horizontal(float alpha);
        void draw(glm::mat4 P, glm::mat4 V, GLuint tex, ShaderProgram* s_p);
        bool is_within(glm::vec3 punkt, float radius);
};

class Wall_creator{ // Klasa tworząca manualnie nowe obiekty typu Wall_rect oraz Wall_trian
    protected:
        glm::vec3 DBL = glm::vec3(0.0, 0.0, 0.0);
        float l = 1;
        float w = 1;
        float h = 1;
        float gamma = 0.78;
        float angle_horizontal = 0;

        char current_wall_creation_type = 0; // 0=Wall_rect, 1=Wall_trian
        Wall_rect current_wall_rect; // obecnie tworzony obiekt klasy Wall_rect
        Wall_trian current_wall_trian; // obecnie tworzony obiekt klasy Wall_trian

        Wall_rect* walls_rect; // wskaźnik na tablicę gotowych obiektów Wall_rect
        Wall_trian* walls_trian; // wskaźnik na tablicę gotowych obiektów Wall_trian

        unsigned short walls_rect_ptr = 0; // indeks obecnego obiektu w tablicy walls_rect
        unsigned short walls_trian_ptr = 0; // indeks obecnego obiektu w tablicy walls_trian

        void set_current_wall(); // metoda ustawiająca wskażnik current_wall na odpowiedni obiekt
    public:
        bool is_creating_wall = false; // flaga określająca, czy tworzony jest aktualnie jakiś obiekt 
        Wall* current_wall; // wskaźnik na aktualnie tworzony obiekt
        Wall_creator();
        void setArguments(glm::vec3 DBL, float length, float width, float height, float gamma, float angle_horizontal); // ustawia atrybuty aktualnie tworzonego obiektu
        void switch_wall_type(); // zmienia klasę tworzonego obiektu z Wall_rect na Wall_trian i na odwrót
        char get_wall_type();

        // przesuwanie tworzonego obiektu
        void move_X(float dx); 
        void move_Y(float dy); 
        void move_Z(float dz); 

        // zmiana atrybutów tworzonego obiektu
        void changeLength(float l); 
        void changeWidth(float w);
        void changeHeight(float h);
        void changeGamma(float gamma);
        void changeAngle_horizontal(float angle_horizontal);

        void finish_wall_creation(std::vector<Wall*>& obstacles); // kończy modyfikację obiektu i go zapamiętuje
        void abort_wall_creation(); // kończy modyfikację obiektu bez zapisywania
};


#endif