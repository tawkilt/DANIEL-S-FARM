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