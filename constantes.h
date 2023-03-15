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
enum {NEW, SEMI, FULL};
enum {NOTHING, TOOL, SEEDS};

typedef enum tool_s {hoe, scythe, can} tool_t; //Tous les outils
typedef enum seeds_s {cauliflower, melon, potato, pumpkin, tomato} seeds_t; //Tous les types de graines/plantes

typedef struct player_s{
    SDL_Rect position; //Position du personnage sur la carte

    SDL_Surface *sPerso[PERSO]; //Sprites du personnage
    SDL_Texture *tPerso[PERSO];

    int holding; //Vérifie si il tient quelque chose et qu'est-ce qu'il tient

    int cooldown; //Un cooldown d'action pour ne pas pouvoir en faire à répétition
    int last_action;

    int direction; //Direction dans laquelle le personnage regarde
}player_t;

typedef struct plante_s{
    SDL_Rect position; //Position de la plante sur la carte

    SDL_Surface *sPlante[PLANTE]; //Sprites de la plante
    SDL_Texture *tPlante[PLANTE];

    int state; //État de la plante
}plante_t;

#endif