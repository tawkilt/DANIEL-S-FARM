#ifndef ACTION_H_INCLUDED
#define ACTION_H_INCLUDED

#include "constantes.h"
void planter(SDL_Renderer *, player_t * const , tile_t * const , listeP_t * );
void becher(SDL_Renderer * , player_t * const , tile_t * );
void faucher(player_t * const , listeP_t * );
void arroser(SDL_Renderer * , player_t * const , tile_t * , listeP_t * );
void recolter(SDL_Renderer * , player_t * , tile_t * , listeP_t * );
void action(SDL_Renderer *, player_t *, listeT_t *, listeP_t * );
#endif