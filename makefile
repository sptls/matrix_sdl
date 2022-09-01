CC = g++
LIBS = -lSDL2

all:
	@echo -n "Compiling... "
	@${CC} -o matrix main.cpp src/*.cpp ${LIBS}
	@echo "done"