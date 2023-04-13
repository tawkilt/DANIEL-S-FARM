#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constantes.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/**
* \file joursuivant.c
* \brief Changement de jour
* \author Henzo & Serda & Ania & Rabia
* \version 0.1
* \date 15 mars 2023
*/

/**
*\fn void jour_suivant(SDL_Renderer * render, player_t * const player, listeP_t * plantes, listeT_t * tiles)
*\brief Fonction qui va passer au jour suivant (et donc changer les états des plantes et des tiles)
*/

void jour_suivant(SDL_Renderer * render, player_t * player, listeP_t * plantes, listeT_t * tiles){
    int i;
    int elementsP = plantes->nb_elem;
    int elementsT = tiles->nb_elem;

    Uint8 alpha = 0x00;

    SDL_Rect overlay;
    SDL_Surface * sOverlay = NULL;
    SDL_Texture * tOverlay = NULL;

    sOverlay = IMG_Load("sprites/map/overlay.png");

    tOverlay = SDL_CreateTextureFromSurface(render, sOverlay);
    SDL_FreeSurface(sOverlay);
    sOverlay = NULL;

    overlay.x = overlay.y = 0;

    SDL_SetTextureBlendMode(tOverlay, SDL_BLENDMODE_BLEND);

    plante_t * tempP = malloc(sizeof(plante_t));
    tile_t * tempT = malloc(sizeof(tile_t));

    for(i = 0; i < elementsP; i++){
        tempP = plantes->plantes[i];

        if(tempP->state != DEAD){
            if(tempP->state == FULL && !tempP->arrose){
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

    player->money += player->inventaireVente[cauliflower] * 10;
    player->money += player->inventaireVente[melon] * 10;
    player->money += player->inventaireVente[potato] * 5;
    player->money += player->inventaireVente[pumpkin] * 20;
    player->money += player->inventaireVente[tomato] * 15;

    for(i = 0; i < PLANTE; i++){
        player->inventaireVente[i] = 0;
    }

    /*for(alpha; alpha < 0xFF; alpha += 0x05){
        SDL_SetTextureAlphaMod(tOverlay, alpha);
        SDL_RenderCopy(render, tOverlay, NULL, &overlay);
        SDL_Delay(50);
        SDL_RenderPresent(render);
    }*/
    SDL_SetTextureAlphaMod(tOverlay, alpha);
    SDL_RenderCopy(render, tOverlay, NULL, &overlay);
    SDL_RenderPresent(render);
    SDL_Delay(100);

}