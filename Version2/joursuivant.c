#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constantes.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>



//Fonction qui va passer au jour suivant (et donc changer les états des plantes et des tiles)

void jour_suivant(SDL_Renderer * render, player_t * const player, listeP_t * plantes){
    int i;
    int elements = plantes->nb_elem;

    plante_t * temp = malloc(sizeof(plante_t));

    for(i = 0; i < elements; i++){
        temp = plantes->plantes[i];

        if(temp->state != DEAD){
            if(temp->state == FULL){
                temp->state = DEAD;
            }
            else{
                if(temp->arrose == true){
                    temp->state++;
                }
                else{
                    temp->state = DEAD;
                }
            }
        }

        temp->arrose = false;
    }
    temp = NULL;
}