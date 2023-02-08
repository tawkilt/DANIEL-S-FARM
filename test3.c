#include<stdlib.h>
#include<stdio.h>
#include<SDL2/SDL.h>
void pause(){
// cette fonction permet de mettre en pause le programme
// pour éviter que la fenêtre se ferme aussitôt ouverte
int continuer = 1;
SDL_Event event;
while ( continuer ) {
    SDL_WaitEvent(&event);
    switch ( event.type ) {
        case SDL_QUIT:
        // quitte et ferme la fenêtre
            continuer = 0;
            break;
        default:
            // ne fait rien
            break;
        }
    }
}
int main(int argc, char *argv[]){
    SDL_Surface *ecran = NULL, *imageDeFond = NULL, *sprite = NULL;
    SDL_Rect positionFond, positionSprite;
    positionFond.x = 0;
    positionFond.y = 0;
    positionSprite.x = 495;
    positionSprite.y = 455;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetIcon(SDL_LoadBMP("p1.bmp"), NULL);
    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    imageDeFond = SDL_LoadBMP("p1.bmp");
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
    /* On charge l'image : */
    sprite = SDL_LoadBMP("p1.bmp");
    /* On rend le vert derrière le sprite transparent : */
    SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 34, 177, 76));
    /* On blitte l'image maintenant transparente sur le fond : */
    SDL_BlitSurface(sprite, NULL, ecran, &positionSprite);
    SDL_Flip(ecran);
    pause();
    SDL_FreeSurface(imageDeFond);
    SDL_FreeSurface(sprite);
    SDL_Quit();
    return EXIT_SUCCESS;
}





#include <SDL2/SDL.h>
#include <stdio.h>
 
/*#include "../include/constantes.c"*/ 
 
void Mouvement(int Carte[][26], SDL_Rect *pos, int Direction, SDL_Renderer *render);   
 
int lvl1(SDL_Renderer *render)
{  
 
    // On crée des variables
    SDL_Rect position, positionJoueur;
    SDL_Surface *SPerso[5] = {NULL};
    SDL_Texture *TPerso[5] = {NULL};
    SDL_Texture *PersoActuelle = NULL;
 
    // Compteur_Variable
    int i;
    int j;
 
    // Definit les images sur les Surfaces Perso[Orientation]
    SPerso[1]=SDL_LoadBMP("../projet/local/c/p1.bmp");
    SPerso[4]=SDL_LoadBMP("../projet/local/c/p1.bmp");
    SPerso[2]=SDL_LoadBMP("../projet/local/c/p1.bmp");
    SPerso[3]=SDL_LoadBMP("../projet/local/c/p1.bmp");
 
    // Définition de la Carte
    int Carte[11][26];
 
    for(j = 1; j < 5; j++)
    {  
        if(SPerso[j] == NULL)
        {  
            printf("%d : Erreur SDL chargement de l'image Personnage \n",j );
            exit(EXIT_FAILURE);
        }
    }
 
    for(i = 1; i < 5; i++)
    {
        TPerso[i] = SDL_CreateTextureFromSurface(render, SPerso[i]);
        SDL_FreeSurface(SPerso[i]);
        SDL_Log("Free de la sufrace du perso %d", i);
    }
     
 
 
    // On remet le render vierge
    SDL_RenderClear(render);
 
    // On Définit la position du Joueur
    PersoActuelle = TPerso[BAS];
    if(PersoActuelle == NULL)
        SDL_Log("Erreur lors du chargement du personnage actuelle");
    positionJoueur.x = 3;
    positionJoueur.y = 3;
    position.w = 100;
    position.h = 100;
 
/*-------------------------------------*/
/*------------ Boucle infini ----------*/
/*-------------------------------------*/
    SDL_bool run = SDL_TRUE;
    while(run)
    {  
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {  
                case SDL_QUIT:
                    run = SDL_FALSE;
                    break;
 
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            run = SDL_FALSE;
                                break;
                        case SDLK_DOWN:
                            Mouvement(Carte, &positionJoueur, BAS, render);
                            break;
                        case SDLK_UP:
                            Mouvement(Carte, &positionJoueur, HAUT, render);
                            break;
                        case SDLK_RIGHT:
                            Mouvement(Carte, &positionJoueur, DROITE, render);
                            break;
                        case SDLK_LEFT:
                            Mouvement(Carte, &positionJoueur, GAUCHE, render);
                            break;
 
                        default:
                            break;
                    }
 
                default:
                    break;
 
            }
        }
 
        position.x = positionJoueur.x * TAILLE_BLOCK;
        position.y = positionJoueur.y * TAILLE_BLOCK;
 
        if(SDL_RenderCopy(render, PersoActuelle, NULL, &position) != 0)
            SDL_Log("Erreur lors de l'affichage à l'écran");
 
        SDL_RenderPresent(render);
 
    }
    SDL_DestroyRenderer(render);
    SDL_Quit();
    exit(EXIT_FAILURE);
}
 
void Mouvement(int Carte[][26], SDL_Rect *pos, int Direction, SDL_Renderer *render)
{
    SDL_Log("Entrée fonction Mouvement");
    switch(Direction)
    {  
        case BAS:
            pos->y++;
             
            break;
 
        case HAUT:
            pos->y--;
             
            break;
 
        case DROITE:
            pos->x++;
             
            break;
 
        case GAUCHE:
            pos->x--;
             
            break;
 
        default:
            break;
    }
 
 
}