#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define STEP 5
#define PERSO 4
#define PLANTE 5

enum {BAS, GAUCHE, HAUT, DROITE};
enum {NEW, SEMI, FULL, PLANT, DEAD};
enum {NOTHING, TOOL, SEED};
enum {GRASS, DIRT};

typedef enum tool_s {hoe, scythe, can} tool_t; //Tous les outils
typedef enum seed_s {cauliflower, melon, potato, pumpkin, tomato} seed_t; //Tous les types de graines/plantes

//Structure avec les données du personnage
typedef struct player_s{
    SDL_Rect position; //Position du personnage sur la carte

    SDL_Surface *sPerso[PERSO]; //Sprites du personnage
    SDL_Texture *tPerso[PERSO];

    int holding; //Vérifie si il tient quelque chose et qu'est-ce qu'il tient
    tool_t tool;
    seed_t seed;

    int cooldown; //Un cooldown d'action pour ne pas pouvoir en faire à répétition
    int last_action;

    int direction; //Direction dans laquelle le personnage regarde
}player_t;

//Structure avec les données d'une plante
typedef struct plante_s{
    SDL_Rect position; //Position de la plante sur la carte

    SDL_Surface *sPlante[PLANTE]; //Sprites de la plante
    SDL_Texture *tPlante[PLANTE];

    int state; //État de la plante
    bool arrose;
}plante_t;

//Structure avec les données d'une tile
typedef struct tile_s{
    SDL_Rect position; //Position de la tile sur la carte

    SDL_Surface *sTile; //Sprite de la tile
    SDL_Texture *tTile;

    int type; //Type de la tile (herbe ou terre)
}tile_t;

typedef struct listeP_s{
    int nb_elem;
    plante_t ** plantes;
}listeP_t;

typedef struct listeT_s{
    int nb_elem;
    tile_t ** tiles;
}listeT_t;

#endif