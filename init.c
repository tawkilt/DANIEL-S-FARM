#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constantes.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/**
* \file init.c
* \brief Initialiser les tiles du carte
* \author Henzo & Serda & Ania & Rabia
* \version 0.1
* \date 15 mars 2023
*/
/**
*\fn tile_t * init_tile(SDL_Renderer * render, int x, int y)
*/

tile_t * init_tile(SDL_Renderer * render, int x, int y){
    tile_t * tile = malloc(sizeof(tile_t));

    tile->position.x = x;
    tile->position.y = y;

    /*tile->sTile = IMG_Load("grass.png");

    tile->tTile = SDL_CreateTextureFromSurface(render, tile->sTile);
    SDL_FreeSurface(tile->sTile);
    tile->sTile = NULL;*/
    tile->tTile = NULL;

    tile->type = GRASS;
    tile->arrose = false;
    tile->jours = 0;

    return(tile);
}

/**
*\fn void liste_tiles(SDL_Renderer * render, listeT_t * tiles)
*/
void liste_tiles(SDL_Renderer * render, listeT_t * tiles){
    int i, j;
    //tile_t * temp = malloc(sizeof(tile_t));
    for(i = 41; i < 111; i += 7){
        for(j = 38; j < 73; j += 7){
            tiles->tiles[tiles->nb_elem] = init_tile(render, i, j);
            tiles->nb_elem++;
            //temp = NULL;
        }
    }
}
