CC=gcc
FLAGS=-Wall -g

SDL_DIR=${HOME}/SDL2
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include

LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf
INCS=-I${SDL_INC_DIR}
PROG=main

all: main

main: main.o
	${CC} -o main main.o ${LIBS} ${INCS} ${FLAGS}

main.o: main.c
	${CC} -c main.c ${LIBS} ${INCS} ${FLAGS}

clean:
	rm -f ${PROG}
	rm -f *.o