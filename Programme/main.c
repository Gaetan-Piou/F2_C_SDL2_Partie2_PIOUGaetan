#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
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
        pWindow=SDL_CreateWindow("SDL_Application",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 780, SDL_WINDOW_SHOWN);//x,y,width,eight

        //si succès, créer window et renderer
        if(pWindow!=NULL)
        {
            pRenderer=SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_PRESENTVSYNC);
           /* }
            else
            {*/

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
            SDL_Surface* pPng = IMG_Load("mule.png");
            SDL_Texture* Image = SDL_CreateTextureFromSurface(pRenderer,pPng);

            SDL_FreeSurface(pPng);

            if (Image == NULL)
              printf("erreur");

            SDL_Rect myRect;
            myRect.x = 0;
            myRect.y = 0;
            SDL_QueryTexture(Image, NULL, NULL, &myRect.w, &myRect.h);//Récupère le format de l'image

            SDL_RenderCopy(pRenderer, Image, NULL, &myRect);
            SDL_RenderPresent(pRenderer);
            //----------------------------------------------------------------------------//


            SDL_Delay(10000);

            SDL_DestroyRenderer(pRenderer); //On supprime tout ce qui à été créer
            SDL_DestroyWindow(pWindow);
            SDL_Quit();

        }
    }



    return 0;
}


