#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#define LARGEUR_TILE 24  // hauteur et largeur des tiles.
#define HAUTEUR_TILE 16

#define NOMBRE_BLOCS_LARGEUR 15  // nombre a afficher en x et y
#define NOMBRE_BLOCS_HAUTEUR 13

void Afficher (SDL_Renderer*, SDL_Texture*, char**, int, int);



int main(int argc, char *argv[])
{
    SDL_Window *pWindow=NULL;           //Pointeur sur la fenêtre, ref d'un window win32
    SDL_Renderer *pRenderer=NULL;       //Pointeur sur le Rendus, ref rendu encapsulé dans window

    //Requis pour utiliser la SDL
    if(SDL_Init(SDL_INIT_EVERYTHING)>=0)    //INIT_EVERYTHING = initialise l'audio, la vidéo, les contrôles,... cf; SDL wiki/API by name/SDL_Init
    {
        pWindow = SDL_CreateWindow("TILESET_TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_TILE*NOMBRE_BLOCS_LARGEUR, HAUTEUR_TILE*NOMBRE_BLOCS_HAUTEUR, SDL_WINDOW_SHOWN);

        //si succès, créer window et renderer
        if(pWindow!=NULL)
        {
            pRenderer=SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_PRESENTVSYNC);
            SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

            //------------------------------------------------------------------------------------------------//
            //Tilemapping

            char* table[] = {
                "000000000000000",
                "000000000000000",
                "000000000000000",
                "000000000000000",
                "000000000000000",
                "000000022122200",
                "000000000000000",
                "003400000000000",
                "005600000000000",
                "005600000000000",
                "005600000000000",
                "777777777777777",
                "777777777777777"
            };

            SDL_Surface *tileset = NULL;
            SDL_Texture *textuTil = NULL;
            SDL_Event event;
            int continuer = 1, tempsPrecedent = 0, tempsActuel = 0;
            int statut = EXIT_FAILURE;

            tileset = IMG_Load("assets/tileset1.png");
            if (tileset == NULL)
            {
                fprintf(stderr, "Erreur chargement image droite : %s", SDL_GetError());
            }

            textuTil = SDL_CreateTextureFromSurface(pRenderer, tileset);
            if (textuTil == NULL)
            {
                fprintf(stderr, "Erreur SDL_CreateTexturetil : %s", SDL_GetError());
            }
            SDL_FreeSurface(tileset);

            Afficher(pRenderer, textuTil, table, NOMBRE_BLOCS_LARGEUR, NOMBRE_BLOCS_HAUTEUR);
            while(continuer)
            {
                SDL_PollEvent(&event);
                switch(event.type)
                {
                    case SDL_QUIT:
                        continuer = 0;
                        break;

                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym)
                        {
                            case SDLK_ESCAPE:
                                continuer = 0;
                                break;
                        }
                        break;
                }

                tempsActuel = SDL_GetTicks();
                if (tempsActuel - tempsPrecedent > 30) /* si 30ms se sont écoulé depuis le dernier tour de la boucle plus le temps est petit plus il se deplace vite */
                {
                    tempsPrecedent = tempsActuel; // le temps actuel devient le temps présent
                }
                else
                {
                    SDL_Delay(30 - (tempsActuel - tempsPrecedent));
                }

                SDL_RenderPresent(pRenderer);
            }

            //------------------------------------------------------------------------------------------------//

            //SDL_Delay(10000);

            SDL_DestroyTexture(textuTil);
            SDL_DestroyRenderer(pRenderer); //On supprime tout ce qui à été créer
            SDL_DestroyWindow(pWindow);
            SDL_Quit();
        }

    }

    return 0;
}


void Afficher(SDL_Renderer* pRenderer, SDL_Texture* textuTil, char** table, int nombre_blocs_largeur, int nombre_blocs_hauteur) {
    int i, j;
    SDL_Rect Rect_dest;
    SDL_Rect Rect_source;
    Rect_source.w = LARGEUR_TILE;
    Rect_dest.w = LARGEUR_TILE;
    Rect_source.h = HAUTEUR_TILE;
    Rect_dest.h = HAUTEUR_TILE;
    for(i = 0 ; i < NOMBRE_BLOCS_LARGEUR; i++)
    {
        for(j = 0 ; j < NOMBRE_BLOCS_HAUTEUR; j++)
        {
            Rect_dest.x = i * LARGEUR_TILE;
            Rect_dest.y = j * HAUTEUR_TILE;
            Rect_source.x = (table[j][i] - '0') * LARGEUR_TILE;
            Rect_source.y = 0;
            SDL_RenderCopy(pRenderer, textuTil, &Rect_source, &Rect_dest);
        }
    }
}
