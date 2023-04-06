#ifndef VERIF_H_INCLUDED
#define VERIF_H_INCLUDED
/**
* \file verif.h
* \author Henzo & Serda & Ania & Rabia
* \version 0.1
* \date 15 mars 2023
*/
/**
*\fn bool verife_position(SDL_Rect const, SDL_Rect const);
*/
/**
*\fn int verife_tile(player_t * const, listeT_t * const);
*/
/**
*\fn bool verife_porte(SDL_Rect const, player_t * const);
*/
/**
*\fn bool verife_bed(player_t * const);
*/
bool verife_position(SDL_Rect const, SDL_Rect const);
int verife_tile(player_t * const, listeT_t * const);
bool verife_porte(SDL_Rect const, player_t * const);
bool verife_bed(player_t * const);
#endif