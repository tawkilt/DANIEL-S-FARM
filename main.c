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
        case HAUT: player->position.y--; break;
        case BAS: player->position.y++; break;
        case GAUCHE: player->position.x--; break;
        case DROITE: player->position.x++; break;
        default: break;
    }
}

//Fonction qui va changer l'outil que l'on a dans les mains

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
    SDL_Rect dif;

    dif.x = player->position.x - tile->position.x;
    dif.y = player->position.y - tile->position.y;
    if((((dif.x >= -9 && dif.x <= -4) && (dif.y >= -6 && dif.y <= -3)) && player->direction == DROITE) ||
        (((dif.x >= 4 && dif.x <= 10) && (dif.y >= -6 && dif.y <= -3)) && player->direction == GAUCHE) ||
        (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -4 && dif.y <= 0)) && player->direction == HAUT) ||
        (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -12 && dif.y <= -8)) && player->direction == BAS))
    {
        plante_t * plante = malloc(sizeof(plante_t));

        int i;

        SDL_RWops * rwop = NULL;

        for(i = 0; i < PLANTE; i++){
            plante->sPlante[i] = NULL;
            plante->tPlante[i] = NULL;
        }

        plante->state = NEW;

        //Ajout des sprites dans le tableau de surfaces de la plante, dépendant de quelle plante il s'agit
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

        //Création des textures et suppression des surfaces
        for(i = 0; i < PLANTE; i++){
            plante->tPlante[i] = SDL_CreateTextureFromSurface(render, plante->sPlante[i]);
            SDL_FreeSurface(plante->sPlante[i]);
            plante->sPlante[i] = NULL;
        }

        //Initialisation de la position de la plante sur la carte, de son type et ajout dans la liste des plantes
        plante->type = player->seed;
        plante->position = tile->position;

        plantes->plantes[plantes->nb_elem] = plante;
        plantes->nb_elem++;

        free(rwop);
    }
}

//Fonction qui va transformer de l'herbe en terre (changement de la texture et du type)

void becher(SDL_Renderer * render, player_t * const player, tile_t * tile){
    SDL_Rect dif;

    dif.x = player->position.x - tile->position.x;
    dif.y = player->position.y - tile->position.y;
    if((((dif.x >= -9 && dif.x <= -4) && (dif.y >= -6 && dif.y <= -3)) && player->direction == DROITE) ||
        (((dif.x >= 4 && dif.x <= 10) && (dif.y >= -6 && dif.y <= -3)) && player->direction == GAUCHE) ||
        (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -4 && dif.y <= 0)) && player->direction == HAUT) ||
        (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -12 && dif.y <= -8)) && player->direction == BAS))
    {
        SDL_RWops *rwop = SDL_RWFromFile("dirt.png", "rb");
        tile->sTile = IMG_LoadPNG_RW(rwop);

        tile->tTile = SDL_CreateTextureFromSurface(render, tile->sTile);

        SDL_FreeSurface(tile->sTile);

        tile->type = DIRT;

        free(rwop);
    }
}

//Fonction qui va supprimer une ou plusieurs plante(s) de la liste de plantes (et donc de la carte)

void faucher(player_t * const player, listeP_t * plantes){
    plante_t * temp = malloc(sizeof(plante_t));
    SDL_Rect dif;
    int i, j;
    int elements = plantes->nb_elem;

    //Vérification pour savoir si il y a plusieurs plantes que l'on peut enlever en même temps

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
            temp = NULL;
            plantes->nb_elem--;
        }
    }
}

//Fonction qui va passer au jour suivant (et donc changer les états des plantes et des tiles)

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
    temp = NULL;
}

//Fonction qui va changer l'état de l'arrosage d'une tile (et d'une plante si elle se trouve sur cette tile)

void arroser(SDL_Renderer * render, player_t * const player, tile_t * tile, listeP_t * plantes){
    SDL_Rect dif;

    dif.x = player->position.x - tile->position.x;
    dif.y = player->position.y - tile->position.y;
    if((((dif.x >= -9 && dif.x <= -4) && (dif.y >= -6 && dif.y <= -3)) && player->direction == DROITE) ||
        (((dif.x >= 4 && dif.x <= 10) && (dif.y >= -6 && dif.y <= -3)) && player->direction == GAUCHE) ||
        (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -4 && dif.y <= 0)) && player->direction == HAUT) ||
        (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -12 && dif.y <= -8)) && player->direction == BAS))
    {
        if(tile->type == DIRT){
            int i;
            tile->arrose = true;

            for(i = 0; i < plantes->nb_elem; i++){
                if(tile->position.x == plantes->plantes[i]->position.x && tile->position.y == plantes->plantes[i]->position.y){
                    plantes->plantes[i]->arrose = true;
                    break;
                }
            }
        }
    }
}

//Fonction qui va ajouter une plante à l'inventaire si elle est au maximum

void recolter(SDL_Renderer * render, player_t * player, tile_t * tile, listeP_t * plantes){
    SDL_Rect dif;

    dif.x = player->position.x - tile->position.x;
    dif.y = player->position.y - tile->position.y;
    if((((dif.x >= -9 && dif.x <= -4) && (dif.y >= -6 && dif.y <= -3)) && player->direction == DROITE) ||
        (((dif.x >= 4 && dif.x <= 10) && (dif.y >= -6 && dif.y <= -3)) && player->direction == GAUCHE) ||
        (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -4 && dif.y <= 0)) && player->direction == HAUT) ||
        (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -12 && dif.y <= -8)) && player->direction == BAS))
    {
        plante_t * temp = malloc(sizeof(plante_t));
        int i, j;
        int elements = plantes->nb_elem;

        for(i = 0; i < elements; i++){
            temp = plantes->plantes[i];
            if(tile->position.x == temp->position.x && tile->position.y == temp->position.y && temp->state == FULL){
                player->inventaire[temp->type]++;

                for(j = 0; j < PLANTE; j++){
                    SDL_DestroyTexture(temp->tPlante[j]);
                }
                temp = NULL;
                plantes->nb_elem--;
            }
        }
    }
}

//Fonction qui va choisir l'action à faire

void action(SDL_Renderer * render, player_t * player, tile_t * tile, listeP_t * plantes){
    switch(player->holding){
        case TOOL:
            switch(player->tool){
                case hoe: if(tile->type == GRASS) becher(render, player, tile); break;
                case scythe: faucher(player, plantes); break;
                case can: arroser(render, player, tile, plantes); break;
                default: break;
            }; break;
        case SEED: if(tile->type == DIRT) planter(render, player, tile, plantes); break;
        case NOTHING : recolter(render, player, tile, plantes); break;
        default: break;
    }
}

//Fonction de jeu principal, avec une boucle qui vérifie que le jeu n'est pas fermé

void jouer(SDL_Renderer *render){
    player_t *player = malloc(sizeof(player_t));
    tile_t *tile = malloc(sizeof(tile_t));
    plante_t * tempPlante = malloc(sizeof(plante_t));

    listeP_t * plantes = malloc(sizeof(listeP_t));
    listeT_t * tiles = malloc(sizeof(listeT_t));

    SDL_Rect position, backRect, dirt, contour;
    SDL_Surface *sBackground = NULL;
    SDL_Texture *tBackground = NULL;
    SDL_Texture *persoActuel = NULL;

    SDL_Surface * sFrames[3];
    SDL_Texture * tFrames[3];
    SDL_Surface * sContour = NULL;
    SDL_Texture * tContour = NULL;

    SDL_Rect frames[3];

    int i, j;

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

    rwop = SDL_RWFromFile("sprites/frames/frame.png", "rb");
    for(i = 0; i < 3; i++){
        sFrames[i] = IMG_LoadPNG_RW(rwop);
    }

    rwop = SDL_RWFromFile("sprites/frames/frame2.png", "rb");
    sContour = IMG_LoadPNG_RW(rwop);

    rwop = NULL;

    /*for(j = 0; j < 5; j++){
        if(sPerso[j] == NULL){
            printf("%d : Erreur SDL chargement de l'image Personnage \n", j);
            return -1;
        }
    }*/

    //Creation de textures à partir des sprites

    for(i = 0; i < 3; i++){
        tFrames[i] = SDL_CreateTextureFromSurface(render, sFrames[i]);
        SDL_FreeSurface(sFrames[i]);
        sFrames[i] = NULL;
    }

    tContour = SDL_CreateTextureFromSurface(render, sContour);
    SDL_FreeSurface(sContour);
    sContour = NULL;

    for(i = 0; i < PERSO; i++){
        player->tPerso[i] = SDL_CreateTextureFromSurface(render, player->sPerso[i]);
        SDL_FreeSurface(player->sPerso[i]);
        player->sPerso[i] = NULL;
    }

    tBackground = SDL_CreateTextureFromSurface(render, sBackground);
    SDL_FreeSurface(sBackground);
    sBackground = NULL;

    tile->tTile = SDL_CreateTextureFromSurface(render, tile->sTile);
    SDL_FreeSurface(tile->sTile);
    tile->sTile = NULL;

    SDL_RenderClear(render);

    persoActuel = player->tPerso[0];
    if(persoActuel == NULL){
        SDL_Log("Erreur lors du chargement du personnage actuelle");
    }

    player->direction = BAS;
    
    player->position.x = 0;
    player->position.y = 0;

    for(i = 0; i < 5; i++){
        player->inventaire[i] = 0;
    }

    player->cooldown = 2500;
    player->holding = NOTHING;
    player->tool = hoe;
    player->seed = cauliflower;

    player->last_action = 0;

    tile->position.x = 20;
    tile->position.y = 20;

    tile->arrose = false;
    tile->type = GRASS;

    position.w = 100;
    position.h = 100;

    backRect.w = 1920;
    backRect.h = 1080;

    frames[0].x = 600;
    frames[0].y = 600;
    frames[0].h = 100;
    frames[0].w = 100;

    plantes->nb_elem = 0;
    tiles->nb_elem = 0;

    plantes->plantes = malloc(sizeof(plante_t *));

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

        if(SDL_RenderCopy(render, tFrames[0], NULL, &frames[0]) != 0){
            SDL_Log("Erreur lors de l'affichage à l'écran");
        }

        /*printf("[%d | %d | %d] ", player->holding, player->tool, player->seed);
        printf("Inventaire : [ ");
        for(i = 0; i < 5; i++){
            printf("%d ", player->inventaire[i]);
            if(i != 4){
                printf("| ");
            }
        }
        printf("]\n");*/

        SDL_RenderPresent(render);
    }

    for(i = 0; i < PERSO; i++){
        SDL_DestroyTexture(player->tPerso[i]);
        player->tPerso[i] = NULL;
    }
    free(player);
    player = NULL;

    SDL_DestroyTexture(tile->tTile);
    tile->tTile = NULL;
    free(tile);
    tile = NULL;

    for(i = 0; i < plantes->nb_elem; i++){
        tempPlante = plantes->plantes[i];
        for(j = 0; j < PLANTE; j++){
            SDL_DestroyTexture(tempPlante->tPlante[j]);
            tempPlante->tPlante[i] = NULL;
        }
        free(tempPlante);
    }

    free(plantes->plantes);
    free(plantes);
    plantes = NULL;

    free(tiles);
    tiles = NULL;

    tempPlante = NULL;

    SDL_DestroyTexture(tBackground);

    for(i = 0; i < 3; i++){
        SDL_DestroyTexture(tFrames[i]);
        tFrames[i] = NULL;
    }

    SDL_DestroyTexture(tContour);
    tContour = NULL;
}

int main(){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window *win = NULL;
    win = SDL_CreateWindow("Daniels' Valley", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

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