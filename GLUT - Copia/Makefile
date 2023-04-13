CC = g++
CFLAGS = -Wall

GLLIBS = -lglut -lGLEW -lGL -lGLU 

FILES = ../lib/utils.cpp glut-tutorial.cpp gutils.cpp colors.cpp window.cpp inputHandlers.cpp shadersUtils.cpp

OBJFILES = glut-tutorial.o colors.o inputHandlers.o 

TARGET = glut-tutorial

glut-tutorial : $(OBJFILES)
	echo "glut-tutorial"
	$(CC) -o main $(OBJFILES)

glut-tutorial.o: glut-tutorial.cpp window.h colors.h inputHandlers.h shadersUtils.h gutils.h
	echo "glut-tutorial.o"
	$(CC) -c glut-tutorial.cpp ../lib/utils.cpp $(GLLIBS)

colors.o: colors.cpp
	echo "colors.o"
	$(CC) -c colors.cpp $(GLLIBS)

inputHandlers.o: inputHandlers.cpp
	echo "inputHandlers.o"
	$(CC) -c inputHandlers.cpp $(GLLIBS)

	

clean:
	rm -f main *.o 
