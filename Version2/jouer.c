#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constantes.h"
#include "action.h"
#include "deplacer.h"
#include "changeroutils.h"
#include "text.h"
#include "init.h"
#include "verif.h"
#include "joursuivant.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//Fonction de jeu principal, avec une boucle qui vérifie que le jeu n'est pas fermé

void jouer(SDL_Renderer *render){
    player_t *player = malloc(sizeof(player_t));
    plante_t * tempPlante = malloc(sizeof(plante_t));
    tile_t * tempTile = malloc(sizeof(tile_t));

    listeP_t * plantes = malloc(sizeof(listeP_t));
    listeT_t * tiles = malloc(sizeof(listeT_t));

    tool_t outilAct = hoe;
    seed_t graineAct = cauliflower;

    SDL_Rect position, backRect, contour, inventory, boite, coin;

    SDL_Surface *sBackground[2];
    SDL_Texture *tBackground[2];
    SDL_Texture *screenAct = NULL;

    SDL_Texture *persoActuel = NULL;

    SDL_Surface * sFrames[3];
    SDL_Texture * tFrames[3];
    SDL_Surface * sContour = NULL;
    SDL_Texture * tContour = NULL;
    SDL_Surface * sInv = NULL;
    SDL_Texture * tInv = NULL;

    SDL_Surface * sFrameSelect = NULL;
    SDL_Texture * tFrameSelect = NULL;

    SDL_Surface * sCoin = NULL;
    SDL_Texture * tCoin = NULL;

    SDL_Surface * sTools[OUTIL];
    SDL_Texture * tTools[OUTIL];
    SDL_Surface * sSeeds[PLANTE];
    SDL_Texture * tSeeds[PLANTE];

    SDL_Surface * sPlante[PLANTE];
    SDL_Texture * tPlante[PLANTE];

    SDL_Rect frames[3];
    SDL_Rect invent[PLANTE];

    SDL_Rect selection;

    SDL_Rect portes[2];

    TTF_Font * police = NULL;

    int i, j, tileActuelle;
    bool inv = false;

    int walking = SDL_GetTicks();

    char * text = malloc(sizeof(char) * 50);

    //Initialisation des sprites

    sBackground[OUTSIDE] = IMG_Load("sprites/map/map.png");
    sBackground[HOME] = IMG_Load("sprites/map/home.png");

    player->sPerso = IMG_Load("sprites/player/bitmap.png");

    for(i = 0; i < 3; i++){
        sFrames[i] = IMG_Load("sprites/frames/frame.png");
    }

    /*-----------------------------*/

    sTools[hoe] = IMG_Load("sprites/tools/hoe.png");

    sTools[scythe] = IMG_Load("sprites/tools/scythe.png");

    sTools[can] = IMG_Load("sprites/tools/can.png");

    /*----------------------------*/

    sSeeds[cauliflower] = IMG_Load("sprites/seeds/cauliflower/cauliflowerBag.png");

    sSeeds[melon] = IMG_Load("sprites/seeds/melon/melonBag.png");

    sSeeds[potato] = IMG_Load("sprites/seeds/potato/potatoBag.png");

    sSeeds[pumpkin] = IMG_Load("sprites/seeds/pumpkin/pumpkinBag.png");

    sSeeds[tomato] = IMG_Load("sprites/seeds/tomato/tomatoBag.png");

    /*----------------------------*/

    sPlante[cauliflower] = IMG_Load("sprites/seeds/cauliflower/cauliflower.png");

    sPlante[melon] = IMG_Load("sprites/seeds/melon/melon.png");

    sPlante[potato] = IMG_Load("sprites/seeds/potato/potato.png");

    sPlante[pumpkin] = IMG_Load("sprites/seeds/pumpkin/pumpkin.png");

    sPlante[tomato] = IMG_Load("sprites/seeds/tomato/tomato.png");
    
    /*-----------------------------*/

    sContour = IMG_Load("sprites/frames/frame2.png");

    /*-----------------------------*/

    sFrameSelect = IMG_Load("sprites/frames/frameSelect.png");

    /*-----------------------------*/

    sInv = IMG_Load("sprites/frames/inventory.png");

    /*-----------------------------*/

    sCoin = IMG_Load("sprites/tools/coin.png");

    /*for(j = 0; j < 5; j++){
        if(sPerso[j] == NULL){
            printf("%d : Erreur SDL chargement de l'image Personnage \n", j);
            return -1;
        }
    }*/

    //Creation de textures à partir des sprites

    for(i = 0; i < 3; i++){
        tFrames[i] = SDL_CreateTextureFromSurface(render, sFrames[i]);
        SDL_FreeSurface(sFrames[i]);
        sFrames[i] = NULL;
    }

    tContour = SDL_CreateTextureFromSurface(render, sContour);
    SDL_FreeSurface(sContour);
    sContour = NULL;

    tFrameSelect = SDL_CreateTextureFromSurface(render, sFrameSelect);
    SDL_FreeSurface(sFrameSelect);
    sFrameSelect = NULL;

    player->tPerso = SDL_CreateTextureFromSurface(render, player->sPerso);
    SDL_FreeSurface(player->sPerso);
    player->sPerso = NULL;

    tBackground[OUTSIDE] = SDL_CreateTextureFromSurface(render, sBackground[OUTSIDE]);
    SDL_FreeSurface(sBackground[OUTSIDE]);
    sBackground[OUTSIDE] = NULL;

    tBackground[HOME] = SDL_CreateTextureFromSurface(render, sBackground[HOME]);
    SDL_FreeSurface(sBackground[HOME]);
    sBackground[HOME] = NULL;

    /*-----------------------------*/

    for(i = 0; i < OUTIL; i++){
        tTools[i] = SDL_CreateTextureFromSurface(render, sTools[i]);
        SDL_FreeSurface(sTools[i]);
        sTools[i] = NULL;
    }

    for(i = 0; i < PLANTE; i++){
        tSeeds[i] = SDL_CreateTextureFromSurface(render, sSeeds[i]);
        SDL_FreeSurface(sSeeds[i]);
        sSeeds[i] = NULL;
    }

    /*-----------------------------*/

    for(i = 0; i < PLANTE; i++){
        tPlante[i] = SDL_CreateTextureFromSurface(render, sPlante[i]);
        SDL_FreeSurface(sPlante[i]);
        sPlante[i] = NULL;
    }

    /*-----------------------------*/

    tInv = SDL_CreateTextureFromSurface(render, sInv);
    SDL_FreeSurface(sInv);
    sInv = NULL;

    /*-----------------------------*/

    tCoin = SDL_CreateTextureFromSurface(render, sCoin);
    SDL_FreeSurface(sCoin);
    sCoin = NULL;

    /*-----------------------------*/

    if ((police = TTF_OpenFont("sprites/font/font.ttf", 50)) == NULL){
        SDL_Log("Erreur lors du chargement de la police");
    }

    /*-----------------------------*/

    screenAct = tBackground[OUTSIDE];

    persoActuel = player->tPerso;
    if(persoActuel == NULL){
        SDL_Log("Erreur lors du chargement du personnage actuelle");
    }

    player->direction = BAS;
    player->frame = 0;
    
    player->position.x = 19;
    player->position.y = 35;

    for(i = 0; i < 5; i++){
        player->inventaire[i] = 0;
    }

    player->money = 20;

    player->jours = 0;

    player->local = OUTSIDE;

    player->cooldown = 500;
    player->holding = NOTHING;
    player->tool = hoe;
    player->seed = cauliflower;

    player->last_action = 0;
    player->last_frame = SDL_GetTicks();

    player->vel = false;

    /*-----------------------------*/

    position.w = 100;
    position.h = 100;

    backRect.w = 1296;
    backRect.h = 720;
    backRect.x = 0;
    backRect.y = 0;

    portes[OUTSIDE].x = 19;
    portes[OUTSIDE].y = 31;

    portes[HOME].x = 101;
    portes[HOME].y = 90;

    /*-----------------------------*/

    for(i = 0; i < 3; i++){
        frames[i].h = frames[i].w = 100;
        frames[i].y = 600;
    }

    frames[NOTHING].x = 529;
    frames[TOOL].x = 587;
    frames[SEED].x = 645;

    contour.w = contour.h = 100;
    contour.y = frames[NOTHING].y;
    contour.x = frames[NOTHING].x;

    inventory.w = 640;
    inventory.h = 360;
    inventory.x = 325;
    inventory.y = 125;

    for(i = 0; i < PLANTE; i++){
        invent[i].h = invent[i].w = 200;
        invent[i].y = 205;
    }

    invent[cauliflower].x = 340;
    invent[melon].x = 440;
    invent[potato].x = 540;
    invent[pumpkin].x = 640;
    invent[tomato].x = 740;

    //boite.h = boite.w = 100;

    /*-----------------------------*/

    plantes->nb_elem = 0;
    tiles->nb_elem = 0;

    for(i = 0; i < 50; i++){
        plantes->plantes[i] = NULL;
        tiles->tiles[i] = NULL;
    }

    liste_tiles(render, tiles);

    //Boucle de jeu

    bool is_running = true;
    SDL_Event event;
    while(is_running){
        SDL_RenderClear(render);
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT: is_running = false; break;

                //Vérification des touches pressées
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        //Fermeture du jeu
                        case SDLK_ESCAPE: is_running = false; break;

                        //Déplacement du personnage
                        case SDLK_z: player->direction = HAUT; player->vel = true; /*deplacerPers(player);*/ break;
                        case SDLK_s: player->direction = BAS; player->vel = true; /*deplacerPers(player);*/ break;
                        case SDLK_q: player->direction = GAUCHE; player->vel = true; /*deplacerPers(player);*/ break;
                        case SDLK_d: player->direction = DROITE; player->vel = true; /*deplacerPers(player);*/ break;

                        //Action performée
                        case SDLK_e: if(SDL_GetTicks() - player->last_action > player->cooldown){
                            action(render, player, tiles, plantes);
                            player->last_action = SDL_GetTicks();
                        }; break;

                        case SDLK_RIGHT: if(player->holding == SEED){
                            player->holding = NOTHING;
                            contour.x = frames[NOTHING].x;
                        }
                        else{
                            player->holding++;
                            contour.x += 58;
                        }; break;

                        case SDLK_LEFT: if(player->holding == NOTHING){
                            player->holding = SEED;
                            contour.x = frames[SEED].x;
                        }
                        else{
                            player->holding--;
                            contour.x -= 58;
                        }; break;
                        
                        case SDLK_UP: changer_outil(player, HAUT, &outilAct, &graineAct); break;

                        case SDLK_DOWN: changer_outil(player, BAS, &outilAct, &graineAct); break;

                        case SDLK_TAB: inv = inv ? false : true; break;

                        default: break;
                    }; break;
                case SDL_KEYUP:
                    switch(event.key.keysym.sym){
                        case SDLK_z: player->vel = false; break;
                        case SDLK_s: player->vel = false; break;
                        case SDLK_q: player->vel = false; break;
                        case SDLK_d: player->vel = false; break;
                        default: break;
                    }
                default: break;
            }
        }

        tileActuelle = verife_tile(player, tiles);

        if(verife_porte(portes[player->local], player)){
            player->local = player->local == OUTSIDE ? HOME : OUTSIDE;
            player->position.x = portes[player->local].x;
            player->position.y = portes[player->local].y;
            switch(player->local){
                case OUTSIDE: player->position.y += 2; break;
                case HOME: player->position.y -= 2; break;
                default: break;
            }
        }

        if(player->vel && (SDL_GetTicks() - walking >= FPS)){
            if((player->local == HOME && ((player->position.x >= 82 && player->position.x <= 157) && (player->position.y >= 33 && player->position.y <= 90))) || player->local == OUTSIDE){
                switch(player->direction){
                    case HAUT: player->position.y--; walking = SDL_GetTicks(); break;
                    case BAS: player->position.y++; walking = SDL_GetTicks(); break;
                    case GAUCHE: player->position.x--; walking = SDL_GetTicks(); break;
                    case DROITE: player->position.x++; walking = SDL_GetTicks(); break;
                    default: break;
                }
            }
            else{
                switch(player->direction){
                    case HAUT: player->position.y += 2; walking = SDL_GetTicks(); break;
                    case BAS: player->position.y -= 2; walking = SDL_GetTicks(); break;
                    case GAUCHE: player->position.x += 2; walking = SDL_GetTicks(); break;
                    case DROITE: player->position.x -= 2; walking = SDL_GetTicks(); break;
                    default: break;
                }
            }
        }

        //Affichage de tous les éléments sur la carte
        if(SDL_RenderCopy(render, tBackground[player->local], NULL, &backRect) != 0){
            SDL_Log("Erreur lors de l'affichage à l'écran");
        }

        if(player->local == OUTSIDE){
            if(tiles->nb_elem > 0){
                for(i = 0; i < tiles->nb_elem; i++){
                    tempTile = tiles->tiles[i];

                    position.x = tempTile->position.x * STEP;
                    position.y = tempTile->position.y * STEP;

                    if(tempTile->tTile != NULL){
                        if(SDL_RenderCopy(render, tempTile->tTile, NULL, &position) != 0){
                            SDL_Log("Erreur lors de l'affichage à l'écran");
                        }
                    }
                    tempTile = NULL;
                }
            }

            if(tileActuelle >= 0){
                selection = tiles->tiles[tileActuelle]->position;

                position.x = selection.x * STEP;
                position.y = selection.y * STEP;

                if(SDL_RenderCopy(render, tFrameSelect, NULL, &position) != 0){
                    SDL_Log("Erreur lors de l'affichage à l'écran");
                }
            }

            if(plantes->nb_elem > 0){
                for(i = 0; i < plantes->nb_elem; i++){
                    tempPlante = plantes->plantes[i];

                    position.x = tempPlante->position.x * STEP;
                    position.y = tempPlante->position.y * STEP;

                    if(tempPlante->tPlante[tempPlante->state] != NULL){
                        if(SDL_RenderCopy(render, tempPlante->tPlante[tempPlante->state], NULL, &position) != 0){
                            SDL_Log("Erreur lors de l'affichage à l'écran");
                        }
                    }
                    tempTile = NULL;
                }
            }
        }

        if(player->vel){
            if(SDL_GetTicks() - player->last_frame >= ANIM){
                if(player->frame == FRAMES - 1){
                    player->frame = 0;
                }
                else{
                    player->frame = FRAMES -1;
                }
                player->last_frame = SDL_GetTicks();
            }
        }
        else{
            player->frame = 1;
        }

        player->source.x = PERS_WIDTH * player->frame;
        player->source.y = PERS_HEIGHT * player->direction;
        player->source.h = PERS_HEIGHT;
        player->source.w = PERS_WIDTH;

        position.x = player->position.x * STEP;
        position.y = player->position.y * STEP;


        if(SDL_RenderCopy(render, persoActuel, &player->source, &position) != 0){
            SDL_Log("Erreur lors de l'affichage à l'écran");
        }

        for(i = 0; i < 3; i++){
            if(SDL_RenderCopy(render, tFrames[i], NULL, &frames[i]) != 0){
                SDL_Log("Erreur lors de l'affichage à l'écran");
            }
        }

        if(SDL_RenderCopy(render, tTools[outilAct], NULL, &frames[TOOL]) != 0){
            SDL_Log("Erreur lors de l'affichage à l'écran");
        }

        if(SDL_RenderCopy(render, tSeeds[graineAct], NULL, &frames[SEED]) != 0){
            SDL_Log("Erreur lors de l'affichage à l'écran");
        }

        if(SDL_RenderCopy(render, tContour, NULL, &contour) != 0){
            SDL_Log("Erreur lors de l'affichage à l'écran");
        }

        if(inv){
            if(SDL_RenderCopy(render, tInv, NULL, &inventory) != 0){
                SDL_Log("Erreur lors de l'affichage à l'écran");
            }

            for(i = 0; i < PLANTE; i++){
                if(SDL_RenderCopy(render, tPlante[i], NULL, &invent[i]) != 0){
                    SDL_Log("Erreur lors de l'affichage à l'écran");
                }
            }

            for(i = 0; i < PLANTE; i++){
                sprintf(text, "%d", player->inventaire[i]);
                boite.x = invent[i].x + 88;
                boite.y = 350;
                afficheText(render, boite, text, police);
            }

            coin = invent[potato];
            coin.y -= 90;
            coin.x -= 50;
            if(SDL_RenderCopy(render, tCoin, NULL, &coin) != 0){
                SDL_Log("Erreur lors de l'affichage à l'écran");
            }

            if(player->money < 10){
                sprintf(text, "00%d", player->money);
            }
            else if(player->money >= 10 && player->money < 100){
                sprintf(text, "0%d", player->money);
            }
            else{
                sprintf(text, "%d", player->money);
            }

            coin = invent[potato];
            coin.x += 90;
            coin.y -= 13;
            afficheText(render, coin, text, police);
        }

        sprintf(text, "Jour %d", player->jours);
        boite.x = 1100;
        boite.y = 20;
        afficheText(render, boite, text, police);

        
        //printf("%s\n", text);

        /*printf("Inventaire : [ ");
        for(i = 0; i < 5; i++){
            printf("%d ", player->inventaire[i]);
            if(i != 4){
                printf("| ");
            }
        }
        printf("]\n");*/

        //printf("Positions perso : [%d | %d]\n", player->position.x, player->position.y);

        SDL_RenderPresent(render);
    }

    SDL_DestroyTexture(player->tPerso);
    player->tPerso = NULL;

    free(player);
    player = NULL;

    for(i = 0; i < tiles->nb_elem; i++){
        tempTile = tiles->tiles[i];
        SDL_DestroyTexture(tempTile->tTile);
        tempTile->tTile = NULL;
        free(tempTile);
        tempTile = NULL;
    }

    free(tiles);
    tiles = NULL;

    for(i = 0; i < plantes->nb_elem; i++){
        tempPlante = plantes->plantes[i];
        for(j = 0; j < PLANTE; j++){
            SDL_DestroyTexture(tempPlante->tPlante[j]);
            tempPlante->tPlante[i] = NULL;
        }
        free(tempPlante);
        tempPlante = NULL;
    }

    free(plantes);
    plantes = NULL;

    SDL_DestroyTexture(tBackground[OUTSIDE]);
    SDL_DestroyTexture(tBackground[HOME]);

    for(i = 0; i < 3; i++){
        SDL_DestroyTexture(tFrames[i]);
        tFrames[i] = NULL;
    }

    SDL_DestroyTexture(tContour);
    tContour = NULL;
}