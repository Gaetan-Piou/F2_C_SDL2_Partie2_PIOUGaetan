#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "voidCarrés.h"

int main(int argc, char *argv[])    //arguments obligatoire pour compiler en SDL
{

    SDL_Window *pWindow=NULL;           //Pointeur sur la fenêtre, ref d'un window win32
    SDL_Renderer *pRenderer=NULL;       //Pointeur sur le Rendus, ref rendu encapsulé dans window
    SDL_Texture *pTexture=NULL;         //Pointeur sur la texture, qui possède l'image à afficher, ref image/texture/materiel


    //Requis pour utiliser la SDL
    if(SDL_Init(SDL_INIT_EVERYTHING)>=0)    //INIT_EVERYTHING = initialise l'audio, la vidéo, les contrôles,... cf; SDL wiki/API by name/SDL_Init
    {
        //succès, créer window
        pWindow=SDL_CreateWindow("SDL_Application",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 780, SDL_WINDOW_SHOWN);//x,y,width,eight

        //si succès, créer window et renderer
        if(pWindow!=NULL)
        {
            pRenderer=SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_PRESENTVSYNC);

            SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderPresent(pRenderer);   //afficher le Renderer

//

            SDL_Delay(2000);

            SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(pRenderer);
            SDL_RenderPresent(pRenderer);


            //----------------------------------------------------------------------------//
            //Création d'une texture à partir d'un PNG
            SDL_SetRenderTarget(pRenderer, NULL); //redéfinitions de la zone de travail
            SDL_Surface* pPng = IMG_Load("assets/mule.png"); //On charge la surface
            SDL_Texture* Image = SDL_CreateTextureFromSurface(pRenderer,pPng); //On utilise la surface pour creer la texture

            SDL_FreeSurface(pPng);

            //On verifie si la texture est bien creee
            if (Image == NULL)
              printf("erreur");

            SDL_Rect myRect;
            myRect.x = 0;
            myRect.y = 0;
            SDL_QueryTexture(Image, NULL, NULL, &myRect.w, &myRect.h);//Récupère le format de l'image

            SDL_RenderCopy(pRenderer, Image, NULL, &myRect);
            SDL_RenderPresent(pRenderer);
            //----------------------------------------------------------------------------//



            //----------------------------------------------------------------------------//
            //Création d'un tileset
            SDL_SetRenderTarget(pRenderer, NULL);

            SDL_Surface* spritePng = IMG_Load("assets/tileset_sprite.png");
            SDL_Texture* spriteImage = SDL_CreateTextureFromSurface(pRenderer,spritePng);

            SDL_FreeSurface(spritePng);


            int quit = 0;                                                                   //Mise en place d'une condition de sortie via un pseudo bool
            SDL_Event event;

            SDL_Rect myRectSource;                                                        //Définition d'une zone d'affichage
            myRectSource.x = 0;
            myRectSource.y = 0;
            SDL_QueryTexture(spriteImage, NULL, NULL, &myRectSource.w, &myRectSource.h);  //Appel de la texture créer à partir de l'image
            myRectSource.w = myRectSource.w;          //Division des dimensions pour adapter à la taille de chaque images
            myRectSource.h = myRectSource.h/4;

            printf("%d,%d\n",myRectSource.w,myRectSource.h);

           while (!quit)
            {
                Uint32 ticks = SDL_GetTicks();
                Uint32 sprite = (ticks / 100) % 4;

                SDL_Rect srcrect = { 0, sprite * myRectSource.h, myRectSource.w,  myRectSource.h };     //Mise en place des rects de source et de réception
                SDL_Rect dstrect = { 200, 150, myRectSource.w,  myRectSource.h };

                SDL_PollEvent(&event);

                switch (event.type)
                {
                    case SDL_MOUSEBUTTONDOWN :
                        quit = 1;
                        break;
                }

                SDL_RenderClear(pRenderer);
                SDL_RenderCopy(pRenderer, Image, NULL, &myRect);
                SDL_RenderCopy(pRenderer, spriteImage, &srcrect, &dstrect);
                SDL_RenderPresent(pRenderer);

            }

            SDL_DestroyTexture(spriteImage);
            SDL_DestroyTexture(Image);
            SDL_DestroyRenderer(pRenderer); //On supprime tout ce qui à été cree
            SDL_DestroyWindow(pWindow);
            SDL_Quit();

        }
    }



    return 0;
}


