#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define STEP 5
#define PERSO 4
#define PLANTE 3

enum {BAS, GAUCHE, HAUT, DROITE};
enum {VIDE, MUR, DANIEL};
enum {NEW, SEMI, FULL};

typedef struct player_s{
    SDL_Rect position;
    SDL_Surface *sPerso[PERSO];
    SDL_Texture *tPerso[PERSO];
    int cooldown;
    int last_action;
    int direction;
}player_t;

typedef struct plante_s{
    SDL_Rect position;
    SDL_Surface *sPlante[PLANTE];
    SDL_Texture *tPlante[PLANTE];
    int state;
}plante_t;

#endif