CC = g++
LIBS = -lSDL2
#windows -lsdl2
all:
	@echo -n "Compiling... "
	@${CC} -o matrix main.cpp src/*.cpp ${LIBS}
	@cp src/*.bmp .
	@echo "done"