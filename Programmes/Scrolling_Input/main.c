#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#define LARGEUR_TILE 24  // hauteur et largeur des tiles.
#define HAUTEUR_TILE 16

#define NOMBRE_BLOCS_LARGEUR 15  // nombre a afficher en x et y
#define NOMBRE_BLOCS_HAUTEUR 13

const int FPS=60;

void Afficher(SDL_Renderer* pRenderer, SDL_Texture* textuTil, char** table, int nombre_blocs_largeur, int nombre_blocs_hauteur,int xBase, int yBase);



int main(int argc, char *argv[]) {
    SDL_Window *pWindow=NULL;           //Pointeur sur la fen�tre, ref d'un window win32
    SDL_Renderer *pRenderer=NULL;       //Pointeur sur le Rendus, ref rendu encapsul� dans window

    //Requis pour utiliser la SDL
    if(SDL_Init(SDL_INIT_EVERYTHING)>=0) {   //INIT_EVERYTHING = initialise l'audio, la vid�o, les contr�les,... cf; SDL wiki/API by name/SDL_Init
        pWindow = SDL_CreateWindow("TILESET_TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_TILE*NOMBRE_BLOCS_LARGEUR, HAUTEUR_TILE*NOMBRE_BLOCS_HAUTEUR, SDL_WINDOW_SHOWN);

        //si succ�s, cr�er window et renderer
        if(pWindow!=NULL) {
            pRenderer=SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_PRESENTVSYNC);
            SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

            //------------------------------------------------------------------------------------------------//
            //Tilemapping

            char* table[] = {
                "000000000000000000000000000000",
                "000000000000000000000000000000",
                "000000000000000000000000100000",
                "000000000000000000000000000000",
                "000000000000000000000000000000",
                "000000022122200000000000000000",
                "000000000000000000000021212000",
                "003400000000000000000000000000",
                "005600000000000000000000000000",
                "005600000000000003400000000000",
                "005600000000000005600000000000",
                "777777777777777777777777777777",
                "777777777777777777777777777777",
                "002000000000000000000000000000",
                "000000000000000000000020000000",
                "000002000000000000000000000000",
                "000000000000000000002000000000"
            };

            unsigned long int nTempsActuel=0;
            unsigned long int nTempsPrecedent=0;
            int nDeltaTime = div(1000,FPS).quot;
            int PixelX = 0;
            int PixelY = 0;
            int sens = 1;
            int hauteurMax = (sizeof(table) / sizeof(table[1]) / sizeof(char) - NOMBRE_BLOCS_HAUTEUR) * HAUTEUR_TILE - 1;
            printf("%d",hauteurMax);

            SDL_Surface *tileset = NULL;
            SDL_Texture *textuTil = NULL;
            SDL_Event event;
            int continuer = 1, tempsPrecedent = 0, tempsActuel = 0;
            int statut = EXIT_FAILURE;

            tileset = IMG_Load("assets/tileset1.png");
            if (tileset == NULL) {
                fprintf(stderr, "Erreur chargement image droite : %s", SDL_GetError());
            }

            textuTil = SDL_CreateTextureFromSurface(pRenderer, tileset);
            if (textuTil == NULL) {
                fprintf(stderr, "Erreur SDL_CreateTexturetil : %s", SDL_GetError());
            }
            SDL_FreeSurface(tileset);

            Afficher(pRenderer, textuTil, table, NOMBRE_BLOCS_LARGEUR, NOMBRE_BLOCS_HAUTEUR,0,0);

            while(continuer) {
                SDL_PollEvent(&event);
                switch(event.type) {
                    case SDL_QUIT:
                        continuer = 0;
                        break;

                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym) {
                            case SDLK_ESCAPE:
                                continuer = 0;
                                break;

                            //Gestion des touches
                            case SDLK_d:
                            case SDLK_RIGHT:
                                if(PixelX < ((strlen(table[0]) - NOMBRE_BLOCS_LARGEUR) * LARGEUR_TILE)) //Si l'utilisateur appuie sur la touche d ET qu'il n'arrive pas en bout de tableau
                                    PixelX = PixelX + 1; //Alors il avance d'un block vers la droite
                                break;

                            case SDLK_q:
                            case SDLK_LEFT:
                                if(PixelX > 0) //Si l'utilisateur appuie sur la touche q ET qu'il n'arrive pas en bout de tableau
                                    PixelX = PixelX - 1; //Alors il avance d'un block vers la gauche
                                break;

                            case SDLK_s:
                            case SDLK_DOWN:
                                if(PixelY < hauteurMax) {//Si l'utilisateur appuie sur la touche s ET qu'il n'arrive pas en bout de tableau
                                    PixelY = PixelY + 1; //Alors il avance d'un block vers le bas
                                }
                                break;

                            case SDLK_z:
                            case SDLK_UP:
                                if(PixelY > 0) //Si l'utilisateur appuie sur la touche z ET qu'il n'arrive pas en bout de tableau
                                    PixelY = PixelY - 1; //Alors il avance d'un block vers le haut
                                break;
                        }
                        break;
                }


                nTempsActuel = SDL_GetTicks();
                if (nTempsActuel > nTempsPrecedent + nDeltaTime) {          //On effectue l'affichage � chaque frame.

                    if((PixelX >= ((strlen(table[1]) - NOMBRE_BLOCS_LARGEUR) * LARGEUR_TILE)) || (PixelX <= 0)) {
                        sens = -sens;
                    }

                    Afficher(pRenderer, textuTil, table, NOMBRE_BLOCS_LARGEUR, NOMBRE_BLOCS_HAUTEUR,PixelX,PixelY);
                    nTempsPrecedent = nTempsActuel;

                }

                SDL_RenderPresent(pRenderer);
            }

            //------------------------------------------------------------------------------------------------//

            //SDL_Delay(10000);

            SDL_DestroyTexture(textuTil);
            SDL_DestroyRenderer(pRenderer); //On supprime tout ce qui � �t� cr�er
            SDL_DestroyWindow(pWindow);
            SDL_Quit();
        }

    }

    return 0;
}


void Afficher(SDL_Renderer* pRenderer, SDL_Texture* textuTil, char** table, int nombre_blocs_largeur, int nombre_blocs_hauteur,int xBase, int yBase) {

    SDL_RenderClear(pRenderer);
    int i, j;
    int BlocX, BlocY;
    SDL_Rect Rect_dest;
    SDL_Rect Rect_source;
    BlocX = xBase / LARGEUR_TILE;
    BlocY = yBase / HAUTEUR_TILE;

    Rect_source.w = LARGEUR_TILE;
    Rect_dest.w = LARGEUR_TILE;
    Rect_source.h = HAUTEUR_TILE;
    Rect_dest.h = HAUTEUR_TILE;
    for(i = BlocX ; i < NOMBRE_BLOCS_LARGEUR + (BlocX+1); i++) {
        for(j = BlocY ; j < NOMBRE_BLOCS_HAUTEUR + (BlocY+1); j++) {
            Rect_dest.x = i * LARGEUR_TILE - xBase;
            Rect_dest.y = j * HAUTEUR_TILE - yBase;
            Rect_source.x = (table[j][i] - '0') * LARGEUR_TILE;
            Rect_source.y = 0;
            SDL_RenderCopy(pRenderer, textuTil, &Rect_source, &Rect_dest);
        }
    }
}
