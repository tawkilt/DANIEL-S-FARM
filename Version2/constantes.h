#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define STEP 5
#define PERSO 4
#define FRAMES 3
#define OUTIL 3
#define PLANTE 5

#define PERS_WIDTH 48
#define PERS_HEIGHT 48

#define ANIM 250
#define FPS 30

enum {DROITE = 0, GAUCHE, BAS, HAUT};
enum {NEW, SEMI, FULL, PLANT, DEAD};
enum {NOTHING, TOOL, SEED};
enum {GRASS, DIRT};
enum {OUTSIDE, HOME};

typedef enum tool_s {hoe, scythe, can} tool_t; //Tous les outils
typedef enum seed_s {cauliflower, melon, potato, pumpkin, tomato} seed_t; //Tous les types de graines/plantes

//Structure avec les données du personnage
typedef struct player_s{
    SDL_Rect position; //Position du personnage sur la carte
    SDL_Rect source; //Frame à sélectionner

    int inventaire[5];
    int money;
    int local;

    SDL_Surface *sPerso; //Sprites du personnage
    SDL_Texture *tPerso;

    int holding; //Vérifie si il tient quelque chose et qu'est-ce qu'il tient
    tool_t tool;
    seed_t seed;

    int cooldown; //Un cooldown d'action pour ne pas pouvoir en faire à répétition
    int last_action;

    int direction; //Direction dans laquelle le personnage regarde

    bool vel; //Vitesse du personnage

    int frame;
    int last_frame;
}player_t;

//Structure avec les données d'une plante
typedef struct plante_s{
    SDL_Rect position; //Position de la plante sur la carte

    SDL_Surface *sPlante[PLANTE]; //Sprites de la plante
    SDL_Texture *tPlante[PLANTE];

    seed_t type;
    int state; //État de la plante
    bool arrose; //État de l'arrosage
}plante_t;

//Structure avec les données d'une tile
typedef struct tile_s{
    SDL_Rect position; //Position de la tile sur la carte

    SDL_Surface *sTile; //Sprite de la tile
    SDL_Texture *tTile;

    int type; //Type de la tile (herbe ou terre)
    bool arrose; //État de l'arrosage
    int jours; //Jours passés depuis qu'elle est une tile de terre
}tile_t;

typedef struct listeP_s{
    int nb_elem;
    plante_t * plantes[50];
}listeP_t;

typedef struct listeT_s{
    int nb_elem;
    tile_t * tiles[50];
}listeT_t;

#endif