CC = g++
LIBS = -lSDL2
#linux -lX11
#windows -lsdl2
all:
	@echo -n "Compiling... "
	@${CC} -o matrix main.cpp src/*.cpp ${LIBS}
	@cp src/*.bmp .
	@echo "done"