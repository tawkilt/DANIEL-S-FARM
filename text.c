#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constantes.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/**
* \file text.c
* \brief Afficher les texts
* \author Henzo & Serda & Ania & Rabia
* \version 0.1
* \date 15 mars 2023
*/

/**
*\fn int afficheText(SDL_Renderer * render, SDL_Rect boite, char * message, TTF_Font * police)
*/

int afficheText(SDL_Renderer * render, SDL_Rect boite, char * message, TTF_Font * police){
    SDL_Color blanc = {255, 255, 255};
    SDL_Surface * texte ;
    SDL_Texture * texte_tex ;

    texte = TTF_RenderUTF8_Blended(police, message, blanc);

    if(!texte){
        return 1 ;
    }

    texte_tex = SDL_CreateTextureFromSurface(render, texte);

    if(!texte_tex){
        return 1 ;
    }

    SDL_QueryTexture(texte_tex, NULL, NULL, &(boite.w), &(boite.h));

    if(SDL_RenderCopy(render, texte_tex, NULL, &boite) != 0){
        SDL_Log("Erreur lors de l'affichage à l'écran");
    }

    SDL_DestroyTexture(texte_tex);
    SDL_FreeSurface(texte);
    return 0;
}