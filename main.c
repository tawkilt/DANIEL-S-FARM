#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constantes.h"
#include "jeu.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void deplacerPers(int carte[][26], SDL_Rect *pos, int direction, SDL_Renderer *render){
    switch(direction){
        case HAUT: pos->y--;break;
        case BAS: pos->y++;break;
        case GAUCHE: pos->x--;break;
        case DROITE: pos->x++;break;
        default: break;
    }
}

/*int jouer(SDL_Surface *ecran){
    SDL_Rect position, positionJoueur;
    SDL_Surface *sPerso[5] = {NULL};
    SDL_Texture *tPerso[5] = {NULL};
    SDL_Texture *persoActuel = NULL;

    int i;
    int j;

    sPerso[1] = IMG_LoadPNG_RW("cat.png", "rb");

    int carte[11][26];

    for(j = 1; j < 5; j++){
        if(sPerso[j] == NULL){
            printf("%d : Erreur SDL chargement de l'imiage Personnage \n", j);
            return -1;
        }
    }

    for(i = 1; i < 5; i++){
        tPerso[i] = SDL_CreateTextureFromSurface(render, sPerso[i]);
        SDL_FreeSurface(sPerso[i]);
        SDL_Log("Free de la surface du perso %d", i);
    }

    SDL_RenderClear(render);

    persoActuel = tPerso[BAS];
    if(persoActuel == NULL){
        SDL_Log("Erreur lors du chargement du personnage actuelle");
    }
    positionJoueur.x = 3;
    positionJoueur.y = 3;
    position.w = 100;
    position.h = 100;

    bool is_running = true;
    SDL_Event event;
    while(is_running){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT: is_running = false;break;

                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_UP: deplacerPers(carte, &positionJoueur, HAUT, render); break;
                        case SDLK_DOWN: deplacerPers(carte, &positionJoueur, BAS, render); break;
                        case SDLK_LEFT: deplacerPers(carte, &positionJoueur, GAUCHE, render); break;
                        case SDLK_RIGHT: deplacerPers(carte, &positionJoueur, DROITE, render); break;
                        default: break;
                    }
                default: break;
            }
        }
        position.x = positionJoueur.x * TAILLE_BLOCK;
        position.y = positionJoueur.y * TAILLE_BLOCK;

        SDL_BlitSurface(persoActuel, NULL, ecran)

        if(SDL_RenderCopy(render, persoActuel, NULL, &position) != 0){
            SDL_Log("Erreur lors de l'affichage à l'écran");
        }

        SDL_RenderPresent(render);
    }
    SDL_DestroyRenderer(render);
    SDL_Quit();
    return -1;
}*/

int main(){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window *win = NULL;
    win = SDL_CreateWindow("Le Mans Valley", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);

    if(win){
        jouer(win);
        SDL_Delay(3000);
        SDL_DestroyWindow(win);
    }

    SDL_Quit();
    return 0;
}