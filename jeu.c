#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constantes.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void jouer(SDL_Surface *ecran){
    
    SDL_Event event;

    bool is_running = true;
    int i = 0, j = 0;

    while(is_running){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT: is_running = false; break;
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

        
    }
}