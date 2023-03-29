#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constantes.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

tile_t * init_tile(SDL_Renderer * render, int x, int y){
    tile_t * tile = malloc(sizeof(tile_t));

    tile->position.x = x;
    tile->position.y = y;

    tile->sTile = IMG_Load("grass.png");

    tile->tTile = SDL_CreateTextureFromSurface(render, tile->sTile);
    SDL_FreeSurface(tile->sTile);
    tile->sTile = NULL;

    tile->type = GRASS;
    tile->arrose = false;
    tile->jours = 0;

    return(tile);
}

void liste_tiles(SDL_Renderer * render, listeT_t * tiles){
    int i, j, k;
    tiles->nb_elem = 0;
    for(i = 41, k = 0; i < 111; i += 7, k++){
        for(j = 41; j < 76; j += 7){
            tiles->tiles[k] = init_tile(render, i, j);
            tiles->nb_elem++;
        }
    }
}

//Fonction de déplacement du personnage

void deplacerPers(player_t * player){
    switch(player->direction){
        case HAUT: player->position.y--; break;
        case BAS: player->position.y++; break;
        case GAUCHE: player->position.x--; break;
        case DROITE: player->position.x++; break;
        default: break;
    }
}

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

//Fonction qui va initialiser une plante et qui va la placer sur la terre la plus proche

void planter(SDL_Renderer *render, player_t * const player, tile_t * const tile, listeP_t * plantes){
    SDL_Rect dif;

    dif.x = player->position.x - tile->position.x;
    dif.y = player->position.y - tile->position.y;
    if((((dif.x >= -9 && dif.x <= -4) && (dif.y >= -6 && dif.y <= -3)) && player->direction == DROITE) ||
        (((dif.x >= 4 && dif.x <= 10) && (dif.y >= -6 && dif.y <= -3)) && player->direction == GAUCHE) ||
        (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -4 && dif.y <= 0)) && player->direction == HAUT) ||
        (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -12 && dif.y <= -8)) && player->direction == BAS))
    {
        plante_t * plante = malloc(sizeof(plante_t));

        int i;

        for(i = 0; i < PLANTE; i++){
            plante->sPlante[i] = NULL;
            plante->tPlante[i] = NULL;
        }

        plante->state = NEW;

        //Ajout des sprites dans le tableau de surfaces de la plante, dépendant de quelle plante il s'agit
        switch(player->seed){
            case cauliflower:                
                plante->sPlante[NEW] = IMG_Load("sprites/seeds/cauliflower/l1cauliflower.png");                
                plante->sPlante[SEMI] = IMG_Load("sprites/seeds/cauliflower/l2cauliflower.png");                
                plante->sPlante[FULL] = IMG_Load("sprites/seeds/cauliflower/cauliflower.png");
                plante->sPlante[PLANT] = IMG_Load("sprites/seeds/cauliflower/cauliflower.png");
            break;
            case melon: 
                plante->sPlante[NEW] = IMG_Load("sprites/seeds/melon/l1melon.png");
                plante->sPlante[SEMI] = IMG_Load("sprites/seeds/melon/l2melon.png"); 
                plante->sPlante[FULL] = IMG_Load("sprites/seeds/melon/l3melon.png");
                plante->sPlante[PLANT] = IMG_Load("sprites/seeds/melon/melon.png");
            break;
            case potato: 
                plante->sPlante[NEW] = IMG_Load("sprites/seeds/potato/l1potato.png");
                plante->sPlante[SEMI] = IMG_Load("sprites/seeds/potato/l2potato.png");
                plante->sPlante[FULL] = IMG_Load("sprites/seeds/potato/l3potato.png");
                plante->sPlante[PLANT] = IMG_Load("sprites/seeds/potato/potato.png");
            break;
            case pumpkin: 
                plante->sPlante[NEW] = IMG_Load("sprites/seeds/pumpkin/l1pumpkin.png");
                plante->sPlante[SEMI] = IMG_Load("sprites/seeds/pumpkin/l2pumpkin.png");
                plante->sPlante[FULL] = IMG_Load("sprites/seeds/pumpkin/l3pumpkin.png");
                plante->sPlante[PLANT] = IMG_Load("sprites/seeds/pumpkin/pumpkin.png");
            break;
            case tomato: 
                plante->sPlante[NEW] = IMG_Load("sprites/seeds/tomato/l1tomato.png");
                plante->sPlante[SEMI] = IMG_Load("sprites/seeds/tomato/l2tomato.png");
                plante->sPlante[FULL] = IMG_Load("sprites/seeds/tomato/l3tomato.png");
                plante->sPlante[PLANT] = IMG_Load("sprites/seeds/tomato/tomato.png");
            break;
        }

        plante->sPlante[DEAD] = IMG_Load("sprites/seeds/dead.png");

        //Création des textures et suppression des surfaces
        for(i = 0; i < PLANTE; i++){
            plante->tPlante[i] = SDL_CreateTextureFromSurface(render, plante->sPlante[i]);
            SDL_FreeSurface(plante->sPlante[i]);
            plante->sPlante[i] = NULL;
        }

        //Initialisation de la position de la plante sur la carte, de son type et ajout dans la liste des plantes
        plante->type = player->seed;
        plante->position = tile->position;

        plantes->plantes[plantes->nb_elem] = plante;
        plantes->nb_elem++;
    }
}

//Fonction qui va transformer de l'herbe en terre (changement de la texture et du type)

void becher(SDL_Renderer * render, player_t * const player, tile_t * tile){
    SDL_Rect dif;

    dif.x = player->position.x - tile->position.x;
    dif.y = player->position.y - tile->position.y;
    if((((dif.x >= -9 && dif.x <= -4) && (dif.y >= -6 && dif.y <= -3)) && player->direction == DROITE) ||
        (((dif.x >= 4 && dif.x <= 10) && (dif.y >= -6 && dif.y <= -3)) && player->direction == GAUCHE) ||
        (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -4 && dif.y <= 0)) && player->direction == HAUT) ||
        (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -12 && dif.y <= -8)) && player->direction == BAS))
    {
        SDL_DestroyTexture(tile->tTile);

        tile->sTile = IMG_Load("dirt.png");

        tile->tTile = SDL_CreateTextureFromSurface(render, tile->sTile);

        SDL_FreeSurface(tile->sTile);

        tile->type = DIRT;
    }
}

//Fonction qui va supprimer une ou plusieurs plante(s) de la liste de plantes (et donc de la carte)

void faucher(player_t * const player, listeP_t * plantes){
    plante_t * temp = malloc(sizeof(plante_t));
    SDL_Rect dif;
    int i, j;
    int elements = plantes->nb_elem;

    //Vérification pour savoir si il y a plusieurs plantes que l'on peut enlever en même temps

    for(i = 0; i < elements; i++){
        temp = plantes->plantes[i];

        dif.x = player->position.x - temp->position.x;
        dif.y = player->position.y - temp->position.y;
        if((((dif.x >= -9 && dif.x <= -4) && (dif.y >= -6 && dif.y <= -3)) && player->direction == DROITE) ||
            (((dif.x >= 4 && dif.x <= 10) && (dif.y >= -6 && dif.y <= -3)) && player->direction == GAUCHE) ||
            (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -4 && dif.y <= 0)) && player->direction == HAUT) ||
            (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -12 && dif.y <= -8)) && player->direction == BAS))
        {
            for(j = 0; j < PLANTE; j++){
                SDL_DestroyTexture(temp->tPlante[i]);
            }
            temp = NULL;
            plantes->nb_elem--;
        }
    }
}

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

//Fonction qui va changer l'état de l'arrosage d'une tile (et d'une plante si elle se trouve sur cette tile)

void arroser(SDL_Renderer * render, player_t * const player, tile_t * tile, listeP_t * plantes){
    SDL_Rect dif;

    dif.x = player->position.x - tile->position.x;
    dif.y = player->position.y - tile->position.y;
    if((((dif.x >= -9 && dif.x <= -4) && (dif.y >= -6 && dif.y <= -3)) && player->direction == DROITE) ||
        (((dif.x >= 4 && dif.x <= 10) && (dif.y >= -6 && dif.y <= -3)) && player->direction == GAUCHE) ||
        (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -4 && dif.y <= 0)) && player->direction == HAUT) ||
        (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -12 && dif.y <= -8)) && player->direction == BAS))
    {
        if(tile->type == DIRT){
            int i;
            tile->arrose = true;

            for(i = 0; i < plantes->nb_elem; i++){
                if(tile->position.x == plantes->plantes[i]->position.x && tile->position.y == plantes->plantes[i]->position.y){
                    plantes->plantes[i]->arrose = true;
                    break;
                }
            }
        }
    }
}

//Fonction qui va ajouter une plante à l'inventaire si elle est au maximum

void recolter(SDL_Renderer * render, player_t * player, tile_t * tile, listeP_t * plantes){
    SDL_Rect dif;

    dif.x = player->position.x - tile->position.x;
    dif.y = player->position.y - tile->position.y;
    if((((dif.x >= -9 && dif.x <= -4) && (dif.y >= -6 && dif.y <= -3)) && player->direction == DROITE) ||
        (((dif.x >= 4 && dif.x <= 10) && (dif.y >= -6 && dif.y <= -3)) && player->direction == GAUCHE) ||
        (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -4 && dif.y <= 0)) && player->direction == HAUT) ||
        (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -12 && dif.y <= -8)) && player->direction == BAS))
    {
        plante_t * temp = malloc(sizeof(plante_t));
        int i, j;
        int elements = plantes->nb_elem;

        for(i = 0; i < elements; i++){
            temp = plantes->plantes[i];
            if(tile->position.x == temp->position.x && tile->position.y == temp->position.y && temp->state == FULL){
                player->inventaire[temp->type]++;

                for(j = 0; j < PLANTE; j++){
                    SDL_DestroyTexture(temp->tPlante[j]);
                }
                temp = NULL;
                plantes->nb_elem--;
            }
        }
    }
}

//Fonction qui va choisir l'action à faire

void action(SDL_Renderer * render, player_t * player, tile_t * tile, listeP_t * plantes){
    switch(player->holding){
        case TOOL:
            switch(player->tool){
                case hoe: if(tile->type == GRASS) becher(render, player, tile); break;
                case scythe: faucher(player, plantes); break;
                case can: arroser(render, player, tile, plantes); break;
                default: break;
            }; break;
        case SEED: if(tile->type == DIRT) planter(render, player, tile, plantes); break;
        case NOTHING : recolter(render, player, tile, plantes); break;
        default: break;
    }
}

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

//Fonction de jeu principal, avec une boucle qui vérifie que le jeu n'est pas fermé

void jouer(SDL_Renderer *render){
    player_t *player = malloc(sizeof(player_t));
    plante_t * tempPlante = malloc(sizeof(plante_t));

    listeP_t * plantes = malloc(sizeof(listeP_t));
    listeT_t * tiles = malloc(sizeof(listeT_t));

    tool_t outilAct = hoe;
    seed_t graineAct = cauliflower;

    SDL_Rect position, backRect, dirt, contour, inventory, boite, coin;
    SDL_Surface *sBackground = NULL;
    SDL_Texture *tBackground = NULL;
    SDL_Texture *persoActuel = NULL;

    SDL_Surface * sFrames[3];
    SDL_Texture * tFrames[3];
    SDL_Surface * sContour = NULL;
    SDL_Texture * tContour = NULL;
    SDL_Surface * sInv = NULL;
    SDL_Texture * tInv = NULL;

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

    int i, j;
    bool inv = false;

    char * text = malloc(sizeof(char));

    for(i = 0; i < PERSO; i++){
        player->sPerso[i] = NULL;
        player->tPerso[i] = NULL;
    }

    //Initialisation des sprites

    sBackground = IMG_Load("sprites/map/map.png");

    player->sPerso[0] = IMG_Load("sprites/player/player.png");

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

    for(i = 0; i < PERSO; i++){
        player->tPerso[i] = SDL_CreateTextureFromSurface(render, player->sPerso[i]);
        SDL_FreeSurface(player->sPerso[i]);
        player->sPerso[i] = NULL;
    }

    tBackground = SDL_CreateTextureFromSurface(render, sBackground);
    SDL_FreeSurface(sBackground);
    sBackground = NULL;

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

    SDL_RenderClear(render);

    persoActuel = player->tPerso[0];
    if(persoActuel == NULL){
        SDL_Log("Erreur lors du chargement du personnage actuelle");
    }

    player->direction = BAS;
    
    player->position.x = 0;
    player->position.y = 0;

    for(i = 0; i < 5; i++){
        player->inventaire[i] = 0;
    }

    player->money = 20;

    player->cooldown = 500;
    player->holding = NOTHING;
    player->tool = hoe;
    player->seed = cauliflower;

    player->last_action = 0;

    /*-----------------------------*/

    /*tile->position.x = 41;
    tile->position.y = 41;

    tile->arrose = false;
    tile->type = GRASS;

    tile2->position.x = 48;
    tile2->position.y = 41;

    tile2->position.x = 41;
    tile2->position.y = 48;

    tile2->arrose = false;
    tile2->type = GRASS;*/

    /*-----------------------------*/

    position.w = 100;
    position.h = 100;

    backRect.w = 1296;
    backRect.h = 720;
    backRect.x = 0;
    backRect.y = 0;

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

    plantes->plantes = malloc(sizeof(plante_t *));

    liste_tiles(render, tiles);

    SDL_Rect dif;

    //Boucle de jeu

    bool is_running = true;
    SDL_Event event;
    while(is_running){
        SDL_RenderClear(render);
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT: is_running = false;break;

                //Vérification des touches pressées
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        //Fermeture du jeu
                        case SDLK_ESCAPE: is_running = false; break;

                        //Déplacement du personnage
                        case SDLK_z: player->direction = HAUT; deplacerPers(player); break;
                        case SDLK_s: player->direction = BAS; deplacerPers(player); break;
                        case SDLK_q: player->direction = GAUCHE; deplacerPers(player); break;
                        case SDLK_d: player->direction = DROITE; deplacerPers(player); break;

                        //Action performée
                        case SDLK_e: if(SDL_GetTicks() - player->last_action > player->cooldown){
                            dif.x = player->position.x - tile->position.x;
                            dif.y = player->position.y - tile->position.y;
                            if((((dif.x >= -9 && dif.x <= -4) && (dif.y >= -6 && dif.y <= -3)) && player->direction == DROITE) ||
                                (((dif.x >= 4 && dif.x <= 10) && (dif.y >= -6 && dif.y <= -3)) && player->direction == GAUCHE) ||
                                (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -4 && dif.y <= 0)) && player->direction == HAUT) ||
                                (((dif.x >= -3 && dif.x <= 3) && (dif.y >= -12 && dif.y <= -8)) && player->direction == BAS))
                                action(render, player, tile, plantes);
                            player->last_action = SDL_GetTicks();
                        }; break;

                        case SDLK_a: jour_suivant(render, player, plantes); break;

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
                    }
                default: break;
            }
        }

        //Affichage de tous les éléments sur la carte
        if(SDL_RenderCopy(render, tBackground, NULL, &backRect) != 0){
            SDL_Log("Erreur lors de l'affichage à l'écran");
        }

        for(i = 0; i < tiles->nb_elem; i++){

            position.x = tiles->tiles[i]->position.x * STEP;
            position.y = tiles->tiles[i]->position.y * STEP;

            if(SDL_RenderCopy(render, tiles->tiles[i]->tTile, NULL, &position) != 0){
                SDL_Log("Erreur lors de l'affichage à l'écran");
            }
        }

        if(plantes->nb_elem > 0){
            for(i = 0; i < plantes->nb_elem; i++){
                tempPlante = plantes->plantes[i];

                position.x = tempPlante->position.x * STEP;
                position.y = tempPlante->position.y * STEP;

                if(SDL_RenderCopy(render, tempPlante->tPlante[tempPlante->state], NULL, &position) != 0){
                    SDL_Log("Erreur lors de l'affichage à l'écran");
                }
            }
        }

        position.x = player->position.x * STEP;
        position.y = player->position.y * STEP;

        if(SDL_RenderCopy(render, persoActuel, NULL, &position) != 0){
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
                afficheText(render, boite, text);
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
            afficheText(render, coin, text);
        }

        
        //printf("%s\n", text);

        /*printf("Inventaire : [ ");
        for(i = 0; i < 5; i++){
            printf("%d ", player->inventaire[i]);
            if(i != 4){
                printf("| ");
            }
        }
        printf("]\n");*/

        printf("Positions perso : [%d | %d]\n", player->position.x, player->position.y);

        SDL_RenderPresent(render);
    }

    for(i = 0; i < PERSO; i++){
        SDL_DestroyTexture(player->tPerso[i]);
        player->tPerso[i] = NULL;
    }
    free(player);
    player = NULL;

    SDL_DestroyTexture(tile->tTile);
    tile->tTile = NULL;
    free(tile);
    tile = NULL;

    for(i = 0; i < plantes->nb_elem; i++){
        tempPlante = plantes->plantes[i];
        for(j = 0; j < PLANTE; j++){
            SDL_DestroyTexture(tempPlante->tPlante[j]);
            tempPlante->tPlante[i] = NULL;
        }
        free(tempPlante);
    }

    free(plantes->plantes);
    free(plantes);
    plantes = NULL;

    free(tiles);
    tiles = NULL;

    tempPlante = NULL;

    SDL_DestroyTexture(tBackground);

    for(i = 0; i < 3; i++){
        SDL_DestroyTexture(tFrames[i]);
        tFrames[i] = NULL;
    }

    SDL_DestroyTexture(tContour);
    tContour = NULL;
}

int main(){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    if(TTF_Init() == -1) {
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

    SDL_Window *win = NULL;
    win = SDL_CreateWindow("Daniels' Valley", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

    if(win){
        //Création d'un render un des positions du personnage
        SDL_Renderer *render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
        jouer(render);
        SDL_DestroyRenderer(render);
    }
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}