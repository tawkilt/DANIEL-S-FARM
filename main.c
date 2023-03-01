#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constantes.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void deplacerPers(int carte[][480], SDL_Rect *pos, int direction, SDL_Renderer *render){
    switch(direction){
        case HAUT: pos->y--;break;
        case BAS: pos->y++;break;
        case GAUCHE: pos->x--;break;
        case DROITE: pos->x++;break;
        default: break;
    }
}

int jouer(SDL_Renderer *render){
    SDL_Rect position, positionJoueur, backRect;
    SDL_Surface *sPerso[5] = {NULL};
    SDL_Surface *sBackground = NULL;
    SDL_Texture *tPerso[5] = {NULL};
    SDL_Texture *tBackground = NULL;
    SDL_Texture *persoActuel = NULL;

    int i;
    int j;

    SDL_RWops *rwop = SDL_RWFromFile("background.png", "rb");
    sBackground = IMG_LoadPNG_RW(rwop);

    rwop = SDL_RWFromFile("player.png", "rb");
    sPerso[0] = IMG_LoadPNG_RW(rwop);

    int carte[640][480];
    int shop[640][480];
    int mine[640][480];

    /*for(j = 0; j < 5; j++){
        if(sPerso[j] == NULL){
            printf("%d : Erreur SDL chargement de l'image Personnage \n", j);
            return -1;
        }
    }*/

    for(i = 0; i < 5; i++){
        tPerso[i] = SDL_CreateTextureFromSurface(render, sPerso[i]);
        SDL_FreeSurface(sPerso[i]);
        SDL_Log("Free de la surface du perso %d", i);
    }
    tBackground = SDL_CreateTextureFromSurface(render, sBackground);
    SDL_FreeSurface(sBackground);

    SDL_RenderClear(render);

    persoActuel = tPerso[0];
    if(persoActuel == NULL){
        SDL_Log("Erreur lors du chargement du personnage actuelle");
    }
    positionJoueur.x = 3;
    positionJoueur.y = 3;
    position.w = 100;
    position.h = 100;

    backRect.w = 1280;
    backRect.h = 980;

    bool is_running = true;
    SDL_Event event;
    while(is_running){
        SDL_RenderClear(render);
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT: is_running = false;break;

                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE: is_running = false; break;
                        case SDLK_UP: deplacerPers(carte, &positionJoueur, HAUT, render); break;
                        case SDLK_DOWN: deplacerPers(carte, &positionJoueur, BAS, render); break;
                        case SDLK_LEFT: deplacerPers(carte, &positionJoueur, GAUCHE, render); break;
                        case SDLK_RIGHT: deplacerPers(carte, &positionJoueur, DROITE, render); break;
                        default: break;
                    }
                default: break;
            }
        }
        if(positionJoueur.x > 640){
            positionJoueur.x = 3;
            position.x = positionJoueur.x * TAILLE_BLOCK;
        }
        position.x = positionJoueur.x * TAILLE_BLOCK;
        position.y = positionJoueur.y * TAILLE_BLOCK;

        if(SDL_RenderCopy(render, tBackground, NULL, &backRect) != 0){
            SDL_Log("Erreur lors de l'affichage à l'écran");
        }

        if(SDL_RenderCopy(render, persoActuel, NULL, &position) != 0){
            SDL_Log("Erreur lors de l'affichage à l'écran");
        }

        SDL_RenderPresent(render);
    }
    SDL_DestroyRenderer(render);
    SDL_Quit();
    return -1;
}

int main(){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window *win = NULL;
    win = SDL_CreateWindow("Daniels' Valley", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);

    if(win){
        //Création d'un render un des positions du personnage
        SDL_Renderer *render = SDL_CreateRenderer(win, -1, 0);
        jouer(render);
    }
    return 0;
}