CC = g++
CFLAGS = -Wall
GLLIBS = -lglut -lGLEW -lGL -lGLU 
FILES = ../lib/utils.cpp glut-tutorial.cpp input.cpp colors.cpp gutils.cpp shadersUtils.cpp renderScene.cpp
OBJFILES = glut-tutorial.o input.o colors.o gutils.o shadersUtils.o window.o renderScene.o
TARGET = glut-tutorial

glut-tutorial : $(OBJFILES) 
	@echo "Linking glut-tutorial..."
	$(CC) -o glut-tutorial $(OBJFILES) $(GLLIBS)
	@echo "Done!\n"

glut-tutorial.o: src/glut-tutorial.cpp
	@echo "Compiling $@..."
	$(CC) -c src/glut-tutorial.cpp ../lib/utils.cpp 
	@echo "Done!\n"

input.o: src/input.cpp
	@echo "Compiling $@..."
	$(CC) -c src/input.cpp ../lib/utils.cpp 
	@echo "Done!\n"

colors.o: src/colors.cpp
	@echo "Compiling $@..."
	$(CC) -c src/colors.cpp ../lib/utils.cpp 
	@echo "Done!\n"

gutils.o: src/gutils.cpp
	@echo "Compiling $@..."
	$(CC) -c src/gutils.cpp ../lib/utils.cpp 
	@echo "Done!\n"

shadersUtils.o: src/shadersUtils.cpp
	@echo "Compiling $@..."
	$(CC) -c src/shadersUtils.cpp ../lib/utils.cpp 
	@echo "Done!\n"

window.o: src/window.cpp
	@echo "Compiling $@..."
	$(CC) -c src/window.cpp ../lib/utils.cpp 
	@echo "Done!\n"

renderScene.o: src/renderScene.cpp
	@echo "Compiling $@..."
	$(CC) -c src/renderScene.cpp ../lib/utils.cpp 
	@echo "Done!\n"

clean:
	rm -f glut-tutorial *.o 
