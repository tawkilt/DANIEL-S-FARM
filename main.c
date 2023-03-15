#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constantes.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//Fonction de déplacement du personnage

void deplacerPers(SDL_Rect *pos, int direction){
    switch(direction){
        case HAUT: pos->y--;break;
        case BAS: pos->y++;break;
        case GAUCHE: pos->x--;break;
        case DROITE: pos->x++;break;
        default: break;
    }
}

//Fonction qui va initialiser une plante et qui va la placer sur la terre la plus proche

plante_t * planter(SDL_Renderer *render, player_t * const player, SDL_Rect const tile){
    plante_t *plante = malloc(sizeof(plante_t));

    for(int i = 0; i < PLANTE; i++){
        plante->sPlante[i] = NULL;
        plante->tPlante[i] = NULL;
    }

    plante->state = NEW;

    SDL_RWops *rwop = SDL_RWFromFile("sprites/seeds/cauliflowers/cauliflower.png", "rb");
    plante->sPlante[plante->state] = IMG_LoadPNG_RW(rwop);

    plante->tPlante[plante->state] = SDL_CreateTextureFromSurface(render, plante->sPlante[plante->state]);

    /*plante->position = player->position;

    switch(player->direction){
        case HAUT: plante->position.y += 4; break;
        case BAS: plante->position.y += 10; break;
        case GAUCHE: plante->position.x -= 8; plante->position.y += 7; break;
        case DROITE: plante->position.x += 8; plante->position.y += 7; break;
        default: break;
    }*/

    plante->position = tile;

    return(plante);
}

void action(SDL_Renderer *render, player_t * const player){
    
}

//Fonction de jeu principal, avec une boucle qui vérifie que le jeu n'est pas fermé

int jouer(SDL_Renderer *render){
    player_t *player = malloc(sizeof(player_t));
    plante_t *plante = malloc(sizeof(plante_t));

    SDL_Rect position, backRect, dirt;
    SDL_Surface *sBackground = NULL;
    SDL_Surface *sTile = NULL;
    SDL_Texture *tBackground = NULL;
    SDL_Texture *tTile = NULL;
    SDL_Texture *persoActuel = NULL;

    int i;

    player->cooldown = 5000;

    for(i = 0; i < PERSO; i++){
        player->sPerso[i] = NULL;
        player->tPerso[i] = NULL;
    }

    //Initialisation des sprites

    SDL_RWops *rwop = SDL_RWFromFile("background.png", "rb");
    sBackground = IMG_LoadPNG_RW(rwop);

    rwop = SDL_RWFromFile("sprites/player/player.png", "rb");
    player->sPerso[0] = IMG_LoadPNG_RW(rwop);

    rwop = SDL_RWFromFile("dirt.png", "rb");
    sTile = IMG_LoadPNG_RW(rwop);

    /*for(j = 0; j < 5; j++){
        if(sPerso[j] == NULL){
            printf("%d : Erreur SDL chargement de l'image Personnage \n", j);
            return -1;
        }
    }*/

    //Creation de textures à partir des sprites

    for(i = 0; i < PERSO; i++){
        player->tPerso[i] = SDL_CreateTextureFromSurface(render, player->sPerso[i]);
        SDL_FreeSurface(player->sPerso[i]);
        SDL_Log("Free de la surface du perso %d", i);
    }
    tBackground = SDL_CreateTextureFromSurface(render, sBackground);
    SDL_FreeSurface(sBackground);

    tTile = SDL_CreateTextureFromSurface(render, sTile);
    SDL_FreeSurface(sTile);

    SDL_RenderClear(render);

    persoActuel = player->tPerso[0];
    if(persoActuel == NULL){
        SDL_Log("Erreur lors du chargement du personnage actuelle");
    }

    plante = NULL;

    player->direction = BAS;
    player->position.x = 0;
    player->position.y = 0;
    player->last_action = 0;

    position.w = 100;
    position.h = 100;

    backRect.w = 1920;
    backRect.h = 1080;

    dirt.x = 20;
    dirt.y = 20;

    SDL_Rect dif;

    //Boucle de jeu

    bool is_running = true;
    SDL_Event event;
    while(is_running){
        SDL_RenderClear(render);
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT: is_running = false;break;

                //Vérification des touches pressées
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        //Fermeture du jeu
                        case SDLK_ESCAPE: is_running = false; break;

                        //Déplacement du personnage
                        case SDLK_UP: deplacerPers(&player->position, HAUT); player->direction = HAUT; break;
                        case SDLK_DOWN: deplacerPers(&player->position, BAS); player->direction = BAS; break;
                        case SDLK_LEFT: deplacerPers(&player->position, GAUCHE); player->direction = GAUCHE; break;
                        case SDLK_RIGHT: deplacerPers(&player->position, DROITE); player->direction = DROITE; break;

                        //Action performée
                        case SDLK_e: if(SDL_GetTicks() - player->last_action > player->cooldown){
                            dif.x = player->position.x - dirt.x;
                            dif.y = player->position.y - dirt.y;
                            if((((dif.x >= -9 && dif.x <= -4) && (dif.y >= -6 && dif.y <= -3)) && player->direction == DROITE) ||
                                (((dif.x >= 4 && dif.x <= 10) && (dif.y >= -6 && dif.y <= -3)) && player->direction == GAUCHE) ||
                                (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -4 && dif.y <= 0)) && player->direction == HAUT) ||
                                (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -12 && dif.y <= -8)) && player->direction == BAS))
                                plante = planter(render, player, dirt);
                            player->last_action = SDL_GetTicks();
                        }; break;

                        default: break;
                    }
                default: break;
            }
        }

        //Affichage de tous les éléments sur la carte
        if(SDL_RenderCopy(render, tBackground, NULL, &backRect) != 0){
            SDL_Log("Erreur lors de l'affichage à l'écran");
        }

        position.x = dirt.x * STEP;
        position.y = dirt.y * STEP;

        if(SDL_RenderCopy(render, tTile, NULL, &position) != 0){
            SDL_Log("Erreur lors de l'affichage à l'écran");
        }

        if(plante != NULL){
            position.x = plante->position.x * STEP;
            position.y = plante->position.y * STEP;

            if(SDL_RenderCopy(render, plante->tPlante[plante->state], NULL, &position) != 0){
                SDL_Log("Erreur lors de l'affichage à l'écran");
            }
        }

        position.x = player->position.x * STEP;
        position.y = player->position.y * STEP;

        if(SDL_RenderCopy(render, persoActuel, NULL, &position) != 0){
            SDL_Log("Erreur lors de l'affichage à l'écran");
        }

        SDL_RenderPresent(render);
    }
    SDL_DestroyRenderer(render);
    SDL_Quit();
    free(player);
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