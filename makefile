CC=gcc
FLAGS=-Wall -g
SDL_DIR=${HOME}/projet/local/c
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include
LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf
INCS=-I${SDL_INC_DIR}
PROG=test3
all: test3
test3: test3.c
	${CC} -o ${PROG} test3.c ${LIBS} ${INCS} ${FLAGS}
clean:
	rm -f ${PROG}
	rm -f *.o