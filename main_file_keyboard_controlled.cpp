#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "constants.h"
#include "models/allmodels.h"
#include "lodepng.h"
#include "shaders/shaderprogram.h"
#include "moveable.h"
#include "wall.h"
#include "key-funcs.h"
#include "labyrinth.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "externalmodel.h"

struct Torch{
        glm::vec3 position;
        char facing = 0; //{0=X+}{1=X-}{2=Z+}{3=Z-}
};

enum class MovePhase { Left, Up_Left, Up_Right, Right };
MovePhase currentPhase = MovePhase::Left;
float speed = 10.0f;
float traveled = 0.0f;
float totalTraveled = 0.0f;
float wWidth, wLength, lHeight, lWidth;
float delta = 0.15f;

struct Ghost {
        glm::vec3 startingPosition;
        glm::vec3 position;
        MovePhase phase = MovePhase::Left;
};

struct Treasure {
        glm::vec3 position;
        bool rotate;
};


using namespace std;

float zNear = 0.01; // bliższa odległość odcinania
float zFar = 70.0; // dalsza odległość odcinania
float mouse_sensitivity = 0.001; // czułość myszy

char maxActive_lights = 10; // NIE PRZEKRACZAĆ 10, ZMIENIĆ TEŻ W VERTEX SHADERZE ROZMIAR torches[] !!
char maxTorchesPerFloor = 10;
unsigned short screenwidth = 500;
unsigned short screenheight = 500;
float aspectRatio = 1.0;
bool cursor_centred = true;
bool gravity_on = true;

float zasieg_reki = 3.0;
float doorHeight = 6.0;

int numberOfFloors = 2;
float wallHeight = 9.0f;
float floorThickness = 2.0;
std::vector<std::vector<struct Torch>> torches;
std::vector<Fence> fences;
std::vector<Door> doors;
std::vector<GLuint> TEXTURES_FLOOR;
std::vector<GLuint> TEXTURES_WALL;
std::vector<Wall_rect> obstacles_rect;
std::vector<Wall_trian> obstacles_tr;
std::vector<Ramp> ramps;
std::vector<Obstacle*> OBSTACLES;
std::vector<struct Ghost> ghosts;
std::vector<struct Painting> paintings;
Treasure treasure;
Wall_creator wall_creator;
Observer obserwator;

ShaderProgram* sp;
ShaderProgram* observers_light;

void mouse_button_callback();
void draw_torch(struct Torch torch, ShaderProgram* s_p){
        glm::mat4 M = glm::mat4(1.0f);
        M = glm::translate(M, torch.position);
        M = glm::scale(M, glm::vec3(0.02f));
        if(torch.facing==48){
                M = glm::rotate(M, PI/10, glm::vec3(0.0, 0.0, 1.0));
                M = glm::rotate(M, PI/2, glm::vec3(0.0, 1.0, 0.0));
        } 
        else if(torch.facing==49){
                M = glm::rotate(M, -PI/10, glm::vec3(0.0, 0.0, 1.0));
                M = glm::rotate(M, -PI/2, glm::vec3(0.0, 1.0, 0.0));
        } 
        else if(torch.facing==50){
                M = glm::rotate(M, -PI/10, glm::vec3(1.0, 0.0, 0.0));
                M = glm::rotate(M, 0.0f, glm::vec3(0.0, 1.0, 0.0));
        }       
        else if(torch.facing==51){
                M = glm::rotate(M, PI/10, glm::vec3(1.0, 0.0, 0.0));
                M = glm::rotate(M, PI, glm::vec3(0.0, 1.0, 0.0));
        } 
        glUniformMatrix4fv(s_p->u("M"), 1, false, glm::value_ptr(M));
        Models::torch.Draw(*s_p); //Narysowanie obiektu
}

void draw_ghost(Ghost ghost) {
        glm::mat4 M = glm::mat4(1.0f);
        M = glm::translate(M, ghost.position);

        M = glm::scale(M, glm::vec3(2.0f));

        if (ghost.phase == MovePhase::Left)
                M = glm::rotate(M, PI, glm::vec3(0.0f, 1.0f, 0.0f));
        else if (ghost.phase == MovePhase::Up_Left || ghost.phase == MovePhase::Up_Right)     
                M = glm::rotate(M, PI/2, glm::vec3(0.0f, 1.0f, 0.0f));

        glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M));

        Models::ghost.Draw(*spTextured);
}

void move_ghost(float deltaTime) {
        float movement = speed * deltaTime;

        switch (currentPhase) {
                case MovePhase::Left:
                        for (int i = 0; i < ghosts.size(); i++) {
                                ghosts[i].position += glm::vec3(0.0f, 0.0f, -movement); 
                        }
                        traveled += movement;
                        if (traveled >= (wWidth * lHeight + (wLength * 5))) {
                                currentPhase = MovePhase::Up_Left;
                                for (int i = 0; i < ghosts.size(); i++) ghosts[i].phase = MovePhase::Up_Left;
                                traveled = 0;
                        }
                        break;
                case MovePhase::Up_Left:
                        for (int i = 0; i < ghosts.size(); i++) {
                                ghosts[i].position += glm::vec3(movement, 0.0f, 0.0f); 
                        }
                        traveled += movement;
                        totalTraveled += movement;
                        if (traveled + delta >= wWidth) {
                                currentPhase = MovePhase::Right;
                                for (int i = 0; i < ghosts.size(); i++) ghosts[i].phase = MovePhase::Right;
                                traveled = 0;
                        }
                        break;
                case MovePhase::Right:
                        for (int i = 0; i < ghosts.size(); i++) {
                                ghosts[i].position += glm::vec3(0.0f, 0.0f, movement); 
                        }
                        traveled += movement;
                        if (traveled >= wWidth * lHeight + (wLength * 5)) {
                                currentPhase = MovePhase::Up_Right;
                                for (int i = 0; i < ghosts.size(); i++) ghosts[i].phase = MovePhase::Up_Right;
                                traveled = 0;
                        }
                        break;
                case MovePhase::Up_Right:
                        for (int i = 0; i < ghosts.size(); i++) {
                                ghosts[i].position += glm::vec3(movement, 0.0f, 0.0f);
                        }
                        traveled += movement;
                        totalTraveled += movement;
                        if (traveled + delta >= wWidth) {
                                currentPhase = MovePhase::Left;
                                for (int i = 0; i < ghosts.size(); i++) ghosts[i].phase = MovePhase::Left;
                                traveled = 0;
                        }
                        break;
        }

        if (totalTraveled > wWidth * lWidth) {
                for (int i = 0; i < ghosts.size(); i++) {
                        ghosts[i].position = ghosts[i].startingPosition;
                        ghosts[i].phase = MovePhase::Left;
                        currentPhase = MovePhase::Left;
                } 
                totalTraveled = 0.0f;
                traveled = 0;
        }
}

void draw_treasure() {
        glm::mat4 M = glm::mat4(1.0f);
        M = glm::translate(M, treasure.position);
        M = glm::scale(M, glm::vec3(0.7f));
        M = glm::rotate(M, -PI/2, glm::vec3(1.0f, 0.0f, 0.0f));

        if (treasure.rotate)
                M = glm::rotate(M, PI/2, glm::vec3(0.0f, 0.0f, 1.0f));
        else
                M = glm::rotate(M, -PI/2, glm::vec3(0.0f, 0.0f, 1.0f));

        glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M));

        Models::treasure.Draw(*spTextured);
}

bool porownaj_odleglosci(glm::vec3 p1, glm::vec3 p2){
        glm::vec3 pozycjaObs = obserwator.getPosition();
        return pow(pozycjaObs.x - p1.x, 2) + pow(pozycjaObs.z - p1.z, 2) < pow(pozycjaObs.x - p2.x, 2) + pow(pozycjaObs.z - p2.z, 2);
}
bool porownaj_pochodnie(struct Torch t1, struct Torch t2){
        return porownaj_odleglosci(t1.position, t2.position);
}
float clamp(float value, float min, float max){
        float result = value;
        if(result > max) result = max;
        else if(result < min) result = min;
        return result;
}

void error_callback(int error, const char* description) {
        fputs(description, stderr);
}
void windowResizeCallback(GLFWwindow* window,int width,int height) {
        if (height==0) return;
        aspectRatio=(float)width/(float)height;
        glViewport(0,0,width,height);
        screenwidth = width;
        screenheight = height;
}
void key_repetition_wall_creation(GLFWwindow* window, int key, int scancode, int action, int mod){
        float dx = 0.1;
        float dg = 0.05;

        std::this_thread::sleep_for(std::chrono::milliseconds(250));
	while(GLFW_PRESS==glfwGetKey(window, key)){
                if(key==KEY_MOVE_WALL_X_FORWARD){
                        wall_creator.move_X(-dx);
                }
                else if(key==KEY_MOVE_WALL_X_BACKWARD){
                        wall_creator.move_X(dx);
                }
                else if(key==KEY_MOVE_WALL_Z_FORWARD){
                        wall_creator.move_Z(dx);
                }
                else if(key==KEY_MOVE_WALL_Z_BACKWARD){
                        wall_creator.move_Z(-dx);
                }
                else if(key==KEY_MOVE_WALL_Y_FORWARD){
                        wall_creator.move_Y(dx);
                }
                else if(key==KEY_MOVE_WALL_Y_BACKWARD){
                        wall_creator.move_Y(-dx);
                }
                else if(key==KEY_INC_WALL_GAMMA){
                        wall_creator.changeGamma(dg);
                }
                else if(key==KEY_DEC_WALL_GAMMA){
                        wall_creator.changeGamma(-dg);
                }
                else if(key==KEY_ROTATE_WALL_Y_LEFT){
                        wall_creator.changeAngle_horizontal(dg);
                }
                else if(key==KEY_ROTATE_WALL_Y_RIGHT){
                        wall_creator.changeAngle_horizontal(-dg);
                }
                else if(key==KEY_INC_WALL_LENGTH){
                        wall_creator.changeLength(dx);
                }
                else if(key==KEY_DEC_WALL_LENGTH){
                        wall_creator.changeLength(-dx);
                }
                else if(key==KEY_INC_WALL_WIDTH){
                        wall_creator.changeWidth(dx);
                }
                else if(key==KEY_DEC_WALL_WIDTH){
                        wall_creator.changeWidth(-dx);
                }
                else if(key==KEY_INC_WALL_HEIGHT){
                        wall_creator.changeHeight(dx);
                }
                else if(key==KEY_DEC_WALL_HEIGHT){
                        wall_creator.changeHeight(-dx);
                }
                else if(key==KEY_ROTATE_WALL_Z_LEFT){
                        wall_creator.changeAngle_vertical(dg);
                }
                else if(key==KEY_ROTATE_WALL_Z_RIGHT){
                        wall_creator.changeAngle_vertical(-dg);
                }
                else if(key==KEY_ASSIGN_WALL_NEXT_TEXTURE){
                        wall_creator.assign_next_texture(TEXTURES_WALL);
                }
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}
void key_callback_wall_creation(GLFWwindow* window, int key, int scancode, int action, int mod){
        float dx = 0.1;
        float dg = 0.05;
        if(key==KEY_CREATE_WALL){

        }
        else if(key==KEY_SWITCH_WALL_TYPE){
                wall_creator.switch_wall_type();
        }
        else if(key==KEY_FINISH_WALL_CREATION){
                wall_creator.finish_wall_creation(OBSTACLES);
        }
        else if(key==KEY_ABORT_WALL_CREATION){
                wall_creator.abort_wall_creation();
        }
        else if(key==KEY_MOVE_WALL_X_FORWARD){
                wall_creator.move_X(-dx);
        }
        else if(key==KEY_MOVE_WALL_X_BACKWARD){
                wall_creator.move_X(dx);
        }
        else if(key==KEY_MOVE_WALL_Z_FORWARD){
                wall_creator.move_Z(dx);
        }
        else if(key==KEY_MOVE_WALL_Z_BACKWARD){
                wall_creator.move_Z(-dx);
        }
        else if(key==KEY_MOVE_WALL_Y_FORWARD){
                wall_creator.move_Y(dx);
        }
        else if(key==KEY_MOVE_WALL_Y_BACKWARD){
                wall_creator.move_Y(-dx);
        }
        else if(key==KEY_INC_WALL_GAMMA){
                wall_creator.changeGamma(dg);
        }
        else if(key==KEY_DEC_WALL_GAMMA){
                wall_creator.changeGamma(-dg);
        }
        else if(key==KEY_ROTATE_WALL_Y_LEFT){
                wall_creator.changeAngle_horizontal(dg);
        }
        else if(key==KEY_ROTATE_WALL_Y_RIGHT){
                wall_creator.changeAngle_horizontal(-dg);
        }
        else if(key==KEY_INC_WALL_LENGTH){
                wall_creator.changeLength(dx);
        }
        else if(key==KEY_DEC_WALL_LENGTH){
                wall_creator.changeLength(-dx);
        }
        else if(key==KEY_INC_WALL_WIDTH){
                wall_creator.changeWidth(dx);
        }
        else if(key==KEY_DEC_WALL_WIDTH){
                wall_creator.changeWidth(-dx);
        }
        else if(key==KEY_INC_WALL_HEIGHT){
                wall_creator.changeHeight(dx);
        }
        else if(key==KEY_DEC_WALL_HEIGHT){
                wall_creator.changeHeight(-dx);
        }
        else if(key==KEY_ROTATE_WALL_Z_LEFT){
                wall_creator.changeAngle_vertical(dg);
        }
        else if(key==KEY_ROTATE_WALL_Z_RIGHT){
                wall_creator.changeAngle_vertical(-dg);
        }
        else if(key==KEY_ROTATE_WALL_Z_RIGHT){
                wall_creator.changeAngle_vertical(-dg);
        }
        else if(key==KEY_ASSIGN_WALL_NEXT_TEXTURE){
                wall_creator.assign_next_texture(TEXTURES_WALL);
        }
        std::thread t(key_repetition_wall_creation, window, key, scancode, action, mod);
        t.detach(); 
}
void key_repetition(GLFWwindow* window, int key, int scancode, int action, int mod){
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	while(GLFW_PRESS==glfwGetKey(window, key)){
		if(key==KEY_MOVE_LEFT){
                        if(GLFW_PRESS==glfwGetKey(window, KEY_MOVE_FORWARD)) obserwator.speedup_forward_left();
                        else if(GLFW_PRESS==glfwGetKey(window, KEY_MOVE_BACKWARD)) obserwator.speedup_backward_left();
                        else obserwator.speedup_left();
                } 
		else if(key==KEY_MOVE_RIGHT){
                        if(GLFW_PRESS==glfwGetKey(window, KEY_MOVE_FORWARD)) obserwator.speedup_forward_right();
                        else if(GLFW_PRESS==glfwGetKey(window, KEY_MOVE_BACKWARD)) obserwator.speedup_backward_right();
                        else obserwator.speedup_right();
                } 
		else if(key==KEY_MOVE_FORWARD){
                        if(GLFW_PRESS==glfwGetKey(window, KEY_MOVE_RIGHT)) obserwator.speedup_forward_right();
                        else if(GLFW_PRESS==glfwGetKey(window, KEY_MOVE_LEFT)) obserwator.speedup_forward_left();
                        else obserwator.speedup_forward();
                } 
		else if(key==KEY_MOVE_BACKWARD){
                        if(GLFW_PRESS==glfwGetKey(window, KEY_MOVE_RIGHT)) obserwator.speedup_backward_right();
                        else if(GLFW_PRESS==glfwGetKey(window, KEY_MOVE_LEFT)) obserwator.speedup_backward_left();
                        else obserwator.speedup_backward();
                }
                else if(key==KEY_FLY_DOWN && !gravity_on){
                        obserwator.fly_down();
                }	
                else if(key==KEY_FLY_UP && !gravity_on){
                        obserwator.fly_up();
                }
                else if(key==GLFW_KEY_UP) obserwator.change_angle_vertical(mouse_sensitivity);
                else if(key==GLFW_KEY_DOWN) obserwator.change_angle_vertical(-mouse_sensitivity);
                else if(key==GLFW_KEY_RIGHT) obserwator.change_angle_horizontal(mouse_sensitivity);
                else if(key==GLFW_KEY_LEFT) obserwator.change_angle_horizontal(-mouse_sensitivity);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mod){
        if(action == GLFW_PRESS) {
                if(key == KEY_MOVE_LEFT){
			obserwator.speedup_left();
                }
                else if(key == KEY_MOVE_RIGHT){
                        obserwator.speedup_right();	
                }
                else if(key == KEY_MOVE_FORWARD){
			obserwator.speedup_forward();
                }
                else if(key == KEY_MOVE_BACKWARD){
                        obserwator.speedup_backward();	
                }
                else if(key==KEY_FLY_DOWN && !gravity_on){
                        obserwator.fly_down();
                }
                else if(key==KEY_FLY_UP && !gravity_on){
                        obserwator.fly_up();
                }
                else if(key == KEY_OPEN_CLOSE_MENU){
                        glfwSetCursorPos(window, screenwidth/2, screenheight/2);
                        cursor_centred = !cursor_centred;
                }
                else if(wall_creator.is_creating_wall) key_callback_wall_creation(window, key, scancode, action, mod);
                else if(key == KEY_CREATE_WALL) wall_creator.is_creating_wall = true;
                else if(key==KEY_TURN_ON_OFF_GRAVITY){
                        gravity_on = !gravity_on;
                        obserwator.setVelocity(glm::vec3(0.0, 0.0, 0.0));
                }
                else if(key==KEY_MOVE_JUMP)  obserwator.jump();
                else if(key==KEY_INC_MOUSE_SENSITIVITY) mouse_sensitivity *= 2;
                else if(key==KEY_DEC_MOUSE_SENSITIVITY) mouse_sensitivity *= 0.5;
                else if(key==GLFW_KEY_UP) obserwator.change_angle_vertical(mouse_sensitivity);
                else if(key==GLFW_KEY_DOWN) obserwator.change_angle_vertical(-mouse_sensitivity);
                else if(key==GLFW_KEY_RIGHT) obserwator.change_angle_horizontal(mouse_sensitivity);
                else if(key==GLFW_KEY_LEFT) obserwator.change_angle_horizontal(-mouse_sensitivity);
		else if(key==GLFW_KEY_RIGHT_SHIFT) mouse_button_callback();

		std::thread t(key_repetition, window, key, scancode, action, mod);
		t.detach(); 
        }
        else if(action == GLFW_RELEASE){
                if(key == KEY_MOVE_LEFT || key == KEY_MOVE_RIGHT || key == KEY_MOVE_FORWARD || key == KEY_MOVE_BACKWARD || key == KEY_FLY_DOWN || key == KEY_FLY_UP){
                        if(gravity_on) obserwator.setVelocity_horizontal(glm::vec2(0.0, 0.0));
                        else obserwator.setVelocity(glm::vec3(0.0, 0.0, 0.0));
                }
        }
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
        //double dx = xpos - screenwidth/2;
        //double dy = ypos - screenheight/2;

        //if(cursor_centred){
                //obserwator.change_angle_horizontal(dx * mouse_sensitivity);
                //obserwator.change_angle_vertical(-dy * mouse_sensitivity);
                //glfwSetCursorPos(window, screenwidth/2, screenheight/2);
        //}
}

//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
void mouse_button_callback() {
	//if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
                int selectedIndex = -1;
                float closestT = 1e9;

                for (int i = 0; i < fences.size(); ++i) {
                        float t;
                        if (fences[i].is_clicked_on(obserwator.getCameraPosition(), obserwator.getCameraViewVector(), t)) {
                                if (t < closestT && t < zasieg_reki) {
                                        closestT = t;
                                        selectedIndex = i;
                                }
                        }
                }
                // Wyznacz najbliższy
                if(selectedIndex!=-1){
                        fences[selectedIndex].setIsSelected(true);
                        fences[selectedIndex].change_height(floorThickness+wallHeight);
                        return;
                }
                
                selectedIndex = -1;
                closestT = 1e9;
                for (int i = 0; i < doors.size(); ++i) {
                        float t;
                        if (doors[i].is_clicked_on(obserwator.getCameraPosition(), obserwator.getCameraViewVector(), t)) {
                                if (t < closestT) {
                                        closestT = t;
                                        selectedIndex = i;
                                }
                        }
                }
                // Wyznacz najbliższy
                if(selectedIndex!=-1){
                        doors[selectedIndex].open_close();
                        return;
                }

                selectedIndex = -1;
                closestT = 1e9;
                for (int i = 0; i < paintings.size(); ++i) {
                        float t;
                        if (paintings[i].is_clicked_on(obserwator.getCameraPosition(), obserwator.getCameraViewVector(), t)) {
                                if (t < closestT) {
                                        closestT = t;
                                        selectedIndex = i;
                                }
                        }
                }

                if(selectedIndex!=-1){
                        if (!paintings[selectedIndex].getOnFloor()) {}
                                paintings[selectedIndex].change_height(wallHeight / 2);
                        return;
                }
        //}
}
GLuint readTexture(const char* scianyname) {
        GLuint tex;
        glActiveTexture(GL_TEXTURE0);

        //Wczytanie do pamięci komputera
        std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
        unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
        //Wczytaj obrazek
        //unsigned error = 
        lodepng::decode(image, width, height, scianyname);

        //Import do pamięci karty graficznej
        glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
        glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
        //Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
        glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());
        glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);

        return tex;
}
void initOpenGLProgram(GLFWwindow* window) {
        initShaders();
        //************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
        glClearColor(0, 0, 0, 1); //Ustaw kolor czyszczenia bufora kolorów
        glEnable(GL_DEPTH_TEST); //Włącz test głębokości na pikselach

        glfwSetKeyCallback(window, key_callback);
        glfwSetCursorPosCallback(window, cursor_position_callback);
        glfwSetWindowSizeCallback(window,windowResizeCallback);
        //glfwSetMouseButtonCallback(window, mouse_button_callback);

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetCursorPos(window, screenwidth/2, screenheight/2);

        //TEXTURES.push_back(readTexture("assests/textures/drewno.png"));
        TEXTURES_WALL.push_back(readTexture("assests/textures/walls/bricks.png"));
        TEXTURES_WALL.push_back(readTexture("assests/textures/walls/bricks_02.png"));
        TEXTURES_WALL.push_back(readTexture("assests/textures/walls/bricks_03.png"));
        TEXTURES_WALL.push_back(readTexture("assests/textures/walls/bricks_04.png"));
        TEXTURES_WALL.push_back(readTexture("assests/textures/walls/stone_wall_01.png"));
        TEXTURES_WALL.push_back(readTexture("assests/textures/walls/stone_wall_02.png"));
        TEXTURES_WALL.push_back(readTexture("assests/textures/walls/stone_tiles.png"));
        TEXTURES_WALL.push_back(readTexture("assests/textures/walls/marble.png"));
        TEXTURES_WALL.push_back(readTexture("assests/textures/walls/cobblestone.png"));
        TEXTURES_WALL.push_back(readTexture("assests/textures/walls/rocks.png"));
        //TEXTURES_FLOOR.push_back(readTexture("assests/textures/floors/deski.png"));
        TEXTURES_FLOOR.push_back(readTexture("assests/textures/floors/ground_01.png"));
        TEXTURES_FLOOR.push_back(readTexture("assests/textures/floors/ground_02.png"));
        TEXTURES_FLOOR.push_back(readTexture("assests/textures/floors/bricks_01.png"));
        TEXTURES_FLOOR.push_back(readTexture("assests/textures/floors/bricks_02.png"));
        TEXTURES_FLOOR.push_back(readTexture("assests/textures/floors/ground_square.png"));
        TEXTURES_FLOOR.push_back(readTexture("assests/textures/floors/rock.png"));
        TEXTURES_FLOOR.push_back(readTexture("assests/textures/floors/dirt.png"));
        TEXTURES_FLOOR.push_back(readTexture("assests/textures/floors/wood.png"));
        TEXTURES_FLOOR.push_back(readTexture("assests/textures/floors/tiles.png"));


        wall_creator.assign_next_texture(TEXTURES_WALL);
        sp = new ShaderProgram("shaders/v_test.glsl", NULL, "shaders/f_test.glsl");
        observers_light = new ShaderProgram("shaders/v_distanced.glsl", NULL, "shaders/f_distanced.glsl");

        Models::loadTorch();
        Models::loadFence();
        Models::loadSpider();
        Models::loadGhost();
        Models::loadDoor();
        Models::loadTreasure();
        Models::loadPainting();
}

void freeOpenGLProgram(GLFWwindow* window) {
        freeShaders();
        //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************
        for(unsigned int i=0;i<TEXTURES_WALL.size();i++) glDeleteTextures(1, &TEXTURES_WALL[i]);
        for(unsigned int i=0;i<TEXTURES_FLOOR.size();i++) glDeleteTextures(1, &TEXTURES_FLOOR[i]);
}

void prepareMoveables(){
        obserwator.setRadius(0.02);
        obserwator.setPosition(-15, 1, 4);
        obserwator.setVelocity_value(7.0);
}
void prepareScene(){
        torches.resize(numberOfFloors);
        int labyrinthHeight = 10, labyrinthWidth = 10;
        float wallLength = 1.0f, wallWidth = 7.0f;

        wLength = wallLength; wWidth = wallWidth; lHeight = labyrinthHeight; lWidth = labyrinthWidth;
        
        for (int i = 0; i < numberOfFloors; i++) {
                srand(std::chrono::high_resolution_clock::now().time_since_epoch().count() + i * 1337);
                unsigned short rand_floor_texture_id = rand() % TEXTURES_FLOOR.size();
                unsigned short rand_wall_texture_id = rand() % TEXTURES_WALL.size();

                Labyrinth labyrinth = Labyrinth(labyrinthHeight, labyrinthWidth);
                labyrinth.print();
                labyrinth.generateCoordinates(i, wallLength, wallHeight, wallWidth, floorThickness, doorHeight/1.5, maxTorchesPerFloor);

                ifstream sciany("input/labyrinth_" + to_string(i) + ".txt");
                ifstream podlogi("input/floors_" + to_string(i) + ".txt");
                ifstream rampy("input/rampy_" + to_string(i) + ".txt");
                ifstream pochodnie("input/pochodnie_"+ to_string(i) + ".txt");
                ifstream kraty("input/kraty_"+ to_string(i) + ".txt");
                ifstream duchy("input/duchy_"+ to_string(i) + ".txt");
                ifstream obrazy("input/obrazy_"+ to_string(i) + ".txt");
                string line;

                while (getline(sciany, line)) {
                        istringstream iss(line);
                        float xl, yd, zb, dlugosc, wysokosc, szerokosc;
                        int horizontal;

                        if (iss >> xl >> yd >> zb >> dlugosc >> wysokosc >> szerokosc >> horizontal) {
                                //printf("xl = %lf, yd = %lf, zb = %lf, d = %lf, w = %lf, s = %lf, h = %d\n", xl, yd, zb, dlugosc, wysokosc, szerokosc, horizontal);

                                Wall_rect mur;
                                mur = Wall_rect(xl, yd, zb, dlugosc, wysokosc, szerokosc);
                                mur.setAngle_vertical(0);
                                mur.setTexture(TEXTURES_WALL[rand_wall_texture_id]);
                                if (horizontal) mur.setAngle_horizontal(PI/2); else mur.setAngle_horizontal(0);
                                obstacles_rect.push_back(mur);
                        }
                }

                while (getline(podlogi, line)) {
                        istringstream iss(line);
                        float xl, yd, zb, dlugosc, wysokosc, szerokosc;
                        bool obrot;

                        if (iss >> xl >> yd >> zb >> dlugosc >> wysokosc >> szerokosc >> obrot){
                                
                                float step = 8.0;
                                for(short iw=0;iw<1+szerokosc/step;iw++) for(short il=0;il<1+dlugosc/step;il++){ // fragmentator zbyt dużych kawałków podłogi
                                        //printf("iw=%hd,  il=%hd\n", iw, il);
                                        Wall_rect podloga;
                                        podloga = Wall_rect(xl+step*il, yd, zb+step*iw, clamp(dlugosc-step*il, 0.0, step), wysokosc, clamp(szerokosc-step*iw, 0.0, step));
                                        podloga.setAngle_vertical(0);
                                        if(!obrot) podloga.setAngle_horizontal(0); else podloga.setAngle_horizontal(PI/2);
                                        podloga.setTexture(TEXTURES_FLOOR[rand_floor_texture_id]);
                                        obstacles_rect.push_back(podloga);
                                }
                                        
                                /*
                                Wall_rect podloga;
                                podloga = Wall_rect(xl, yd, zb, dlugosc, wysokosc, szerokosc);
                                podloga.setAngle_vertical(0);
                                if(!obrot) podloga.setAngle_horizontal(0); else podloga.setAngle_horizontal(PI/2);
                                podloga.setTexture(TEXTURES_FLOOR[rand_floor_texture_id]);
                                obstacles_rect.push_back(podloga);
                                */
                        }
                }

                while (getline(rampy, line)) {
                        istringstream iss(line);
                        float xl, yd, zb, dlugosc, wysokosc, szerokosc;
                        int klatka;

                        if (iss >> xl >> yd >> zb >> dlugosc >> wysokosc >> szerokosc >> klatka) {
                                //printf("xl = %lf, yd = %lf, zb = %lf, d = %lf, w = %lf, s = %lf\n", xl, yd, zb, dlugosc, wysokosc, szerokosc);

                                Ramp rampa = Ramp(glm::vec3(xl, yd, zb), dlugosc, wysokosc, szerokosc);
                                if (!klatka) rampa.setAngle_horizontal(3*PI/2); else rampa.setAngle_horizontal(PI/2);
                                rampa.setTexture(TEXTURES_WALL[rand_wall_texture_id]);
                                ramps.push_back(rampa);
                        }
                }

                
                while (getline(pochodnie, line)) {
                        istringstream iss(line);
                        float x, y, z;
                        char f;

                        if (iss >> x >> y >> z >> f) {
                                Torch tmp;
                                tmp.position = glm::vec3(x,y,z);
                                tmp.facing = f;
                                torches[i].push_back(tmp);
                        }
                }

                while (getline(kraty, line)) {
                        istringstream iss(line);
                        float x, y, z;
                        bool rotate;

                        if (iss >> x >> y >> z >> rotate) {
                                if(!rotate){
                                        Fence tmp(glm::vec3(x, y, z));
                                        tmp.setAngle_horizontal(0);
                                        fences.push_back(tmp);
                                }
                                else{
                                        Door tmp(glm::vec3(x,y,z), doorHeight);
                                        tmp.setAngle_horizontal(0);
                                        doors.push_back(tmp);
                                }
                        }
                }

                while (getline(duchy, line)) {
                        istringstream iss(line);
                        float x, y, z;

                        if (iss >> x >> y >> z) {
                                Ghost ghost;
                                ghost.position = glm::vec3(x, y, z);
                                ghost.startingPosition = glm::vec3(x, y, z);
                                ghosts.push_back(ghost);
                        }
                }

                while (getline(obrazy, line)) {
                        istringstream iss(line);
                        float x, y, z;
                        short unsigned facing;

                        if (iss >> x >> y >> z >> facing) {
                                Painting painting(glm::vec3(x, y, z), facing);
                                
                                paintings.push_back(painting);
                        }
                }
                

                sciany.close();
                podlogi.close();
                rampy.close();
                pochodnie.close();
                kraty.close();
                duchy.close();
                obrazy.close();
        }

        ifstream skarb("input/skarb.txt");
        string line;
        while (getline(skarb, line)) {
                istringstream iss(line);
                float x, y, z;
                bool rotate;

                if (iss >> x >> y >> z >> rotate) {
                        treasure.position = glm::vec3(x, y, z);
                        treasure.rotate = rotate;
                }
        }
        skarb.close();

        for(unsigned int i=0;i<obstacles_rect.size();i++) OBSTACLES.push_back(&obstacles_rect[i]);
        for(unsigned int i=0;i<obstacles_tr.size();i++) OBSTACLES.push_back(&obstacles_tr[i]);
        for(unsigned int i=0;i<ramps.size();i++) OBSTACLES.push_back(&ramps[i]);
        for(unsigned int i=0;i<fences.size();i++) OBSTACLES.push_back(&fences[i]);
        for(unsigned int i=0;i<doors.size();i++) OBSTACLES.push_back(&doors[i]);
        for(unsigned int i=0;i<paintings.size();i++) OBSTACLES.push_back(&paintings[i]);
}

void drawScene(GLFWwindow* window, float dt){
        static double time = 0;
        time += dt;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wyczyść bufor koloru i bufor głębokości
        short current_floor = 0;//clamp(obserwator.getPosition().y / wallHeight, 0.0, numberOfFloors-1);
        sort(torches[current_floor].begin(), torches[current_floor].end(), porownaj_pochodnie);

        glm::mat4 M = glm::mat4(1.0f); //Zainicjuj macierz modelu macierzą jednostkową
        glm::mat4 V = glm::lookAt(obserwator.getCameraPosition(), obserwator.getLookAtPoint(), glm::vec3(0.0f, 1.0f, 0.0f)); //Wylicz macierz widoku
        glm::mat4 P = glm::perspective(glm::radians(50.0f), aspectRatio, zNear, zFar); //Wylicz macierz rzutowania
        
        for(unsigned int i=0;i<torches[current_floor].size();i++){
               draw_torch(torches[current_floor][i], observers_light);
        }
        for (int i = 0; i < ghosts.size(); i++) {
                draw_ghost(ghosts[i]);
        }


        glUniform4f(observers_light->u("camera_position"), obserwator.getCameraPosition().x, obserwator.getCameraPosition().y, obserwator.getCameraPosition().z, 0.0);
        for(unsigned short i=0;i<torches[current_floor].size();i++){
		std::string var_name = "torches[X]";
                var_name[8] = 48 + i;
                glUniform4f(observers_light->u(var_name.c_str()), torches[current_floor][i].position.x, torches[current_floor][i].position.y, torches[current_floor][i].position.z, 0.0);
        }
        glUniform1f(observers_light->u("light_power"), (float)(3.5+1.0*sin(time/2)));
        for(unsigned int i=0;i<OBSTACLES.size();i++){
                OBSTACLES[i]->draw(P, V, observers_light);
        }
        //if(wall_creator.is_creating_wall) wall_creator.current_wall->draw(P, V, spLambertSun);

        draw_treasure();
        
        glfwSwapBuffers(window); //Skopiuj bufor tylny do bufora przedniego
}

int main(void){
        srand(time(NULL));

        GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

        glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

        if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
                fprintf(stderr, "Nie można zainicjować GLFW.\n");
                exit(EXIT_FAILURE);
        }

        window = glfwCreateWindow(screenwidth, screenheight, "Katakumby", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

        if(!window){
                fprintf(stderr, "Nie można utworzyć okna.\n");
                glfwTerminate();
                exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
        glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

        if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
                fprintf(stderr, "Nie można zainicjować GLEW.\n");
                exit(EXIT_FAILURE);
        }

        initOpenGLProgram(window); //Operacje inicjujące

        prepareScene();
        prepareMoveables();

        //Główna pętla
        float dt = 0;
        glfwSetTime(0); //Wyzeruj licznik czasu
        while (!glfwWindowShouldClose(window)){
                if(!cursor_centred) dt = 0.0;
                else dt = glfwGetTime();
                glfwSetTime(0); //Wyzeruj licznik czasu

                drawScene(window, dt); //Wykonaj procedurę rysującą
                glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
                // if(cursor_centred) printf("pos= %f %f %f\n", obserwator.getPosition().x, obserwator.getPosition().y, obserwator.getPosition().z);

                move_ghost(dt);

                if(gravity_on){
                        obserwator.fall(dt, OBSTACLES);
                        obserwator.move(dt, OBSTACLES);
                } 
                else{
                        static std::vector<Obstacle*> brak_przeszkod;
                        obserwator.move(dt, brak_przeszkod);
                }

                for(unsigned short i=0;i<fences.size();i++) fences[i].move(dt);
                for(unsigned short i=0;i<doors.size();i++) doors[i].move(dt);
                for(unsigned short i=0;i<paintings.size();i++) paintings[i].move(dt);
        }

        freeOpenGLProgram(window);

        glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
        glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
        exit(EXIT_SUCCESS);
}
