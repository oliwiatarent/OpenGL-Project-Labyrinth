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

using namespace std;

float zNear = 0.05; // bliższa odległość odcinania
float zFar = 100.0; // dalsza odległość odcinania
float mouse_sensitivity = 0.001; // czułość myszy


unsigned short screenwidth = 500;
unsigned short screenheight = 500;
float aspectRatio = 1.0;
bool cursor_centred = true;
bool gravity_on = false;

std::vector<GLuint> TEXTURES;
std::vector<Wall_rect> obstacles_rect;
std::vector<Wall_trian> obstacles_tr;
std::vector<Ramp> ramps;
std::vector<Wall*> OBSTACLES;
Wall_creator wall_creator;
Observer obserwator;

ShaderProgram* sp;
ShaderProgram* observers_light;

float clamp(float value, float min, float max){
        float result = value;
        if(result > max) result = max;
        else if(result < min) result = min;
        return result;
}

//Procedura obsługi błędów
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
                        wall_creator.assign_next_texture(TEXTURES);
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
                wall_creator.assign_next_texture(TEXTURES);
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
        double dx = xpos - screenwidth/2;
        double dy = ypos - screenheight/2;

        if(cursor_centred){
                obserwator.change_angle_horizontal(dx * mouse_sensitivity);
                obserwator.change_angle_vertical(-dy * mouse_sensitivity);
                glfwSetCursorPos(window, screenwidth/2, screenheight/2);
        }
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

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetCursorPos(window, screenwidth/2, screenheight/2);

        TEXTURES.push_back(readTexture("assests/textures/marble.png"));
                //TEXTURES.push_back(readTexture("assests/textures/rock.png"));
        TEXTURES.push_back(readTexture("assests/textures/bricks.png"));
        TEXTURES.push_back(readTexture("assests/textures/drewno.png"));
        wall_creator.assign_next_texture(TEXTURES);
        sp = new ShaderProgram("shaders/v_test.glsl", NULL, "shaders/f_test.glsl");
        observers_light = new ShaderProgram("shaders/v_distanced.glsl", NULL, "shaders/f_distanced.glsl");
}

//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
        freeShaders();
        //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************
        for(unsigned int i=0;i<TEXTURES.size();i++) glDeleteTextures(1, &TEXTURES[i]);
}

void prepareMoveables(){
        obserwator.setRadius(0.02);
        obserwator.setPosition(-4, 1, 4);
        obserwator.setVelocity_value(10);
}

int numberOfFloors = 3;
void prepareScene() {
        int labyrinthHeight = 10, labirynthWidth = 10;
        float wallLength = 1.0f, wallHeight = 9.0f, wallWidth = 7.0f;
        
        for (int i = 0; i < numberOfFloors; i++) {
                srand(std::chrono::high_resolution_clock::now().time_since_epoch().count() + i * 1337);

                Labyrinth labyrinth = Labyrinth(labyrinthHeight, labirynthWidth);
                // labyrinth.print();
                labyrinth.generateCoordinates(i, wallLength, wallHeight, wallWidth);

                ifstream sciany("input/labyrinth_" + to_string(i) + ".txt");
                ifstream podlogi("input/floors_" + to_string(i) + ".txt");
                ifstream rampy("input/rampy_" + to_string(i) + ".txt");
                string line;

                while (getline(sciany, line)) {
                        istringstream iss(line);
                        float xl, yd, zb, dlugosc, wysokosc, szerokosc;
                        int horizontal;

                        if (iss >> xl >> yd >> zb >> dlugosc >> wysokosc >> szerokosc >> horizontal) {
                                printf("xl = %lf, yd = %lf, zb = %lf, d = %lf, w = %lf, s = %lf, h = %d\n", xl, yd, zb, dlugosc, wysokosc, szerokosc, horizontal);

                                Wall_rect mur;
                                mur = Wall_rect(xl, yd, zb, dlugosc, wysokosc, szerokosc);
                                mur.setAngle_vertical(0);
                                mur.setTexture(TEXTURES[1]);
                                if (horizontal) mur.setAngle_horizontal(PI/2); else mur.setAngle_horizontal(0);
                                obstacles_rect.push_back(mur);
                        }
                }

                while (getline(podlogi, line)) {
                        istringstream iss(line);
                        float xl, yd, zb, dlugosc, wysokosc, szerokosc;

                        if (iss >> xl >> yd >> zb >> dlugosc >> wysokosc >> szerokosc) {
                                printf("xl = %lf, yd = %lf, zb = %lf, d = %lf, w = %lf, s = %lf\n", xl, yd, zb, dlugosc, wysokosc, szerokosc);

                                float step = 5.0;
                                for(short iw=0;iw<1+szerokosc/step;iw++) for(short il=0;il<1+dlugosc/step;il++){
                                        //printf("iw=%hd,  il=%hd\n", iw, il);
                                        Wall_rect podloga;
                                        podloga = Wall_rect(xl+step*il, yd, zb+step*iw, clamp(dlugosc-step*il, 0.0, 5.0), wysokosc, clamp(szerokosc-step*iw, 0.0, 5.0));
                                        podloga.setAngle_vertical(0);
                                        podloga.setAngle_horizontal(0);
                                        podloga.setTexture(TEXTURES[1]);
                                        obstacles_rect.push_back(podloga);
                                }
                        }
                }

                while (getline(rampy, line)) {
                        istringstream iss(line);
                        float xl, yd, zb, dlugosc, wysokosc, szerokosc;
                        int klatka;

                        if (iss >> xl >> yd >> zb >> dlugosc >> wysokosc >> szerokosc >> klatka) {
                                printf("xl = %lf, yd = %lf, zb = %lf, d = %lf, w = %lf, s = %lf\n", xl, yd, zb, dlugosc, wysokosc, szerokosc);

                                Ramp rampa = Ramp(glm::vec3(xl, yd, zb), dlugosc, wysokosc, szerokosc);
                                if (!klatka) rampa.setAngle_horizontal(3*PI/2); else rampa.setAngle_horizontal(PI/2);
                                rampa.setTexture(TEXTURES[1]);
                                ramps.push_back(rampa);
                        }
                }

                sciany.close();
                podlogi.close();
                rampy.close();

        }

        Ramp ranp(glm::vec3(-14, 0.0, -14), 5, 5, 5);
        ramps.push_back(ranp);

        for(unsigned int i=0;i<obstacles_rect.size();i++) OBSTACLES.push_back(&obstacles_rect[i]);
        for(unsigned int i=0;i<obstacles_tr.size();i++) OBSTACLES.push_back(&obstacles_tr[i]);
        for(unsigned int i=0;i<ramps.size();i++) OBSTACLES.push_back(&ramps[i]);
}

void drawScene(GLFWwindow* window, float dt){
        static double time = 0;
        time += dt;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wyczyść bufor koloru i bufor głębokości

        glm::mat4 M = glm::mat4(1.0f); //Zainicjuj macierz modelu macierzą jednostkową
        glm::mat4 V = glm::lookAt(obserwator.getCameraPosition(), obserwator.getLookAtPoint(), glm::vec3(0.0f, 1.0f, 0.0f)); //Wylicz macierz widoku
        glm::mat4 P = glm::perspective(glm::radians(50.0f), aspectRatio, zNear, zFar); //Wylicz macierz rzutowania

        glUniform4f(observers_light->u("camera_position"), obserwator.getCameraPosition().x, obserwator.getCameraPosition().y, obserwator.getCameraPosition().z, 0.0);
        glUniform1f(observers_light->u("light_power"), (float)(5.0+1.0*sin(time)));
        for(unsigned int i=0;i<OBSTACLES.size();i++){
                OBSTACLES[i]->draw(P, V, observers_light);
        }
        if(wall_creator.is_creating_wall) wall_creator.current_wall->draw(P, V, spLambertSun);

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
                dt = glfwGetTime();
                glfwSetTime(0); //Wyzeruj licznik czasu

                drawScene(window, dt); //Wykonaj procedurę rysującą
                glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
                if(cursor_centred) printf("pos= %f %f %f\n", obserwator.getPosition().x, obserwator.getPosition().y, obserwator.getPosition().z);

                if(gravity_on) obserwator.fall(dt, OBSTACLES);
                obserwator.move(dt, OBSTACLES);
        }

        freeOpenGLProgram(window);

        glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
        glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
        exit(EXIT_SUCCESS);
}