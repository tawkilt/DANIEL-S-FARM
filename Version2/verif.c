#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constantes.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

int verife_tile(player_t * const player, listeT_t * const tiles){
    SDL_Rect dif;
    int i;

    for(i = 0; i < tiles->nb_elem; i++){
        dif.x = player->position.x - tiles->tiles[i]->position.x;
        dif.y = player->position.y - tiles->tiles[i]->position.y;
        if((((dif.x >= -9 && dif.x <= -4) && (dif.y >= -5 && dif.y <= -3)) && player->direction == DROITE) ||
            (((dif.x >= 4 && dif.x <= 10) && (dif.y >= -5 && dif.y <= -3)) && player->direction == GAUCHE) ||
            (((dif.x >= -2 && dif.x <= 3) && (dif.y >= -4 && dif.y <= 0)) && player->direction == HAUT) ||
            (((dif.x >= -2 && dif.x <= 3) && (dif.y >= -12 && dif.y <= -8)) && player->direction == BAS))
            return i;
    }
    return -1;
}