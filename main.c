#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

int fonctionx(int g);
int fonctiony(int c);
int fonctioninverse(int x, int y,int cases);
void avancePion(int *pointeurcasedepart, int *pointeurcasearrivee, int *tableau, int*pointeursurchoix);
void saut(int *pointeurcasedepart, int *pointeurcasearrivee, int *tableau, int*pointeursurchoix);


int main(int argc, char *argv[])
{
    int tableau[50] = {1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 0,0,0,0,0, 0,0,0,0,0, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2};
    //int tableau[50] = {1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 0,0,0,0,0, 0,0,0,0,1, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2}; //saut droit
    //int tableau[50] = {1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,1,0, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2};  //saut gauche
    //int tableau[50] = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,1,1,0,0, 0,0,0,0,0, 0,0,0,1,0, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2}; //double saut
    //int tableau[50] = {1,0,0,1,1, 1,1,2,1,1, 1,1,1,1,1, 1,1,1,1,1, 0,0,0,0,0, 0,0,0,0,0, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2};  //devenir une reine
    //int tableau[50] = {1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 0,0,0,0,0, 0,0,0,0,0, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2};    //deplacement reine
    //int tableau[50] = {1,1,1,1,1, 0,0,0,0,0, 1,1,1,1,1, 1,1,1,1,1, 0,0,0,0,0, 0,0,0,0,0, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2};   //deplacement droite et ordre de scan de lordinateur
    //int tableau[50] = {1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 0,1,1,1,1, 0,0,0,0,0, 0,0,0,0,0, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2};   //deplacement gauche de lordinateur
    //int tableau[50] = {1,1,1,1,1, 1,0,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 0,0,0,0,0, 0,0,0,2,0, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2};   //saut droite de lordinateur
    //int tableau[50] = {1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 0,0,2,0,0, 0,0,0,2,0, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2};   //saut gauche de lordinateur
    //int tableau[50] = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 1,0,0,0,0, 0,2,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,2,0,0,0, 0,0,0,0,0};   //double saut normal ordinateur
    //int tableau[50] = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 1,0,0,0,0, 0,2,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 2,0,0,0,0, 0,0,0,0,0};   //double saut deux sens ordinateur

    int casedepart = 0,casearrivee =0, d =0,a = 1,continuer = 1, choix=2; // joueur commence la partie
    int compteurjoueur = 20, compteurordinateur = 20, saute=0;

   do
    {
        d=1, a=1, continuer=1, casedepart=0, casearrivee=0;


        // initialisation des valeurs (celle qui vont être réutiliser, mais qui ne peuvent pas être static
        SDL_Surface *ecran = NULL, *imageDeFond = NULL, *dame = NULL, *selection=NULL, *dame2, *Reine, *Reine2;
        SDL_Rect positionFond, positionDame, positionselection, positionselection2, positionDame2, positionReine, positionReine2; // définition des variables SDL
        SDL_Event event;

        if (choix ==2)
        {
            positionselection.x =0;
            positionselection.y =540;
            positionselection2.x = 0;
            positionselection2.y = 540;
        }
        positionFond.x = 0;
        positionFond.y = 0;

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxx chargement du damier apres chaque tour xxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

        do
        {
            int x=0, y=0, v=0;
            SDL_Init(SDL_INIT_VIDEO);
            ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
            SDL_WM_SetCaption("Les dames", NULL);

            // Chargement du damier
            imageDeFond = SDL_LoadBMP("Sans titre.bmp");// definition du damier
            // On blitte par-dessus le damier qu'on a crée
            SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);

            // change les pions qui sont qrrives de l'autre cote en reine
            for(v=0;v<5;v++)
            {
                if(tableau[v]==2)
                {
                    tableau[v]=4; // alors change en reine
                }
            }

            for(v=45;v<50;v++)
            {
                if(tableau[v]==1)
                {
                    tableau[v]=3; // alors change en reine
                }
            }
            dame = SDL_LoadBMP("dame.bmp");
            for (v=0;v<50;v++) // definition de chaque pièce sur le damier
            {
                if (tableau[v] == 1)
                {
                    positionDame.x = fonctionx(v),
                    positionDame.y = fonctiony(v),
                    SDL_BlitSurface(dame, NULL, ecran, &positionDame);
                }
            }

            dame2 = SDL_LoadBMP("dame type 2.bmp");
            for (v=0;v<50;v++) // definition de chaque pièce de l'adversaire sur le damier
            {
                if (tableau[v] == 2)
                {
                    positionDame2.x = fonctionx(v),
                    positionDame2.y = fonctiony(v),
                    SDL_BlitSurface(dame2, NULL, ecran, &positionDame2);
                }
            }

            Reine = SDL_LoadBMP("reine.bmp");
            for (v=0;v<50;v++) // definition de chaque pièce de l'adversaire sur le damier
            {
                if (tableau[v] == 3)
                {
                    positionReine.x = fonctionx(v),
                    positionReine.y = fonctiony(v),
                    SDL_BlitSurface(Reine, NULL, ecran, &positionReine);
                }
            }

            Reine2 = SDL_LoadBMP("reine type 2.bmp");
            for (v=0;v<50;v++) // definition de chaque pièce de l'adversaire sur le damier
            {
                if (tableau [v] == 4)
                {
                    positionReine2.x = fonctionx(v),
                    positionReine2.y = fonctiony(v),
                    SDL_BlitSurface(Reine2, NULL, ecran, &positionReine2);
                }
            }

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx tour du joueur xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

            if (choix == 2)
            {

                //xxxxxxxxxxxxxxxxxxxxxxxxxxxx Premiere selection xxxxxxxxxxxxxxxxxxxxxxxxxxxx
                selection = SDL_LoadBMP("Selection.bmp");
                if(a==1)
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
                                case SDLK_SPACE:
                                    a=0;
                                    continuer = 0;
                                    x = positionselection.x;
                                    y = positionselection.y;
                                    casedepart = fonctioninverse(x,y,casedepart);
                                    break;
                                case SDLK_a:
                                    d=0;
                                    compteurordinateur =0;
                                    a=0;
                                    choix =3;
                                default:
                                    break;
                            }

                        default:
                            break;
                    }
                }

                SDL_SetColorKey(selection, SDL_SRCCOLORKEY, SDL_MapRGB(selection->format, 0, 0, 255));
                /* Transparence Alpha moyenne (128) pour le selectionnement: */
                SDL_SetAlpha(selection, SDL_SRCALPHA, 128);
                SDL_BlitSurface(selection, NULL, ecran, &positionselection);

                //xxxxxxxxxxxxxxxxxxxxxxxxxxxx deuxieme selection xxxxxxxxxxxxxxxxxxxxxxxxxxxx
                // il serait bien de redemarrer de la premiere selection ???
                selection = SDL_LoadBMP("selection2.bmp");
                SDL_SetColorKey(selection, SDL_SRCCOLORKEY, SDL_MapRGB(selection->format, 0, 0, 255));

                if(continuer == 0)
                {
                    SDL_WaitEvent(&event);

                    switch(event.type)
                    {
                        case SDL_KEYDOWN:
                            switch(event.key.keysym.sym)
                            {
                                case SDLK_UP: // Flèche haut
                                    positionselection2.y-=60;
                                    break;
                                case SDLK_DOWN: // Flèche bas
                                    positionselection2.y+=60;
                                    break;
                                case SDLK_RIGHT: // Flèche droite
                                        positionselection2.x+=80;
                                        break;
                                case SDLK_LEFT: // Flèche gauche
                                    positionselection2.x-=80;
                                    break;
                                case SDLK_SPACE:
                                    continuer=1;
                                    d = 0;
                                    x = positionselection2.x ;
                                    y = positionselection2.y ;
                                    casearrivee = fonctioninverse(x,y,casearrivee);
                                    break;
                                default:
                                    break;
                            }

                        default:
                            break;
                    }
                }

                /* Transparence Alpha moyenne (128) pour le selectionnement: */
                SDL_SetAlpha(selection, SDL_SRCALPHA, 128);
                SDL_BlitSurface(selection, NULL, ecran, &positionselection2);
                SDL_Flip(ecran);

                //xxxxxxxxxxxxxxxxxxxxxxxxxxxx action du pion xxxxxxxxxxxxxxxxxxxxxxxxxxxx
                avancePion(&casedepart,&casearrivee, tableau, &choix); // ou bien on avance
                if(choix ==2) // ou bien on saute
                {
                    saut(&casedepart,&casearrivee, tableau, &choix);
                    compteurordinateur--; // decompte un pion de l'ordinateur

                if (choix == 1)
                {
                    if((tableau[casearrivee-9]==0&&(tableau[(casearrivee*2 - 9)/2] ==1) ) )
                    {
                        choix =2 ;
                        casedepart =casearrivee;
                    }
                    else if(tableau[casearrivee-11] ==0 &&tableau[(casearrivee*2 -11)/2] ==1)
                    {
                        choix =2 ;
                        casedepart = casearrivee;
                    }
                }
                }
            }
        }while(d); //

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx c'est au tour de l'ordinateur xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

        if (choix == 1)
        {
            saute=0;
            casedepart=0;
            while(casedepart<50 && choix==1)
            // Scanner le damier pour trouver le premier pion ou reine qui peut sauter
            // Si on en trouve un alors on saute et on regarde si il peut sauter encore
            // une fois que ce pion ne peut plus sauter alors on passe au tour du joueur
            // si on trouve pas d'opportunite pour sauter alors on cherche le pion le moins
            // avance et on le fait avancer pour consolider la defense
            // sinon l'ordinateur passe son tour
            {
                if((tableau[casedepart] == 1) || (tableau[casedepart] == 3)) // si pion ou reine ordi
                {
                    switch(casedepart)
                    {
                        case 5: case 15: case 25: case 35:
                        {
                            if(tableau[casedepart+5] == 2 && tableau[casedepart+11] == 0)
                            {
                                casearrivee=casedepart+11; // alors sauter le pion de gauche
                                saut(&casedepart,&casearrivee, tableau, &choix); // case de depart et d'arrivee
                                compteurjoueur--;
                                if(saute==1) {choix=2;} // doublesaut termine => tour du joueur
                                else {saute=1;} // flag pour indiquer que l'on a saute au moins une fois
                                break;
                            }
                            if(saute==1) {choix=2;}
                            break;
                        }

                        case 0: case 10: case 20: case 30:
                        {
                            if(tableau[casedepart+6] == 2 && tableau[casedepart+11] == 0)
                            {
                                casearrivee=casedepart+11; // alors sauter le pion de gauche
                                saut(&casedepart,&casearrivee, tableau, &choix); // case de depart et d'arrivee
                                compteurjoueur--; // decompte un pion
                                if(saute==1) {choix=2;} // doublesaut termine => tour du joueur
                                else {saute=1;} // flag pour indiquer que l'on a saute au moins une fois
                                break;
                            }
                            if(saute==1) {choix=2;}
                            break;
                        }

                        case 1: case 11: case 21: case 31:
                        case 2: case 12: case 22: case 32:
                        case 3: case 13: case 23: case 33:
                        {
                            if(tableau[casedepart+6] == 2 && tableau[casedepart+11] == 0)
                            {
                                casearrivee=casedepart+11; // alors sauter le pion de gauche
                                saut(&casedepart,&casearrivee, tableau, &choix); // case de depart et d'arrivee
                                compteurjoueur--; // decompte un pion
                                if(saute==1) {choix=2;} // doublesaut termine => tour du joueur
                                else {saute=1;} // flag pour indiquer que l'on a saute au moins une fois
                                break;
                            }
                            else if(tableau[casedepart+5] == 2 && tableau[casedepart+9] == 0)
                            {
                                casearrivee=casedepart+9; // alors sauter le pion de droite
                                saut(&casedepart,&casearrivee, tableau, &choix); // case de depart et d'arrivee
                                compteurjoueur--; // decompte un pion
                                if(saute==1) {choix=2;} // doublesaut termine => tour du joueur
                                else {saute=1;} // flag pour indiquer que l'on a saute au moins une fois
                                break;
                            }
                            if(saute==1) {choix=2;}
                            break;
                        }

                        case 6: case 16: case 26: case 36:
                        case 7: case 17: case 27: case 37:
                        case 8: case 18: case 28: case 38:
                        {
                            if(tableau[casedepart+5] == 2 && tableau[casedepart+11] == 0)
                            {
                                casearrivee=casedepart+11;// alors sauter le pion de gauche
                                saut(&casedepart,&casearrivee, tableau, &choix); // case de depart et d'arrivee
                                compteurjoueur--; // decompte un pion
                                if(saute==1) {choix=2;} // doublesaut termine => tour du joueur
                                else {saute=1;} // flag pour indiquer que l'on a saute au moins une fois
                                break;
                            }
                            else if(tableau[casedepart+4] == 2 && tableau[casedepart+9] == 0)
                            {
                                casearrivee=casedepart+9;// alors sauter le pion de droite
                                saut(&casedepart,&casearrivee, tableau, &choix); // case de depart et d'arrivee
                                compteurjoueur--; // decompte un pion
                                if(saute==1){choix=2;} // doublesaut termine => tour du joueur
                                else {saute=1;} // flag pour indiquer que l'on a saute au moins une fois
                                break;
                            }
                            if(saute==1) {choix=2;}
                            break;
                        }

                        case 9: case 19: case 29: case 39:
                        {
                            if(tableau[casedepart+4] == 2 && tableau[casedepart+9] == 0)
                            {
                                casearrivee=casedepart+9;// alors sauter le pion de droite
                                saut(&casedepart,&casearrivee, tableau, &choix); // case de depart et d'arrivee
                                compteurjoueur--; // decompte un pion
                                if(saute==1) {choix=2;} // doublesaut termine => tour du joueur
                                else {saute=1;} // flag pour indiquer que l'on a saute au moins une fois
                                break;
                            }
                            if(saute==1) {choix=2;}
                            break;
                        }

                        case 4: case 14: case 24: case 34:
                        {
                            if(tableau[casedepart+5] == 2 && tableau[casedepart+9] == 0)
                            {
                                casearrivee=casedepart+9; // alors sauter le pion de droite
                                saut(&casedepart,&casearrivee, tableau, &choix); // case de depart et d'arrivee
                                compteurjoueur--; // decompte un pion
                                if(saute==1) {choix=2;} // doublesaut termine => tour du joueur
                                else {saute=1;} // flag pour indiquer que l'on a saute au moins une fois
                                break;
                            }
                            if(saute==1) {choix=2;}
                            break;
                        }

                        default:
                            break;
                    }
                }
                if(saute==1) {casedepart = casearrivee;} // gestion du double saut
                else {casedepart++;}
            }

            // si on a pas saute alors on peut peut-etre avancer
            casedepart=0; // retour case depart
            while(casedepart<50 && choix==1)
            {
                if((tableau[casedepart] == 1) || (tableau[casedepart] == 3)) // si pion ou reine ordi
                {
                    switch(casedepart)
                    {
                        case 5: case 15: case 25: case 35:
                        {
                            if(tableau[casedepart+5] == 0)
                            {
                                casearrivee=casedepart+5; // alors avancer le pion a gauche
                                avancePion(&casedepart,&casearrivee,tableau,&choix); // case de depart et d'arrivee
                                choix=2;
                            }
                            break;
                        }

                        case 0: case 10: case 20: case 30: case 40:
                        case 1: case 11: case 21: case 31: case 41:
                        case 2: case 12: case 22: case 32: case 42:
                        case 3: case 13: case 23: case 33: case 43:
                        {
                            if(tableau[casedepart+6] == 0)
                            {
                                casearrivee=casedepart+6; // alors avancer le pion a gauche
                                avancePion(&casedepart,&casearrivee,tableau,&choix); // case de depart et d'arrivee
                                choix=2;
                            }
                            else if(tableau[casedepart+5]==0)
                            {
                                casearrivee=casedepart+5;// alors avancer le pion a droite
                                avancePion(&casedepart,&casearrivee,tableau,&choix); // case de depart et d'arrivee
                                choix=2;
                            }
                            break;
                        }

                        case 6: case 16: case 26: case 36:
                        case 7: case 17: case 27: case 37:
                        case 8: case 18: case 28: case 38:
                        case 9: case 19: case 29: case 39:
                        {
                            if(tableau[casedepart+5] == 0)
                            {
                                casearrivee=casedepart+5;// alors avancer le pion a gauche
                                avancePion(&casedepart,&casearrivee,tableau,&choix); // case de depart et d'arrivee
                                choix=2;
                            }
                            else if(tableau[casedepart+4]==0)
                            {
                                casearrivee=casedepart+4; // alors avancer le pion a droite
                                avancePion(&casedepart,&casearrivee,tableau,&choix); // case de depart et d'arrivee
                                choix=2;
                            }
                            break;
                        }

                        case 4: case 14: case 24: case 34:
                        {
                            if(tableau[casedepart+5] == 0)
                            {
                                casearrivee=casedepart+5;// alors avancer le pion a droite
                                avancePion(&casedepart,&casearrivee,tableau,&choix); // case de depart et d'arrivee
                                choix=2;
                            }
                            break;
                        }

                        default:
                            break;
                    }
                }
                casedepart++;
            }
        }


        SDL_FreeSurface(imageDeFond); /* On libère la surface */
        SDL_FreeSurface(dame);
        SDL_FreeSurface(dame2);
        SDL_FreeSurface(Reine);
        SDL_FreeSurface(Reine2);

    } while(compteurjoueur && compteurordinateur);

    SDL_Quit();
    return 0;
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx Fonctions xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// add comments
int fonctiony(int c)
{
    int f;
    f = (c/5) ; //c est le numéro de la case. 5 cases par ligne donc on divise par 5. Si la case est sur la 1ère ligne a=0. Si la case est sur 2ème ligne a=1, etc.
    f = f*60 ;  //f aura la même valeur pour toutes les cases d'une ligne
    return f;
}

// add comments
int fonctionx(int g)
{
    int e,r;
    e = g/5;     // si la case est paire ou impaire (si au début du tableau il y a une case noir
    r = (g%5)*2; //
    if (e%2 ==0) //
            r +=1;
    return r*80; //case 1: 80 - case 2: 240 - case 3: 400 - etc... (car tableau 800*600 avec 10 cases dans chaque sens)
}

// add comments
int fonctioninverse(int x, int y, int cases)
{
    int z = 0;
    cases +=(5*y/60);
    if ((y/60)%2==1)
    {
        z= x/160; //x: 80-160-240 (toutes les cases, pas que noires) etc.. donc première case noire: x=1, 2ème c.n. x=3, 3ème case noire: x=5...
        cases +=z ; //donc 1ère casenoire=0, 2ème=1, 3ème=2, etc..
    }
    if ((y/60)%2==0)
    {
        z=x/160;
        cases +=z;
    }
    return cases;
}

// fonction pour faire avancer un pion ou une reine. Attention il faut encore programmer pour la reine
void avancePion(int *pointeurcasedepart, int *pointeurcasearrivee, int *tableau, int*pointeursurchoix)
{
    int typedepion = tableau[*pointeurcasedepart]; // memorise si c'est un pion ou une reine

    // ordinateur
    if (*pointeursurchoix ==1)
    {

        if((*pointeurcasearrivee/5)%2 ==0)  //ligne impaire
        {
            // peu importe si c'est un pion ou une reine, les 2 peuvent avancer
            if((*pointeurcasedepart+4 == *pointeurcasearrivee) || (*pointeurcasedepart+5 == *pointeurcasearrivee))
            {
                tableau[*pointeurcasedepart] =  0 ;
                tableau[*pointeurcasearrivee] = typedepion;
                *pointeursurchoix = 2; // tour du joueur
            }

            // par contre seule une reine peut reculer
            else if((*pointeurcasedepart-5 == *pointeurcasearrivee) || (*pointeurcasedepart-6 == *pointeurcasearrivee))
            {
                if(typedepion == 3) // verifie qu'il s'agit bien d'une reine
                {
                    tableau[*pointeurcasedepart] =  0 ;
                    tableau[*pointeurcasearrivee] = typedepion;
                    *pointeursurchoix = 2; // tour du joueur
                }
            }
        }
        else if((*pointeurcasearrivee/5)%2 ==1)   //ligne paire
        {
            // peut importe si c'est un pion ou une reine, les 2 peuvent avancer
            if((*pointeurcasedepart+5 == *pointeurcasearrivee) || (*pointeurcasedepart+6 == *pointeurcasearrivee))
            {
                tableau[*pointeurcasedepart] =  0 ;
                tableau[*pointeurcasearrivee] = typedepion;
                *pointeursurchoix = 2;
            }

            // par contre seule une reine peut reculer
            else if((*pointeurcasedepart-4 == *pointeurcasearrivee) || (*pointeurcasedepart-5 == *pointeurcasearrivee))
            {
                if(typedepion == 3) // verifie qu'il s'agit bien d'une reine
                {
                    tableau[*pointeurcasedepart] =  0 ;
                    tableau[*pointeurcasearrivee] = typedepion;
                    *pointeursurchoix = 2;
                }
            }
        }
    }

    // joueur
    else if (*pointeursurchoix == 2)
    {
        if((tableau[*pointeurcasedepart] == 2 || tableau[*pointeurcasedepart] == 4) && tableau[*pointeurcasearrivee]==0 )
        {
            if((*pointeurcasearrivee/5)%2 ==1)   // on doit faire la distinction entre lignes paires et lignes impaires: ici, la ligne est paire
            {
                if((*pointeurcasedepart-4 == *pointeurcasearrivee) || (*pointeurcasedepart-5 == *pointeurcasearrivee))
                {
                    tableau[*pointeurcasedepart] = 0 ;
                    tableau[*pointeurcasearrivee] = typedepion;
                    *pointeursurchoix = 1;
                }

                // par contre seule une reine peut reculer
                else if((*pointeurcasedepart+5 == *pointeurcasearrivee) || (*pointeurcasedepart+6 == *pointeurcasearrivee))
                {
                    if(typedepion == 4) // verifie qu'il s'agit bien d'une reine
                    {
                        tableau[*pointeurcasedepart] =  0 ;
                        tableau[*pointeurcasearrivee] = typedepion;
                        *pointeursurchoix = 1; // tour de l'ordinateur
                    }
                }
            }

            else if((*pointeurcasearrivee/5)%2 ==0)   // on doit faire la distinction entre lignes paires et lignes impaires: ici, la ligne est impaire
            {
                if((*pointeurcasedepart-5 == *pointeurcasearrivee) || (*pointeurcasedepart-6 == *pointeurcasearrivee))
                {
                    tableau[*pointeurcasedepart] = 0 ;
                    tableau[*pointeurcasearrivee] = typedepion;
                    *pointeursurchoix = 1;
                }

                // par contre seule une reine peut reculer
                else if((*pointeurcasedepart+4 == *pointeurcasearrivee) || (*pointeurcasedepart+5 == *pointeurcasearrivee))
                {
                    if(typedepion == 4) // verifie qu'il s'agit bien d'une reine
                    {
                        tableau[*pointeurcasedepart] =  0 ;
                        tableau[*pointeurcasearrivee] = typedepion;
                        *pointeursurchoix = 1; // tour de l'ordinateur
                    }
                }
            }
        }
    }
}

// fonction pour faire sauter un pion ou une reine
void saut(int *pointeurcasedepart, int *pointeurcasearrivee, int *tableau, int*pointeursurchoix)
{
     int typedepion = tableau[*pointeurcasedepart]; // memorise si c'est un pion ou une reine

    if (*pointeursurchoix ==1)   //saut de l'ordinateur
    {
        if((*pointeurcasearrivee/5)%2 ==1)   // on doit faire la distinction entre lignes paires et lignes impaires (pas pour le saut lui-même, mais car tableau [(*pointeurcasearrivee+*pointeurcasedepart)/2] =0;
        //est seulement vrai pour une ligne paire. Il faut tableau [(*pointeurcasearrivee+*pointeurcasedepart)/2+1] =0; pour une ligne impaire.)
        {
            tableau[*pointeurcasedepart] = 0;
            tableau[*pointeurcasearrivee] = typedepion;
            tableau [(*pointeurcasearrivee+*pointeurcasedepart)/2] =0;
        }
        else if((*pointeurcasearrivee/5)%2 ==0)
        {
            tableau[*pointeurcasedepart] = 0;
            tableau[*pointeurcasearrivee] = typedepion;
            tableau [(*pointeurcasearrivee+*pointeurcasedepart)/2+1] =0; // rajoute 1 car le resultat de la division avec int est 'arrondi vers le bas'
        }
    }

    else if (*pointeursurchoix == 2)  //saut du joueur
    {
        if((tableau[*pointeurcasedepart] == 2 || tableau[*pointeurcasedepart] == 4) && tableau[*pointeurcasearrivee]==0 )

        {

        if((*pointeurcasearrivee/5)%2 ==1)
        {
            if((*pointeurcasedepart-9 == *pointeurcasearrivee) || (*pointeurcasedepart-11 == *pointeurcasearrivee))
            {

                tableau[*pointeurcasedepart] =  0 ;
                tableau[*pointeurcasearrivee] = typedepion;
                tableau[((*pointeurcasearrivee+*pointeurcasedepart)/2 )] = 0;
                *pointeursurchoix = 1;

            }

             else
                if (typedepion==4)
            {
                 if((*pointeurcasedepart+9 == *pointeurcasearrivee) || (*pointeurcasedepart+11 == *pointeurcasearrivee))
            {

                tableau[*pointeurcasedepart] =  0 ;
                tableau[*pointeurcasearrivee] = typedepion;
                tableau[((*pointeurcasearrivee+*pointeurcasedepart)/2)] = 0;
                *pointeursurchoix = 1;

                }
            }
        }

        if((*pointeurcasearrivee/5)%2 ==0)
        {

            if((*pointeurcasedepart-9 == *pointeurcasearrivee) || (*pointeurcasedepart-11 == *pointeurcasearrivee))
            {

                tableau[*pointeurcasedepart] =  0 ;
                tableau[*pointeurcasearrivee] = typedepion;
                tableau[((*pointeurcasearrivee+*pointeurcasedepart)/2+1)] = 0;
                *pointeursurchoix = 1;

                }
            else
                if (typedepion==4)   //saut de la reine joueur
            {
                 if((*pointeurcasedepart+9 == *pointeurcasearrivee) || (*pointeurcasedepart+11 == *pointeurcasearrivee))
            {

                tableau[*pointeurcasedepart] =  0 ;
                tableau[*pointeurcasearrivee] = typedepion;
                tableau[((*pointeurcasearrivee+*pointeurcasedepart)/2+1)] = 0;
                *pointeursurchoix = 1;

                }
            }

        }
    }
}
}

