#include "moveable.h"

// MOVEABLE -------------------------------------------------------------------------------------------------------------
void Moveable::move_along_obstacle(float T, std::vector<Wall_rect>& obstacles, std::vector<Wall_trian>& obstacles_tr){
    glm::vec3 original_velocity = velocity;
    velocity.x = (original_velocity.x + original_velocity.z)*(sqrt(2)/2);
    velocity.z = (original_velocity.z - original_velocity.x)*(sqrt(2)/2);
    if(move_along_obstacle_util(T, obstacles, obstacles_tr)) velocity.x = -velocity.x;
    else{
        velocity.x = (original_velocity.x - original_velocity.z)*(sqrt(2)/2);
        velocity.z = (original_velocity.z + original_velocity.x)*(sqrt(2)/2);
        move_along_obstacle_util(T, obstacles, obstacles_tr);
    }
}

bool Moveable::move_along_obstacle_util(float T, std::vector<Wall_rect>& obstacles, std::vector<Wall_trian>& obstacles_tr){
    glm::vec3 new_position = position + velocity * T;
    bool new_position_valid = true;

    for(unsigned int i=0;i<obstacles.size();i++) if(obstacles[i].is_within(new_position, radius)){
        new_position_valid = false;
        break;
    }
    for(unsigned int i=0;i<obstacles_tr.size();i++) if(obstacles_tr[i].is_within(new_position, radius)){
        new_position_valid = false;
        break;
    }
    if(new_position_valid) position = new_position;
    return new_position_valid;
}

Moveable::Moveable(){
    position.x = 0.0;
    position.y = 0.0;
    position.z = 0.0;
}

Moveable::Moveable(glm::vec3 position){
    this->position = position;
}

Moveable::Moveable(float x, float y, float z){
    position.x = x;
    position.y = y;
    position.z = z;
}

void Moveable::setPosition(glm::vec3 position){
    this->position = position;
}

void Moveable::setPosition(float x, float y, float z){
    position.x = x;
    position.y = y;
    position.z = z;
}

glm::vec3 Moveable::getPosition(){
    return position;
}

void Moveable::setVelocity(glm::vec3 v){
    velocity = v;
}

glm::vec3 Moveable::getVelocity(){
    return velocity;
}

float Moveable::getAngle_horizontal(){
    return angle_horizontal;
}

void Moveable::change_angle_horizontal(float dAlpha){
    angle_horizontal += dAlpha;
    if(angle_horizontal > 2*3.1415926535) angle_horizontal -= 2*3.1415926535;
    else if(angle_horizontal < -2*3.1415926535) angle_horizontal += 2*3.1415926535;
}

void Moveable::setVelocity_value(float value){
    velocity_value = value;
}

float Moveable::getVelocity_value(){
    return velocity_value;
}

void Moveable::setRadius(float radius){
    if(radius < 0) radius = 1.0;
    this->radius = radius;
}

float Moveable::getRadius(){
    return radius;
}

void Moveable::speedup_forward(){
    glm::vec3 v;
    v.y = 0.0;
    v.x = cos(angle_horizontal) * velocity_value;
    v.z = sin(angle_horizontal) * velocity_value;
    setVelocity(v);
}

void Moveable::speedup_backward(){
    glm::vec3 v;
    v.y = 0.0;
    v.x = -cos(angle_horizontal) * velocity_value;
    v.z = -sin(angle_horizontal) * velocity_value;
    setVelocity(v);
}

void Moveable::speedup_left(){
    glm::vec3 v;
    v.y = 0.0;
    v.x = sin(angle_horizontal) * velocity_value;
    v.z = -cos(angle_horizontal) * velocity_value;
    setVelocity(v);
}

void Moveable::speedup_right(){
    glm::vec3 v;
    v.y = 0.0;
    v.x = -sin(angle_horizontal) * velocity_value;
    v.z = cos(angle_horizontal) * velocity_value;
    setVelocity(v);
}

void Moveable::speedup_forward_right(){
    glm::vec3 v;
    v.y = 0.0;
    v.x = cos(angle_horizontal) * velocity_value - sin(angle_horizontal) * velocity_value / 1.41;
    v.z = sin(angle_horizontal) * velocity_value + cos(angle_horizontal) * velocity_value / 1.41;
    setVelocity(v);
}

void Moveable::speedup_forward_left(){
    glm::vec3 v;
    v.y = 0.0;
    v.x = cos(angle_horizontal) * velocity_value + sin(angle_horizontal) * velocity_value / 1.41;
    v.z = sin(angle_horizontal) * velocity_value - cos(angle_horizontal) * velocity_value / 1.41;
    setVelocity(v);
}

void Moveable::speedup_backward_right(){
    glm::vec3 v;
    v.y = 0.0;
    v.x = -cos(angle_horizontal) * velocity_value - sin(angle_horizontal) * velocity_value / 1.41;
    v.z = -sin(angle_horizontal) * velocity_value + cos(angle_horizontal) * velocity_value / 1.41;
    setVelocity(v);
}

void Moveable::speedup_backward_left(){
    glm::vec3 v;
    v.y = 0.0;
    v.x = -cos(angle_horizontal) * velocity_value + sin(angle_horizontal) * velocity_value / 1.41;
    v.z = -sin(angle_horizontal) * velocity_value - cos(angle_horizontal) * velocity_value / 1.41;
    setVelocity(v);
}

void Moveable::fly_up(){
    glm::vec3 v = velocity;
    v.y = velocity_value;
    setVelocity(v);
}

void Moveable::fly_down(){
    glm::vec3 v = velocity;
    v.y = -velocity_value;
    setVelocity(v);
}

bool Moveable::move(float T, std::vector<Wall_rect>& obstacles, std::vector<Wall_trian>& obstacles_tr){
    glm::vec3 new_position = position + velocity * T;
    bool new_position_valid = true;

    for(unsigned int i=0;i<obstacles.size();i++) if(obstacles[i].is_within(new_position, radius)){
        new_position_valid = false;
        break;
    }
    if(new_position_valid) for(unsigned int i=0;i<obstacles_tr.size();i++) if(obstacles_tr[i].is_within(new_position, radius)){
        new_position_valid = false;
        printf("traingle colisoiin\n");
        break;
    }
    
    if(new_position_valid) position = new_position;
    else move_along_obstacle(T, obstacles, obstacles_tr);
    return new_position_valid;
}

// OBSERVER ---------------------------------------------------------------------------------------------
Observer::Observer(){
    position.x = 0.0;
    position.y = 0.0;
    position.z = 0.0;
}

Observer::Observer(glm::vec3 position){
    this->position = position;
}

Observer::Observer(float x, float y, float z){
    position.x = x;
    position.y = y;
    position.z = z;
}

float Observer::getAngle_vertical(){
    return angle_vertical;
}

void Observer::change_angle_vertical(float dAlpha){
    float newAngle = angle_vertical + dAlpha;
    if(newAngle < 3.1415926535/2 && newAngle > -3.1415926535/2) angle_vertical = newAngle;
}

glm::vec3 Observer::getLookAtPoint(){
    glm::vec3 pointOnSphere;
    pointOnSphere.y = sin(angle_vertical);
    pointOnSphere.x = cos(angle_horizontal) * cos(angle_vertical);
    pointOnSphere.z = sin(angle_horizontal) * cos(angle_vertical);
    return position + pointOnSphere;
}