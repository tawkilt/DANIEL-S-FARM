#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constantes.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>



int afficheText(SDL_Renderer * render, SDL_Rect boite, char * message){
    SDL_Color blanc = {255, 255, 255};
    SDL_Surface * texte ;
    SDL_Texture * texte_tex ;
    TTF_Font * police = NULL;

    if ((police = TTF_OpenFont("sprites/font/font.ttf", 50)) == NULL){
        SDL_Log("Erreur lors du chargement de la police");
    }

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