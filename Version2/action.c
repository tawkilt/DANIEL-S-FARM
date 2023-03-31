#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constantes.h"
#include "verif.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>



//Fonction qui va initialiser une plante et qui va la placer sur la terre la plus proche

void planter(SDL_Renderer *render, player_t * const player, listeP_t * plantes, tile_t * tile){

    plante_t * plante = malloc(sizeof(plante_t));

    int i;

    for(i = 0; i < PLANTE; i++){
        plante->sPlante[i] = NULL;
        plante->tPlante[i] = NULL;
    }

    plante->state = NEW;

    //Ajout des sprites dans le tableau de surfaces de la plante, dépendant de quelle plante il s'agit
    switch(player->seed){
        case cauliflower:                
            plante->sPlante[NEW] = IMG_Load("sprites/seeds/cauliflower/l1cauliflower.png");                
            plante->sPlante[SEMI] = IMG_Load("sprites/seeds/cauliflower/l2cauliflower.png");                
            plante->sPlante[FULL] = IMG_Load("sprites/seeds/cauliflower/cauliflower.png");
            plante->sPlante[PLANT] = IMG_Load("sprites/seeds/cauliflower/cauliflower.png");
        break;
        case melon: 
            plante->sPlante[NEW] = IMG_Load("sprites/seeds/melon/l1melon.png");
            plante->sPlante[SEMI] = IMG_Load("sprites/seeds/melon/l2melon.png"); 
            plante->sPlante[FULL] = IMG_Load("sprites/seeds/melon/l3melon.png");
            plante->sPlante[PLANT] = IMG_Load("sprites/seeds/melon/melon.png");
        break;
        case potato: 
            plante->sPlante[NEW] = IMG_Load("sprites/seeds/potato/l1potato.png");
            plante->sPlante[SEMI] = IMG_Load("sprites/seeds/potato/l2potato.png");
            plante->sPlante[FULL] = IMG_Load("sprites/seeds/potato/l3potato.png");
            plante->sPlante[PLANT] = IMG_Load("sprites/seeds/potato/potato.png");
        break;
        case pumpkin: 
            plante->sPlante[NEW] = IMG_Load("sprites/seeds/pumpkin/l1pumpkin.png");
            plante->sPlante[SEMI] = IMG_Load("sprites/seeds/pumpkin/l2pumpkin.png");
            plante->sPlante[FULL] = IMG_Load("sprites/seeds/pumpkin/l3pumpkin.png");
            plante->sPlante[PLANT] = IMG_Load("sprites/seeds/pumpkin/pumpkin.png");
        break;
        case tomato: 
            plante->sPlante[NEW] = IMG_Load("sprites/seeds/tomato/l1tomato.png");
            plante->sPlante[SEMI] = IMG_Load("sprites/seeds/tomato/l2tomato.png");
            plante->sPlante[FULL] = IMG_Load("sprites/seeds/tomato/l3tomato.png");
            plante->sPlante[PLANT] = IMG_Load("sprites/seeds/tomato/tomato.png");
        break;
    }

    plante->sPlante[DEAD] = IMG_Load("sprites/seeds/dead.png");

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
}

//Fonction qui va transformer de l'herbe en terre (changement de la texture et du type)

void becher(SDL_Renderer * render, player_t * const player, tile_t * tile){

    if(tile->type == GRASS){
        tile->sTile = IMG_Load("dirt.png");

        //SDL_DestroyTexture(tile->tTile);

        tile->tTile = SDL_CreateTextureFromSurface(render, tile->sTile);

        SDL_FreeSurface(tile->sTile);

        tile->type = DIRT;
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
                temp->tPlante[i] = NULL;
            }
            temp = NULL;
            plantes->nb_elem--;
        }
    }
}

//Fonction qui va changer l'état de l'arrosage d'une tile (et d'une plante si elle se trouve sur cette tile)

void arroser(SDL_Renderer * render, player_t * const player, tile_t * tile, listeP_t * plantes){

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

//Fonction qui va ajouter une plante à l'inventaire si elle est au maximum

void recolter(SDL_Renderer * render, player_t * player, tile_t * tile, listeP_t * plantes){

    plante_t * temp = malloc(sizeof(plante_t));
    int i, j;
    int elements = plantes->nb_elem;

    for(i = 0; i < elements; i++){
        temp = plantes->plantes[i];
        if(tile->position.x == temp->position.x && tile->position.y == temp->position.y && temp->state == FULL){
            player->inventaire[temp->type]++;

            for(j = 0; j < PLANTE; j++){
                SDL_DestroyTexture(temp->tPlante[j]);
                temp->tPlante[i] = NULL;
            }
            temp = NULL;
            plantes->nb_elem--;
        }
    }
}

//Fonction qui va choisir l'action à faire

void action(SDL_Renderer * render, player_t * player, listeT_t * tiles, listeP_t * plantes){
    int i;

    if((i = verife_tile(player, tiles)) >= 0){
        switch(player->holding){
            case TOOL:
                switch(player->tool){
                    case hoe: if(tiles->tiles[i]->type == GRASS) becher(render, player, tiles->tiles[i]); break;
                    case scythe: faucher(player, plantes); break;
                    case can: arroser(render, player, tiles->tiles[i], plantes); break;
                    default: break;
                }; break;
            case SEED: if(tiles->tiles[i]->type == DIRT) planter(render, player, plantes, tiles->tiles[i]); break;
            case NOTHING : recolter(render, player, tiles->tiles[i], plantes); break;
            default: break;
        }
    }
}