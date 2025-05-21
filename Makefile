LIBS=-lGL -lglfw -lGLEW -lassimp -ldraco 
HEADERS=stb_image.h models/allmodels.h constants.h models/cube.h lodepng.h models/model.h models/myCube.h shaders/shaderprogram.h models/sphere.h models/teapot.h models/torus.h models/torch.h models/fence.h models/spider.h models/ghost.h moveable.h wall.h key-funcs.h
FILES=stb_image.cpp models/cube.cpp lodepng.cpp main_file.cpp models/model.cpp shaders/shaderprogram.cpp models/sphere.cpp models/teapot.cpp models/torus.cpp models/torch.cpp models/fence.cpp models/spider.cpp models/ghost.cpp moveable.cpp wall.cpp labyrinth.cpp externalmodel.cpp
main_file: $(FILES) $(HEADERS)
	g++ -Ofast -o main_file.exe $(FILES)  $(LIBS) -I.
