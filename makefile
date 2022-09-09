CC = g++
LIBS = -lSDL2
all:
	@echo -n "Compiling... "
	@${CC} -Wall -o matrix main.cpp src/*.cpp ${LIBS} -mwindows
	@cp src/*.bmp .
	@echo "done"