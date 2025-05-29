#ifndef WALL_H
#define WALL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "shaders/shaderprogram.h"
#include <vector>
#include <thread>
#include "models/allmodels.h"
#include "externalmodel.h"

class Obstacle{
    protected:
        glm::vec3 DBL; // punkt dolny bliższy lewy
        float l; // długość boku pierwszego
        float w; // długość boku drugiego
        float h; // wysokość
        float angle_horizontal = 0; // kąt (w radianach), o jaki obrócona jest bryła wokół osi OY
        float angle_vertical = 0; // kąt (w radianach), o jaki obrócona jest bryła wokół osi OZ
    public:
        virtual void setAngle_horizontal(float alpha) = 0;
        virtual void setAngle_vertical(float alpha) = 0;
        virtual void draw(glm::mat4 P, glm::mat4 V, ShaderProgram* s_p) = 0; // metoda rysująca
        virtual bool is_within(glm::vec3 punkt, float radius) = 0; // metoda sprawdzająca, czy jakikolwiek punkt w odległości 'radius' od 'punkt' znajduje się wewnątrz bryły
};

class Wall : public Obstacle{ // abstrakcyjna klasa do tworzenia graniastosłupów o różnych podstawach, równi pochyłych, itp.
    protected:
        float gamma; // kąt (w radianach) pomiędzy bokami l, w (używany tylko w trójkątnych bryłach)

        unsigned int VERTEX_COUNT; // liczba wierzchołków
        float *VERTICES; // tablica z wierzchołkami
        float *TEX_COORDS; // tablia ze współrzędnymi teksturowania
        float *NORMALS; // tablica wektorów normalnych
        
        GLuint texture_id; // uchwyt do tekstury muru

        virtual void wall_initializer() = 0; // metoda inicjalizująca, wywoływana w konstruktorach
        virtual void skaluj(float tab[], unsigned int start, unsigned int stop, unsigned int step, float mnoznik) = 0; // metoda do modyfikacji współrzędnych teksturowania, by były odpowiednio rozciągnięte na obiekcie

    public:
        virtual void setTexture(GLuint texture_id) = 0;
        virtual char getType() = 0; // metoda służąca do identyfiakcji typu obiektu (przy posługiwaniu się wskaźnikiem)
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
        void setAngle_vertical(float alpha);
        void setTexture(GLuint texture_id);
        void draw(glm::mat4 P, glm::mat4 V, ShaderProgram* s_p);
        char getType(); // 0

        bool is_within(glm::vec3 punkt, float radius);
};

class Wall_trian : public Wall{
    protected:
        void shape_triangle(float vertices[], float normals[]); // metoda nadająca odpowiedni kształt trójkątnej podstawie graniastosłupa
        void wall_initializer();
        void skaluj(float tab[], unsigned int start, unsigned int stop, unsigned int step, float mnoznik);

    public:
        Wall_trian();
        Wall_trian(glm::vec3 punkt, float a, float b, float h, float gamma);
        void setAngle_horizontal(float alpha);
        void setAngle_vertical(float alpha);
        void setTexture(GLuint texture_id);
        void draw(glm::mat4 P, glm::mat4 V, ShaderProgram* s_p);
        char getType(); // 1
        bool is_within(glm::vec3 punkt, float radius);
};

class Ramp : public Wall_trian{
    protected:
        void wall_initializer(); // metoda inicjalizująca, wywoływana w konstruktorach
        void skaluj(float tab[], unsigned int start, unsigned int stop, unsigned int step, float mnoznik); // metoda do modyfikacji współrzędnych teksturowania, by były odpowiednio rozciągnięte na obiekcie
    
    public:
        Ramp(glm::vec3 punkt, float w, float l, float h); 

        void setAngle_horizontal(float alpha);
        void setAngle_vertical(float alpha);
        void setTexture(GLuint texture_id);
        void draw(glm::mat4 P, glm::mat4 V, ShaderProgram* s_p); // metoda rysująca
        char getType(); // 2

        bool is_within(glm::vec3 punkt, float radius); // metoda sprawdzająca, czy jakikolwiek punkt w odległości 'radius' od 'punkt' znajduje się wewnątrz bryły
        float getRampAngleRatio();
};

class Wall_creator{ // Klasa tworząca manualnie nowe obiekty typu Wall_rect oraz Wall_trian
    protected:
        glm::vec3 DBL = glm::vec3(0.0, 0.0, 0.0);
        float l = 1;
        float w = 1;
        float h = 1;
        float gamma = 0.78;
        float angle_horizontal = 0;
        float angle_vertical = 0;
        GLuint texture_id;

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
        Obstacle* current_wall; // wskaźnik na aktualnie tworzony obiekt
        Wall_creator();
        void setArguments(glm::vec3 DBL, float length, float width, float height, float gamma, float angle_horizontal, float angle_vertical); // ustawia atrybuty aktualnie tworzonego obiektu
        void assign_next_texture(std::vector<GLuint>& textures); // przypisuje kolejną teksturę do muru. KONIECZNIE użyć w fazie inicjalizacji.
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
        void changeAngle_vertical(float angle_vertical);

        void finish_wall_creation(std::vector<Obstacle*>& obstacles); // kończy modyfikację obiektu i go zapamiętuje
        void abort_wall_creation(); // kończy modyfikację obiektu bez zapisywania
};

class Obstacle_rect : public Obstacle{
    protected:
        glm::mat4 modelMatrix;
        bool is_selected = false;

        bool rayIntersectsAABB(const glm::vec3& rayOrigin, const glm::vec3& rayDir, const glm::vec3& boxMin, const glm::vec3& boxMax, float& t);

    public:
        Obstacle_rect();
        Obstacle_rect(glm::vec3 position);
        Obstacle_rect(glm::vec3 position, glm::vec3 size);
        void setAngle_horizontal(float alpha);
        void setAngle_vertical(float alpha);
        void draw(glm::mat4 P, glm::mat4 V, ShaderProgram* s_p); // metoda rysująca
        bool is_within(glm::vec3 punkt, float radius); // metoda sprawdzająca, czy jakikolwiek punkt w odległości 'radius' od 'punkt' znajduje się wewnątrz bryły

        glm::vec3 getSize();
        glm::vec3 getPosition();
        void setModelMatrix(glm::mat4 matrix);
        void setIsSelected(bool is_selected);
        bool is_clicked_on(const glm::vec3& rayOrigin, const glm::vec3& rayDir, float& t);
};

class Fence : public Obstacle_rect{
    protected:
        float final_height; // wysokość, na jaką podeniść ma się krata
        static constexpr float velocity_value = 1.0; // szybkość podnoszenia się kraty
        volatile bool is_moving = false;
        volatile bool is_existent = true;
    public: 
        Fence();
        Fence(glm::vec3 position);
        Fence(glm::vec3 position, glm::vec3 size);
        void setAngle_horizontal(float alpha);
        void setAngle_vertical(float alpha);
        void draw(glm::mat4 P, glm::mat4 V, ShaderProgram* s_p); // metoda rysująca
        bool is_within(glm::vec3 punkt, float radius); // metoda sprawdzająca, czy jakikolwiek punkt w odległości 'radius' od 'punkt' znajduje się wewnątrz bryły

        glm::vec3 getSize();
        glm::vec3 getPosition();
        void setModelMatrix(glm::mat4 matrix);
        void setIsSelected(bool is_selected);
        bool is_clicked_on(const glm::vec3& rayOrigin, const glm::vec3& rayDir, float& t);
        void change_height(float dh);
        void move(float T);
};

class Door : public Obstacle_rect{
    protected:
        float final_angle_horizontal; // kat, o jaki obrócić mają się drzwi
        static constexpr float velocity_value = 3.14159265359/4; // szybkość kątowa podnoszenia się kraty
        volatile bool is_moving = false;
        
    public:
        Door();
        Door(glm::vec3 position, float scale);

        void setAngle_horizontal(float alpha);
        void setAngle_vertical(float alpha);
        void draw(glm::mat4 P, glm::mat4 V, ShaderProgram* s_p); // metoda rysująca
        bool is_within(glm::vec3 punkt, float radius); // metoda sprawdzająca, czy jakikolwiek punkt w odległości 'radius' od 'punkt' znajduje się wewnątrz bryły

        glm::vec3 getSize();
        glm::vec3 getPosition();
        bool is_clicked_on(const glm::vec3& rayOrigin, const glm::vec3& rayDir, float& t);
        void open_close();
        void move(float T);
};

class Painting : public Obstacle_rect{
    protected:
        float final_height; 
        static constexpr float velocity_value = 8.0;
        volatile bool is_moving = false;
        short unsigned facing;
        bool on_floor = false;
        
    public:
        Painting();
        Painting(glm::vec3 position, short unsigned facing);

        void setAngle_horizontal(float alpha);
        void setAngle_vertical(float alpha);
        void draw(glm::mat4 P, glm::mat4 V, ShaderProgram* s_p); // metoda rysująca
        // bool is_within(glm::vec3 punkt, float radius); // metoda sprawdzająca, czy jakikolwiek punkt w odległości 'radius' od 'punkt' znajduje się wewnątrz bryły

        glm::vec3 getPosition();
        short unsigned getFacing();
        bool getOnFloor();
        bool is_clicked_on(const glm::vec3& rayOrigin, const glm::vec3& rayDir, float& t);
        void change_height(float dh);
        void move(float T);
};

#endif