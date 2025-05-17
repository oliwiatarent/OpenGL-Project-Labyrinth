LIBS=-lGL -lglfw -lGLEW
HEADERS=models/allmodels.h constants.h models/cube.h lodepng.h models/model.h models/myCube.h shaders/shaderprogram.h models/sphere.h models/teapot.h models/torus.h moveable.h wall.h key-funcs.h
FILES=models/cube.cpp lodepng.cpp main_file.cpp models/model.cpp shaders/shaderprogram.cpp models/sphere.cpp models/teapot.cpp models/torus.cpp moveable.cpp wall.cpp labyrinth.cpp
main_file: $(FILES) $(HEADERS)
	g++ -Ofast -o main_file.exe $(FILES)  $(LIBS) -I.
