#include "voidCercles.h"

//----------------------------------------------------------------------------//
//Dessin d'un cercle vide

int cercleVide(SDL_Renderer *pRenderer, int xCircle, int yCircle, int radiusCircle, int nbPoints) {
	int xPoint, yPoint, xPointCircle, yPointCircle;
	int i;
	double angleActu;

	SDL_SetRenderDrawColor(pRenderer, 255, 0, 255, 255);

	for(i=0; i < nbPoints; i++) {
        angleActu = (double)i / (double)nbPoints * 2 * M_PI;

        xPointCircle = (int)(radiusCircle * cos(angleActu));
		yPointCircle = (int)(radiusCircle * sin(angleActu));

		xPoint = xCircle + xPointCircle;
		yPoint = yCircle + yPointCircle;

        SDL_RenderDrawPoint(pRenderer, xPoint, yPoint);
	}

	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);

	SDL_RenderPresent(pRenderer);

	return(pRenderer);

}


int cerclePlein(SDL_Renderer *pRenderer, int xCircle, int yCircle, int radiusCircle, int nbPoints) {
	int xPoint, yPoint, xPointCircle, yPointCircle;
	int i;
	int xTab, yTab;
	double angleActu;

	int tailleTableau = radiusCircle*2;

	int TPoints[tailleTableau][tailleTableau];

	for(xTab=0; xTab<tailleTableau; xTab++) {
        for(yTab=0; yTab<tailleTableau; yTab++) {
            TPoints[xTab][yTab] = 0;
        }
	}

	SDL_SetRenderDrawColor(pRenderer, 255, 0, 255, 255);

	for(i=0; i < nbPoints; i++) {

        angleActu = (double)i / (double)nbPoints * 2 * M_PI;

		xPointCircle = (int)(radiusCircle * cos(angleActu));
		yPointCircle = (int)(radiusCircle * sin(angleActu));

		xPoint = xCircle + xPointCircle;
		yPoint = yCircle + yPointCircle;

        SDL_RenderDrawPoint(pRenderer, xPoint, yPoint);

        if(angleActu < (M_PI / 2)) {
            for(xTab=radiusCircle; xTab <= radiusCircle+xPointCircle; xTab++) {
                for(yTab=radiusCircle; yTab <= radiusCircle+yPointCircle; yTab++) {
                    TPoints[xTab][yTab] = 1;
                    TPoints[radiusCircle*2-xTab][yTab] = 1;
                    TPoints[xTab][radiusCircle*2-yTab] = 1;
                    TPoints[radiusCircle*2-xTab][radiusCircle*2-yTab] = 1;
                }
            }
        }
	}


	for(xTab=0; xTab<tailleTableau; xTab++) {
        for(yTab=0; yTab<tailleTableau; yTab++) {
            if(TPoints[xTab][yTab] == 1) {
                xPoint = xCircle + xTab - radiusCircle;
                yPoint = yCircle + yTab - radiusCircle;
                SDL_RenderDrawPoint(pRenderer, xPoint, yPoint);
            }
        }
	}

	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);

	SDL_RenderPresent(pRenderer);

	return(pRenderer);

}
