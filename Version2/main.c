#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constantes.h"
#include "jouer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

int main(int argc,char *argv[]){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    if(TTF_Init() == -1) {
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

    SDL_Window *win = NULL;
    win = SDL_CreateWindow("Daniels' Farm", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

    if(win){
        //Création d'un render un des positions du personnage
        SDL_Renderer *render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
        jouer(render);
        SDL_DestroyRenderer(render);
    }
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}