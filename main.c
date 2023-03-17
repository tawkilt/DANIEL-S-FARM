#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constantes.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//Fonction de déplacement du personnage

void deplacerPers(player_t * player){
    switch(player->direction){
        case HAUT: player->position.y--;break;
        case BAS: player->position.y++;break;
        case GAUCHE: player->position.x--;break;
        case DROITE: player->position.x++;break;
        default: break;
    }
}

void changer_outil(player_t *player, int const direction){
    switch(player->holding){
        case TOOL:
            switch(direction){
                case HAUT: if(player->tool == can){
                    player->tool = hoe;
                }
                else{
                    player->tool++;
                }; break;

                case BAS: if(player->tool == hoe){
                    player->tool = can;
                }
                else{
                    player->tool--;
                }; break;

                default: break;
            }; break;

        case SEED:
            switch(direction){
                case HAUT: if(player->seed == tomato){
                    player->seed = cauliflower;
                }
                else{
                    player->seed++;
                }; break;

                case BAS: if(player->seed == cauliflower){
                    player->seed = tomato;
                }
                else{
                    player->seed--;
                }; break;

                default: break;
            }; break;

        default: break;
    }
}

//Fonction qui va initialiser une plante et qui va la placer sur la terre la plus proche

void planter(SDL_Renderer *render, player_t * const player, tile_t * const tile, listeP_t * plantes){
    plante_t *plante = malloc(sizeof(plante_t));

    int i;

    SDL_RWops * rwop = NULL;

    for(i = 0; i < PLANTE; i++){
        plante->sPlante[i] = NULL;
        plante->tPlante[i] = NULL;
    }

    plante->state = NEW;

    switch(player->seed){
        case cauliflower: 
            rwop = SDL_RWFromFile("sprites/seeds/cauliflower/l1cauliflower.png", "rb");
            plante->sPlante[NEW] = IMG_LoadPNG_RW(rwop);
            rwop = SDL_RWFromFile("sprites/seeds/cauliflower/l2cauliflower.png", "rb");
            plante->sPlante[SEMI] = IMG_LoadPNG_RW(rwop);
            rwop = SDL_RWFromFile("sprites/seeds/cauliflower/cauliflower.png", "rb");
            plante->sPlante[FULL] = IMG_LoadPNG_RW(rwop);
            rwop = SDL_RWFromFile("sprites/seeds/cauliflower/cauliflower.png", "rb");
            plante->sPlante[PLANT] = IMG_LoadPNG_RW(rwop);
        break;
        case melon: 
            rwop = SDL_RWFromFile("sprites/seeds/melon/l1melon.png", "rb");
            plante->sPlante[NEW] = IMG_LoadPNG_RW(rwop);
            rwop = SDL_RWFromFile("sprites/seeds/melon/l2melon.png", "rb");
            plante->sPlante[SEMI] = IMG_LoadPNG_RW(rwop);
            rwop = SDL_RWFromFile("sprites/seeds/melon/l3melon.png", "rb");
            plante->sPlante[FULL] = IMG_LoadPNG_RW(rwop);
            rwop = SDL_RWFromFile("sprites/seeds/melon/melon.png", "rb");
            plante->sPlante[PLANT] = IMG_LoadPNG_RW(rwop);
        break;
        case potato: 
            rwop = SDL_RWFromFile("sprites/seeds/potato/l1potato.png", "rb");
            plante->sPlante[NEW] = IMG_LoadPNG_RW(rwop);
            rwop = SDL_RWFromFile("sprites/seeds/potato/l2potato.png", "rb");
            plante->sPlante[SEMI] = IMG_LoadPNG_RW(rwop);
            rwop = SDL_RWFromFile("sprites/seeds/potato/l3potato.png", "rb");
            plante->sPlante[FULL] = IMG_LoadPNG_RW(rwop);
            rwop = SDL_RWFromFile("sprites/seeds/potato/potato.png", "rb");
            plante->sPlante[PLANT] = IMG_LoadPNG_RW(rwop);
        break;
        case pumpkin: 
            rwop = SDL_RWFromFile("sprites/seeds/pumpkin/l1pumpkin.png", "rb");
            plante->sPlante[NEW] = IMG_LoadPNG_RW(rwop);
            rwop = SDL_RWFromFile("sprites/seeds/pumpkin/l2pumpkin.png", "rb");
            plante->sPlante[SEMI] = IMG_LoadPNG_RW(rwop);
            rwop = SDL_RWFromFile("sprites/seeds/pumpkin/l3pumpkin.png", "rb");
            plante->sPlante[FULL] = IMG_LoadPNG_RW(rwop);
            rwop = SDL_RWFromFile("sprites/seeds/pumpkin/pumpkin.png", "rb");
            plante->sPlante[PLANT] = IMG_LoadPNG_RW(rwop);
        break;
        case tomato: 
            rwop = SDL_RWFromFile("sprites/seeds/tomato/l1tomato.png", "rb");
            plante->sPlante[NEW] = IMG_LoadPNG_RW(rwop);
            rwop = SDL_RWFromFile("sprites/seeds/tomato/l2tomato.png", "rb");
            plante->sPlante[SEMI] = IMG_LoadPNG_RW(rwop);
            rwop = SDL_RWFromFile("sprites/seeds/tomato/l3tomato.png", "rb");
            plante->sPlante[FULL] = IMG_LoadPNG_RW(rwop);
            rwop = SDL_RWFromFile("sprites/seeds/tomato/tomato.png", "rb");
            plante->sPlante[PLANT] = IMG_LoadPNG_RW(rwop);
        break;
    }

    rwop = SDL_RWFromFile("sprites/seeds/dead.png", "rb");
    plante->sPlante[DEAD] = IMG_LoadPNG_RW(rwop);

    for(i = 0; i < PLANTE; i++){
        plante->tPlante[i] = SDL_CreateTextureFromSurface(render, plante->sPlante[i]);
        SDL_FreeSurface(plante->sPlante[i]);
    }

    plante->position = tile->position;

    plantes->plantes[plantes->nb_elem] = plante;
    plantes->nb_elem++;
}

void becher(SDL_Renderer * render, player_t * const player, tile_t * tile){
    SDL_RWops *rwop = SDL_RWFromFile("dirt.png", "rb");
    tile->sTile = IMG_LoadPNG_RW(rwop);

    tile->tTile = SDL_CreateTextureFromSurface(render, tile->sTile);

    SDL_FreeSurface(tile->sTile);

    tile->type = DIRT;
}

void recolter(player_t * const player, listeP_t * plantes){
    plante_t * temp = malloc(sizeof(plante_t));
    SDL_Rect dif;
    int i, j;
    int elements = plantes->nb_elem;

    for(i = 0; i < elements; i++){
        temp = plantes->plantes[i];

        dif.x = player->position.x - temp->position.x;
        dif.y = player->position.y - temp->position.y;
        if((((dif.x >= -9 && dif.x <= -4) && (dif.y >= -6 && dif.y <= -3)) && player->direction == DROITE) ||
            (((dif.x >= 4 && dif.x <= 10) && (dif.y >= -6 && dif.y <= -3)) && player->direction == GAUCHE) ||
            (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -4 && dif.y <= 0)) && player->direction == HAUT) ||
            (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -12 && dif.y <= -8)) && player->direction == BAS))
        {
            for(j = 0; j < PLANTE; j++){
                SDL_DestroyTexture(temp->tPlante[i]);
            }
            free(temp);
            temp = NULL;
            plantes->nb_elem--;
        }
    }
}

void jour_suivant(SDL_Renderer * render, player_t * const player, listeP_t * plantes){
    int i;
    int elements = plantes->nb_elem;

    plante_t * temp = malloc(sizeof(plante_t));

    for(i = 0; i < elements; i++){
        temp = plantes->plantes[i];

        if(temp->state != DEAD){
            if(temp->state == FULL){
                temp->state = DEAD;
            }
            else{
                temp->state++;
            }
        }
    }
}

void arroser(SDL_Renderer * render, player_t * const player, plante_t * plante){
    
}

void action(SDL_Renderer * render, player_t * const player, tile_t * tile, listeP_t * plantes){
    switch(player->holding){
        case TOOL:
            switch(player->tool){
                case hoe: if(tile->type == GRASS) becher(render, player, tile); break;
                case scythe: recolter(player, plantes); break;
                default: break;
            }; break;
        case SEED: if(tile->type == DIRT) planter(render, player, tile, plantes); break;
        default: break;
    }
}

//Fonction de jeu principal, avec une boucle qui vérifie que le jeu n'est pas fermé

int jouer(SDL_Renderer *render){
    player_t *player = malloc(sizeof(player_t));
    tile_t *tile = malloc(sizeof(tile_t));
    plante_t * tempPlante = malloc(sizeof(plante_t));

    listeP_t * plantes = malloc(sizeof(listeP_t));
    listeT_t * tiles = malloc(sizeof(listeT_t));

    SDL_Rect position, backRect, dirt;
    SDL_Surface *sBackground = NULL;
    SDL_Texture *tBackground = NULL;
    SDL_Texture *persoActuel = NULL;

    int i;

    for(i = 0; i < PERSO; i++){
        player->sPerso[i] = NULL;
        player->tPerso[i] = NULL;
    }

    //Initialisation des sprites

    SDL_RWops *rwop = SDL_RWFromFile("background.png", "rb");
    sBackground = IMG_LoadPNG_RW(rwop);

    rwop = SDL_RWFromFile("sprites/player/player.png", "rb");
    player->sPerso[0] = IMG_LoadPNG_RW(rwop);

    rwop = SDL_RWFromFile("grass.png", "rb");
    tile->sTile = IMG_LoadPNG_RW(rwop);

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

    tile->tTile = SDL_CreateTextureFromSurface(render, tile->sTile);
    SDL_FreeSurface(tile->sTile);

    SDL_RenderClear(render);

    persoActuel = player->tPerso[0];
    if(persoActuel == NULL){
        SDL_Log("Erreur lors du chargement du personnage actuelle");
    }

    player->direction = BAS;
    
    player->position.x = 0;
    player->position.y = 0;

    player->cooldown = 2500;
    player->holding = NOTHING;
    player->tool = hoe;
    player->seed = cauliflower;

    player->last_action = 0;

    tile->position.x = 20;
    tile->position.y = 20;

    tile->type = GRASS;

    position.w = 100;
    position.h = 100;

    backRect.w = 1920;
    backRect.h = 1080;

    plantes->nb_elem = 0;
    tiles->nb_elem = 0;

    plantes->plantes = malloc(sizeof(plante_t*));

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
                        case SDLK_z: player->direction = HAUT; deplacerPers(player); break;
                        case SDLK_s: player->direction = BAS; deplacerPers(player); break;
                        case SDLK_q: player->direction = GAUCHE; deplacerPers(player); break;
                        case SDLK_d: player->direction = DROITE; deplacerPers(player); break;

                        //Action performée
                        case SDLK_e: if(SDL_GetTicks() - player->last_action > player->cooldown){
                            dif.x = player->position.x - tile->position.x;
                            dif.y = player->position.y - tile->position.y;
                            if((((dif.x >= -9 && dif.x <= -4) && (dif.y >= -6 && dif.y <= -3)) && player->direction == DROITE) ||
                                (((dif.x >= 4 && dif.x <= 10) && (dif.y >= -6 && dif.y <= -3)) && player->direction == GAUCHE) ||
                                (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -4 && dif.y <= 0)) && player->direction == HAUT) ||
                                (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -12 && dif.y <= -8)) && player->direction == BAS))
                                action(render, player, tile, plantes);
                            player->last_action = SDL_GetTicks();
                        }; break;

                        case SDLK_a: jour_suivant(render, player, plantes); break;

                        case SDLK_RIGHT: if(player->holding == SEED){
                            player->holding = NOTHING;
                        }
                        else{
                            player->holding++;
                        }; break;

                        case SDLK_LEFT: if(player->holding == NOTHING){
                            player->holding = SEED;
                        }
                        else{
                            player->holding--;
                        }; break;
                        
                        case SDLK_UP: changer_outil(player, HAUT); break;

                        case SDLK_DOWN: changer_outil(player, BAS); break;

                        default: break;
                    }
                default: break;
            }
        }

        //Affichage de tous les éléments sur la carte
        if(SDL_RenderCopy(render, tBackground, NULL, &backRect) != 0){
            SDL_Log("Erreur lors de l'affichage à l'écran");
        }

        position.x = tile->position.x * STEP;
        position.y = tile->position.y * STEP;

        if(SDL_RenderCopy(render, tile->tTile, NULL, &position) != 0){
            SDL_Log("Erreur lors de l'affichage à l'écran");
        }

        if(plantes->nb_elem > 0){
            for(i = 0; i < plantes->nb_elem; i++){
                tempPlante = plantes->plantes[i];

                position.x = tempPlante->position.x * STEP;
                position.y = tempPlante->position.y * STEP;

                if(SDL_RenderCopy(render, tempPlante->tPlante[tempPlante->state], NULL, &position) != 0){
                    SDL_Log("Erreur lors de l'affichage à l'écran");
                }
            }
        }

        position.x = player->position.x * STEP;
        position.y = player->position.y * STEP;

        if(SDL_RenderCopy(render, persoActuel, NULL, &position) != 0){
            SDL_Log("Erreur lors de l'affichage à l'écran");
        }

        printf("[%d | %d | %d] Type = %d\n", player->holding, player->tool, player->seed, tile->type);

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