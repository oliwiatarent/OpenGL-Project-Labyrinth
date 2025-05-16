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
#include "myCube.h"
#include "constants.h"
#include "allmodels.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "moveable.h"
#include "wall.h"
#include "key-funcs.h"

unsigned short screenwidth = 500;
unsigned short screenheight = 500;
float aspectRatio = 1.0;
bool cursor_centred = true;
bool gravity_on = true;

std::vector<GLuint> TEXTURES;
std::vector<Wall_rect> obstacles_rect;
std::vector<Wall_trian> obstacles_tr;
std::vector<Ramp> ramps;
std::vector<Wall*> OBSTACLES;
Wall_creator wall_creator;
Observer obserwator;

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
                obserwator.change_angle_horizontal(dx * 0.001);
                obserwator.change_angle_vertical(-dy * 0.001);
                glfwSetCursorPos(window, screenwidth/2, screenheight/2);
        }
}

GLuint readTexture(const char* filename) {
        GLuint tex;
        glActiveTexture(GL_TEXTURE0);

        //Wczytanie do pamięci komputera
        std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
        unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
        //Wczytaj obrazek
        //unsigned error = 
        lodepng::decode(image, width, height, filename);

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

ShaderProgram* sp;
//Procedura inicjująca
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
        TEXTURES.push_back(readTexture("assests/textures/bricks.png"));
        wall_creator.assign_next_texture(TEXTURES);
        sp = new ShaderProgram("v_test.glsl", NULL, "f_test.glsl");
}

//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
        freeShaders();
        //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************
        for(unsigned int i=0;i<TEXTURES.size();i++) glDeleteTextures(1, &TEXTURES[i]);
}

void prepareMoveables(){
        obserwator.setRadius(0.02);
        obserwator.setPosition(-3, 1, -3);
        obserwator.setVelocity_value(5);
}

void prepareScene(){
        Wall_rect mur;
        mur = Wall_rect(2, 0, 3, 1, 5, 7);
        mur.setAngle_horizontal(PI/6);
        mur.setAngle_vertical(0);
        mur.setTexture(TEXTURES[0]);
        obstacles_rect.push_back(mur);

        Wall_trian murek = Wall_trian(glm::vec3(6.0, 0.0, 6.0), 3, 4, 5, PI/2);
        murek.setAngle_vertical(PI/2);
        //murek.setAngle_horizontal(PI/2);
        murek.setTexture(TEXTURES[0]);
        obstacles_tr.push_back(murek);

        Ramp rampa(glm::vec3(0.0, 0.0, 0.0), 2, 5, 7.5);
        rampa.setTexture(TEXTURES[0]);
        ramps.push_back(rampa);

        rampa = Ramp(glm::vec3(-10.0, 0.0, -10.0), 3, 3, 3*sqrt(3)-1);
        rampa.setTexture(TEXTURES[0]);
        ramps.push_back(rampa);

        rampa = Ramp(glm::vec3(-20.0, 0.0, -20.0), 3, 3, 3*sqrt(3)+1);
        rampa.setTexture(TEXTURES[0]);
        ramps.push_back(rampa);

        for(unsigned int i=0;i<obstacles_rect.size();i++) OBSTACLES.push_back(&obstacles_rect[i]);
        for(unsigned int i=0;i<obstacles_tr.size();i++) OBSTACLES.push_back(&obstacles_tr[i]);
        for(unsigned int i=0;i<ramps.size();i++) OBSTACLES.push_back(&ramps[i]);
}

void drawScene(GLFWwindow* window) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wyczyść bufor koloru i bufor głębokości

        glm::mat4 M = glm::mat4(1.0f); //Zainicjuj macierz modelu macierzą jednostkową
        glm::mat4 V = glm::lookAt(obserwator.getCameraPosition(), obserwator.getLookAtPoint(), glm::vec3(0.0f, 1.0f, 0.0f)); //Wylicz macierz widoku
        glm::mat4 P = glm::perspective(glm::radians(50.0f), aspectRatio, 0.01f, 50.0f); //Wylicz macierz rzutowania

        for(unsigned int i=0;i<OBSTACLES.size();i++) OBSTACLES[i]->draw(P, V, spLambertSun);
        if(wall_creator.is_creating_wall) wall_creator.current_wall->draw(P, V, spLambertSun);

        glfwSwapBuffers(window); //Skopiuj bufor tylny do bufora przedniego
}

int main(void){
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

                drawScene(window); //Wykonaj procedurę rysującą
                glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
                printf("pos= %f %f %f\nlookAt %f %f %f\nah=%f,  av=%f\n\n", obserwator.getPosition().x, obserwator.getPosition().y, obserwator.getPosition().z, obserwator.getLookAtPoint().x, obserwator.getLookAtPoint().y, obserwator.getLookAtPoint().z, obserwator.getAngle_horizontal(), obserwator.getAngle_vertical());

                if(gravity_on) obserwator.fall(dt, OBSTACLES);
                obserwator.move(dt, OBSTACLES);
        }

        freeOpenGLProgram(window);

        glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
        glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
        exit(EXIT_SUCCESS);
}