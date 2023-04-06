#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include "constantes.h"
/**
* \file init.h
* \author Henzo & Serda & Ania & Rabia
* \version 0.1
* \date 15 mars 2023
*/
/**
*\fn tile_t * init_tile(SDL_Renderer * , int , int )
*/
/**
*\fn void liste_tiles(SDL_Renderer * , listeT_t * )
*/
tile_t * init_tile(SDL_Renderer *, int , int);
void liste_tiles(SDL_Renderer *, listeT_t *);
#endif