#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constantes.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

bool shop(SDL_Rect const shop, player_t * const player){
    if(player->local == OUTSIDE){
        return((player->position.x >= shop.x - 2 && player->position.x <= shop.x + 2) && (player->position.y >= shop.y + 2 && player->position.y <= shop.y + 4));
    }
    return false;
}