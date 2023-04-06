#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constantes.h"
#include "jouer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

/**
* \file main.c
* \brief Main
* \author Henzo & Serda & Ania & Rabia
* \version 0.1
* \date 15 mars 2023
*/

/**
*\fn int main(int argc,char *argv[])
*/

int main(int argc,char *argv[]){
    
    // Initialisation de SDL
    SDL_Init(SDL_INIT_AUDIO);

    // Initialisation de SDL_mixer
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    // Chargement de la musique
    Mix_Music* music = Mix_LoadMUS("sounds/music.mp3");

    // Vérification que la musique a été chargée correctement
    if (!music) {
        printf("Erreur de chargement de la musique : %s\n", Mix_GetError());
        return 1;
    }

    // Lecture de la musique en boucle
    Mix_PlayMusic(music, -1);

    // Boucle principale du programme
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
    
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_DestroyWindow(win);
    SDL_Quit();

    // Libération de la musique et de SDL_mixer
    

    
    return 0;
}