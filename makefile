CC = g++
LIBS = -lSDL2
#windows -lsdl2
all:
	@echo -n "Compiling... "
	@${CC} -o matrix.exe main.cpp src/*.cpp ${LIBS}
	@echo "done"