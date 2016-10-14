#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

void pause();
int fonctionx(int n);
int fonctiony(int n);


int main(int argc, char *argv[])
{

    int casedepart, d =1, x=0, y=0;



    int tableau[50] = {0,1,0,1}, n =0, continuer = 1;

    SDL_Surface *ecran = NULL, *imageDeFond = NULL, *dame = NULL, *selection=NULL;
    SDL_Rect positionFond, positionDame,positionselection;
    SDL_Event event ;
    positionFond.x = 0;
    positionFond.y = 0;
    positionselection.x =0;
    positionselection.y =0;
    do
    {
    SDL_WaitEvent(&event);
    switch(event.type)
{

    case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
    {
        case SDLK_UP: // Flèche haut
            positionselection.y-=60;
            break;
        case SDLK_DOWN: // Flèche bas
            positionselection.y+=60;
            break;
        case SDLK_RIGHT: // Flèche droite
            positionselection.x+=80;
            break;
        case SDLK_LEFT: // Flèche gauche
            positionselection.x-=80;
            break;
        case SDLK_KP_ENTER:
            d=0;
            positionselection.x = x;
            positionselection.y = y;
            break;
    }
        break;
}




    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Les dames", NULL);

    /* Chargement du damier */
    imageDeFond = SDL_LoadBMP("Sans titre.bmp");                // definition du damier
    /* On blitte par-dessus le damier qu'on a crée */
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);

    dame = SDL_LoadBMP("dame.bmp");
     for (n = 0; n <= 6; n++)                                   // definition de chaque pièce sur le damier
        {
            if (tableau [n] == 1)
            {
            positionDame.x = fonctionx(n),
            positionDame.y = fonctiony(n),
            SDL_BlitSurface(dame, NULL, ecran, &positionDame);
            }
        }

    selection = SDL_LoadBMP("Selection.bmp");
    SDL_SetColorKey(selection, SDL_SRCCOLORKEY, SDL_MapRGB(selection->format, 0,
    0, 255));
    /* Transparence Alpha moyenne (128) pour le selectionnement: */
    SDL_SetAlpha(selection, SDL_SRCALPHA, 128);
    SDL_BlitSurface(selection, NULL, ecran, &positionselection);

    SDL_Flip(ecran);
    SDL_FreeSurface(selection);
    SDL_FreeSurface(imageDeFond); /* On libère la surface */
    SDL_FreeSurface(dame);
    }
    while (d);

    SDL_Quit();



    return EXIT_SUCCESS;
}
int reverse_Fonction (int )

int fonctiony(int n)
{
    int a;
    a = (n/5) ;
    a = a*60 ;
    return a;
}

int fonctionx(int n)
{
    int a,b;
    a = n/5;
    b = (n%5)*2;
    if (a%2 ==0)
            b +=1;
    return b*80;
}


void pause()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT)
        {
                continuer = 0;

        }
    }
}
