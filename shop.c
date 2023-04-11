#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constantes.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
/**
* \file shop.c
* \brief Vérifie si le joueur est proche du magasin
* \author Henzo & Serda & Ania & Rabia
* \version 0.1
* \date 15 mars 2023
*/
/**
*\fn bool shop(SDL_Rect const shop, player_t * const player)
*/
bool shop(SDL_Rect const shop, player_t * const player){
    if(player->local == OUTSIDE){
        return((player->position.x >= shop.x - 2 && player->position.x <= shop.x + 2) && (player->position.y >= shop.y + 2 && player->position.y <= shop.y + 4));
    }
    return false;
}

bool chest(SDL_Rect const chest, player_t * const player){
    if(player->local == OUTSIDE){
        return((player->position.x >= chest.x - 6 && player->position.x <= chest.x + 6) && (player->position.y >= chest.y && player->position.y <= chest.y + 4));
    }
    return false;
}