LIBS=-lGL -lglfw -lGLEW -lassimp -ldraco 
HEADERS = stb_image.h models/allmodels.h constants.h models/cube.h lodepng.h models/model.h models/myCube.h shaders/shaderprogram.h models/sphere.h models/teapot.h models/torus.h models/torch/torch.h models/fence/fence.h models/spider/spider.h models/ghost/ghost.h models/door/door.h models/treasure/treasure.h models/painting/painting.h moveable.h wall.h key-funcs.h
FILES = stb_image.cpp models/cube.cpp lodepng.cpp main_file.cpp models/model.cpp shaders/shaderprogram.cpp models/sphere.cpp models/teapot.cpp models/torus.cpp  models/torch/torch.cpp models/fence/fence.cpp models/spider/spider.cpp models/ghost/ghost.cpp models/door/door.cpp models/treasure/treasure.cpp models/painting/painting.cpp moveable.cpp wall.cpp labyrinth.cpp externalmodel.cpp
main_file: $(FILES) $(HEADERS)
	g++ -Ofast -o main_file.exe $(FILES)  $(LIBS) -I.
