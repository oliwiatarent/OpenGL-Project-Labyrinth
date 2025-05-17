LIBS=-lGL -lglfw -lGLEW
HEADERS=allmodels.h constants.h cube.h lodepng.h model.h myCube.h shaders/shaderprogram.h sphere.h teapot.h torus.h moveable.h wall.h key-funcs.h
FILES=cube.cpp lodepng.cpp main_file.cpp model.cpp shaders/shaderprogram.cpp sphere.cpp teapot.cpp torus.cpp moveable.cpp wall.cpp labyrinth.cpp
main_file: $(FILES) $(HEADERS)
	g++ -Ofast -o main_file.exe $(FILES)  $(LIBS) -I.
