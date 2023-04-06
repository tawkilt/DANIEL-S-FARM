#ifndef SHOP_H_INCLUDED
#define SHOP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constantes.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

bool shop(SDL_Rect const, player_t * const);

#endif