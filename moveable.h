#ifndef MOVEABLE_H
#define MOVEABLE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "wall.h"


class Moveable{
    protected:
        glm::vec3 position; // pozycja w przestrzeni świata
        glm::vec3 velocity; // znormalizowany wektor prędkości obiektu
        float angle_horizontal = 0.0; // kat obrotu obiektu wzdłuź osi OX (radiany)
        float velocity_value = 3.0; // wartość prędkości
        float radius = 1.0; // określa, w jakiej odległości od środka obiektu, będzie dochodzić do kolizji 

        void move_along_obstacle(float T, std::vector<Wall*>& obstacles); // usprawnia ruch, gdy obiekt znajduje się obok przeszkody
        bool move_along_obstacle_util(float T, std::vector<Wall*>& obstacles);

    public:
        Moveable();
        Moveable(glm::vec3 position);
        Moveable(float x, float y, float z);

        void setPosition(glm::vec3 position);
        void setPosition(float x, float y, float z);
        glm::vec3 getPosition();

        void setVelocity(glm::vec3 v);
        glm::vec3 getVelocity();

        float getAngle_horizontal();
        void change_angle_horizontal(float dAlpha);

        void setVelocity_value(float value);
        float getVelocity_value();

        void setRadius(float radius);
        float getRadius();

        void speedup_forward(); // ustawia wektor prędkości w kierunku patrzenia
        void speedup_backward(); // ustawia wektor prędkości przeciwnie do kierunku patrzenia
        void speedup_left(); // ustawia wektor prędkości na prawo do kierunku patrzenia
        void speedup_right(); // ustawia wektor prędkości na lewo do kierunku patrzenia
        void speedup_forward_right(); // ustawia wektor prędkości na PI/4 w prawo do kierunku patrzenia
        void speedup_forward_left(); // ustawia wektor prędkości na PI/4 w lewo do kierunku patrzenia
        void speedup_backward_right(); // ustawia wektor prędkości na PI/4 w prawo przeciwnie do kierunku patrzenia
        void speedup_backward_left(); // ustawia wektor prędkości na PI/4 w lewo przeciwnie do kierunku patrzenia

        void fly_up(); // ustawia składową y wektora prędkości
        void fly_down(); // ustawia składową y wektora prędkości

        bool move(float T, std::vector<Wall*>& obstacles); // przemieszcza obiekt zgodnie z wektorem i wartością predkości
};

class Observer : public Moveable{
    protected: 
        float angle_vertical = 0.0; // kąt między promieniem wzroku obserwatora a powierzchnią XZ

    public:
        Observer();
        Observer(glm::vec3 position);
        Observer(float x, float y, float z);
        float getAngle_vertical();
        void change_angle_vertical(float dAlpha);
        glm::vec3 getLookAtPoint(); // wzraca punkt w odległości 1 od obserwatora, na który jest skierowany jego wzrok
};  




#endif