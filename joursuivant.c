#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constantes.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>



//Fonction qui va passer au jour suivant (et donc changer les états des plantes et des tiles)

void jour_suivant(SDL_Renderer * render, player_t * const player, listeP_t * plantes, listeT_t * tiles){
    int i;
    int elementsP = plantes->nb_elem;
    int elementsT = tiles->nb_elem;

    plante_t * tempP = malloc(sizeof(plante_t));
    tile_t * tempT = malloc(sizeof(tile_t));

    for(i = 0; i < elementsP; i++){
        tempP = plantes->plantes[i];

        if(tempP->state != DEAD){
            if(tempP->state == FULL){
                tempP->state = DEAD;
            }
            else{
                if(tempP->arrose == true){
                    tempP->state++;
                }
                else{
                    tempP->state = DEAD;
                }
            }
        }

        tempP->arrose = false;
        tempP = NULL;
    }

    for(i = 0; i < elementsT; i++){
        tempT = tiles->tiles[i];

        if(tempT->type == DIRT){
            tempT->jours++;

            if(tempT->arrose){
                tempT->arrose = false;

                tempT->sTile = IMG_Load("dirt.png");

                tempT->tTile = SDL_CreateTextureFromSurface(render, tempT->sTile);

                SDL_FreeSurface(tempT->sTile);
            }
            else if(tempT->jours >= 3){
                SDL_DestroyTexture(tempT->tTile);

                tempT->tTile = NULL;

                tempT->type = GRASS;

                tempT->jours = 0;
            }
        }

        tempT = NULL;
    }
    player->jours++;
}