#include "moveable.h"

#define maxClimbAngle 3.14/2.5
#define std_grav 9.81
#define climbing_samples 5

// MOVEABLE -------------------------------------------------------------------------------------------------------------
void Moveable::move_along_obstacle(float T, std::vector<Obstacle*>& obstacles){
    glm::vec3 original_velocity = velocity;
    velocity.x = (original_velocity.x + original_velocity.z)*(sqrt(2)/2);
    velocity.z = (original_velocity.z - original_velocity.x)*(sqrt(2)/2);
    if(move_along_obstacle_util(T, obstacles)) velocity.x = -velocity.x;
    else{
        velocity.x = (original_velocity.x - original_velocity.z)*(sqrt(2)/2);
        velocity.z = (original_velocity.z + original_velocity.x)*(sqrt(2)/2);
        move_along_obstacle_util(T, obstacles);
    }
}

bool Moveable::move_along_obstacle_util(float T, std::vector<Obstacle*>& obstacles){
    glm::vec3 new_position_down = position + velocity * T;
    glm::vec3 new_position_up = new_position_down;
    new_position_up.y += height;
    bool new_position_valid = true;

    for(unsigned int i=0;i<obstacles.size();i++) if(obstacles[i]->is_within(new_position_down, radius) || obstacles[i]->is_within(new_position_up, radius)){
        new_position_down.y += tan(maxClimbAngle)*T*velocity_value;
        new_position_up.y += tan(maxClimbAngle)*T*velocity_value;
        if(obstacles[i]->is_within(new_position_down, radius) || obstacles[i]->is_within(new_position_up, radius)){
            new_position_down.y -= tan(maxClimbAngle)*T*velocity_value;
            new_position_up.y -= tan(maxClimbAngle)*T*velocity_value;
            new_position_valid = false;
        }
        new_position_valid = false;
        break;
    }
    if(new_position_valid) position = new_position_down;
    return new_position_valid;
}

bool Moveable::can_fall_down(float T, std::vector<Obstacle*>& obstacles){
    glm::vec3 v(0.0, velocity.y, 0.0);
    glm::vec3 new_position_down = position + v * T;
    bool result = true;

    in_air = true;
    if(new_position_down.y < 0){
        new_position_down.y = 0.0;
        velocity.y = 0.0;
        in_air = false;
        result = false;
    }
    for(unsigned int i=0;i<obstacles.size();i++) if(obstacles[i]->is_within(new_position_down, radius)){
        result = false;
        in_air = false;
        break;
    }
    return result;
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

void Moveable::setVelocity_horizontal(glm::vec2 v){
    velocity.x = v.x;
    velocity.z = v.y;
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
    glm::vec2 v;
    v.x = cos(angle_horizontal) * velocity_value;
    v.y = sin(angle_horizontal) * velocity_value;
    setVelocity_horizontal(v);
}

void Moveable::speedup_backward(){
    glm::vec2 v;
    v.x = -cos(angle_horizontal) * velocity_value;
    v.y = -sin(angle_horizontal) * velocity_value;
    setVelocity_horizontal(v);
}

void Moveable::speedup_left(){
    glm::vec2 v;
    v.x = sin(angle_horizontal) * velocity_value;
    v.y = -cos(angle_horizontal) * velocity_value;
    setVelocity_horizontal(v);
}

void Moveable::speedup_right(){
    glm::vec2 v;
    v.x = -sin(angle_horizontal) * velocity_value;
    v.y = cos(angle_horizontal) * velocity_value;
    setVelocity_horizontal(v);
}

void Moveable::speedup_forward_right(){
    glm::vec2 v;
    v.x = cos(angle_horizontal) * velocity_value - sin(angle_horizontal) * velocity_value / 1.41;
    v.y = sin(angle_horizontal) * velocity_value + cos(angle_horizontal) * velocity_value / 1.41;
    setVelocity_horizontal(v);
}

void Moveable::speedup_forward_left(){
    glm::vec2 v;
    v.x = cos(angle_horizontal) * velocity_value + sin(angle_horizontal) * velocity_value / 1.41;
    v.y = sin(angle_horizontal) * velocity_value - cos(angle_horizontal) * velocity_value / 1.41;
    setVelocity_horizontal(v);
}

void Moveable::speedup_backward_right(){
    glm::vec2 v;
    v.x = -cos(angle_horizontal) * velocity_value - sin(angle_horizontal) * velocity_value / 1.41;
    v.y = -sin(angle_horizontal) * velocity_value + cos(angle_horizontal) * velocity_value / 1.41;
    setVelocity_horizontal(v);
}

void Moveable::speedup_backward_left(){
    glm::vec2 v;
    v.x = -cos(angle_horizontal) * velocity_value + sin(angle_horizontal) * velocity_value / 1.41;
    v.y = -sin(angle_horizontal) * velocity_value - cos(angle_horizontal) * velocity_value / 1.41;
    setVelocity_horizontal(v);
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

bool Moveable::move(float T, std::vector<Obstacle*>& obstacles){
    if(!can_fall_down(T, obstacles)) velocity.y = 0.0;
    glm::vec3 new_position_down = position + velocity * T;
    glm::vec3 new_position_up = new_position_down;
    new_position_up.y += height;
    bool new_position_valid = true;

    for(unsigned int i=0;i<obstacles.size();i++) if(obstacles[i]->is_within(new_position_down, radius) || obstacles[i]->is_within(new_position_up, radius)){
        bool climbing = false;
        for(unsigned short s=1;s<=climbing_samples;s++){
            new_position_down.y += tan(maxClimbAngle)*T*velocity_value/(float)climbing_samples;
            //new_position_down.x -= (position.x - new_position_down.x)/10;
            //new_position_down.z -= (position.z - new_position_down.z)/10;

            new_position_up = new_position_down;
            new_position_up.y += height;

            if(!(obstacles[i]->is_within(new_position_down, radius) || obstacles[i]->is_within(new_position_up, radius))){
                climbing = true;
                break;
            }
        }
        if(!climbing){
            new_position_down.y -= tan(maxClimbAngle)*T*velocity_value;
            new_position_up.y -= tan(maxClimbAngle)*T*velocity_value;
            new_position_valid = false;
        }

        in_air = false;
        if(!new_position_valid){
            break;
        }
        else continue;
    }

    if(new_position_valid) position = new_position_down;
    else{
        move_along_obstacle(T, obstacles);
    } 
    return new_position_valid;
}

void Moveable::fall(float T, std::vector<Obstacle*>& obstacles){
    velocity.y -= std_grav*T;
}

void Moveable::jump(){
    if(!in_air) velocity.y += sqrt(2*std_grav*jump_height);
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
    return getCameraPosition() + getCameraViewVector();
}

glm::vec3 Observer::getCameraPosition(){
    glm::vec3 camera_position = position;
    camera_position.y += height;
    return camera_position;
}

glm::vec3 Observer::getCameraViewVector(){
    glm::vec3 pointOnSphere;
    pointOnSphere.y = sin(angle_vertical);
    pointOnSphere.x = cos(angle_horizontal) * cos(angle_vertical);
    pointOnSphere.z = sin(angle_horizontal) * cos(angle_vertical);  
    return pointOnSphere;
}

#undef maxClimbAngle
#undef std_grav
#undef climbing_samples