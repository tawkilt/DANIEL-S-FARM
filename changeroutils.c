#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constantes.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


//Fonction qui va changer l'outil que l'on a dans les mains

void changer_outil(player_t *player, int const direction, tool_t * outil, seed_t * graine){
    switch(player->holding){
        case TOOL:
            switch(direction){
                case HAUT: if(player->tool == can){
                    player->tool = *outil = hoe;
                }
                else{
                    player->tool++;
                    *outil += 1;
                }; break;

                case BAS: if(player->tool == hoe){
                    player->tool = *outil = can;
                }
                else{
                    player->tool--;
                    *outil -= 1;
                }; break;

                default: break;
            }; break;

        case SEED:
            switch(direction){
                case HAUT: if(player->seed == tomato){
                    player->seed = *graine = cauliflower;
                }
                else{
                    player->seed++;
                    *graine += 1;
                }; break;

                case BAS: if(player->seed == cauliflower){
                    player->seed = *graine = tomato;
                }
                else{
                    player->seed--;
                    *graine -= 1;
                }; break;

                default: break;
            }; break;

        default: break;
    }
}
