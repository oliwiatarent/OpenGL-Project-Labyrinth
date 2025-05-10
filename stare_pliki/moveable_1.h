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
        glm::vec3 position;
        glm::vec3 velocity;
        float angle_horizontal = 0.0;
        float velocity_value = 3.0;
        float radius = 1.0;

        void move_along_obstacle(float T, std::vector<Wall_rect>& obstacles, std::vector<Wall_trian>& obstacles_tr);
        bool move_along_obstacle_util(float T, std::vector<Wall_rect>& obstacles, std::vector<Wall_trian>& obstacles_tr);

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

        void speedup_forward();
        void speedup_backward();
        void speedup_left();
        void speedup_right();
        void speedup_forward_right();
        void speedup_forward_left();
        void speedup_backward_right();
        void speedup_backward_left();

        void fly_up();
        void fly_down();

        bool move(float T, std::vector<Wall_rect>& obstacles, std::vector<Wall_trian>& obstacles_tr);
};

class Observer : public Moveable{
    protected: 
        float angle_vertical = 0.0;

    public:
        Observer();
        Observer(glm::vec3 position);
        Observer(float x, float y, float z);
        float getAngle_vertical();
        void change_angle_vertical(float dAlpha);
        glm::vec3 getLookAtPoint();
};  




#endif