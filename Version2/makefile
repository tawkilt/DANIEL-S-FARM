CCOBJ=gcc -c
CCLNK=gcc 
CFLAGS=-Wall -g

SDL_DIR=${HOME}/SDL2
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include

LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf
INCS=-I${SDL_INC_DIR}

all : main

main: action.o changeroutils.o deplacer.o jouer.o joursuivant.o text.o init.o verif.o main.o
	$(CCLNK) $(CFLAGS) -o main action.o changeroutils.o deplacer.o jouer.o joursuivant.o text.o init.o verif.o main.o ${LIBS} ${INCS}
main.o : main.c
	$(CCOBJ) $(CFLAGS) -o main.o main.c -I./ ${LIBS} ${INCS}

action.o : action.c action.h
		$(CCOBJ) $(CFLAGS)  action.c -o action.o -I./
changeroutils.o : changeroutils.c changeroutils.h
		$(CCOBJ) $(CFLAGS)  changeroutils.c -o changeroutils.o -I./
deplacer.o : deplacer.c deplacer.h
		$(CCOBJ) $(CFLAGS)  deplacer.c -o deplacer.o -I./
jouer.o : jouer.c jouer.h
		$(CCOBJ) $(CFLAGS) jouer.c -o jouer.o -I./
joursuivant.o : joursuivant.c joursuivant.h
		$(CCOBJ) $(CFLAGS)  joursuivant.c -o joursuivant.o -I./
text.o : text.c text.h
		$(CCOBJ) $(CFLAGS) text.c -o text.o -I./
init.o : init.c init.h
		$(CCOBJ) $(CFLAGS) init.c -o init.o -I./
verif.o : verif.c verif.h
		$(CCOBJ) $(CFLAGS) verif.c -o verif.o -I./


clean:
	rm -f *.o
	rm -f main
tests:
	./main