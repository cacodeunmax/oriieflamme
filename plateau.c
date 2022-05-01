#ifndef PLATEAU_C
#define PLATEAU_C

#include "struct.c"
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "faction.c"
#include "struct.h"
#include "constante.h"



/**
* \file plateau.c
*
* \author Nathan VETTER
* Implémente les fonctions liées aux factions.
*/


int get_c_sens(plateau p, int x, int y){
    return p.plateau.cases[x][y].sens;
}

carte get_c_carte(plateau p, int x, int y){
    return p.plateau.cases[x][y].carte;
}

faction get_adverse(plateau p, faction f){
    if (&p.fa == &f){
        return p.fb;
    } else {
        return p.fa;
    }
}

void set_c_nulle (plateau p, int x, int y){
    p.plateau.cases[x][y] = CLN;
}

faction* get_c_fac(plateau p, int x, int y){
    return p.plateau.cases[x][y].fac;
}

void set_c_sens(plateau p, int x, int y, int s){
    p.plateau.cases[x][y].sens = s;
}

void set_c_carte(plateau p, faction *f, int x, int y, carte c){
    p.plateau.cases[x][y].carte = c;
    p.plateau.cases[x][y].sens = 0;
    p.plateau.cases[x][y].fac = f;

}

void set_c_fac(plateau p, int x, int y, faction* f){
    p.plateau.cases[x][y].fac = f;
}

void set_victory(faction *f){
    f->nb_v ++;
}

#include "effets.c"

plateau create_plateau(){
    plateau p;
    p.plateau = grid_create(4*HAND_SIZE-1);
    int i, j;
    for (i = 0; i<p.plateau.size; i++){
        for (j=0; j< p.plateau.size; j++){
            p.plateau.cases[i][j]=CLN;
        }
    }

    faction fa;
    faction fb;

    fa.nom = "Premier joueur";
    fa.nb_v=0;
    fa.nb_point=0;
    fa.redraw=0;
    
    clearHand(&fa);
    shuffle(&fa);

    fb.nom = "Deuxième joueur";
    fb.nb_v=0;
    fb.nb_point=0;
    fb.redraw=0;
    clearHand(&fb);
    shuffle(&fb);

    p.fa = fa;
    p.fb = fb;


    return p;
}

void free_plateau(plateau p){
    grid_free(p.plateau);
}

couple get_faction(plateau p){
    couple c;
    c.fa = p.fa;
    c.fb = p.fb;
    return c;
}

void put_card(plateau *p,carte c, faction *f, int x,int y){
    p-> plateau.cases[x][y].carte= c;
    p-> plateau.cases[x][y].fac = f;

}



carte flip_card(plateau *p){
    int i, j;
    int x,y;
    carte c;
    c = CN;

    faction *f;
    for (i = 0; i <4 * HAND_SIZE -1; i++){
        for (j=0; j< 4 * HAND_SIZE -1; j++){
           if ( strcmp(c.name, "null")){
                break;
            } 
            if ((!empty(p-> plateau.cases[i][j].carte))&&(!p-> plateau.cases[i][j].sens)){
                p-> plateau.cases[i][j].sens = 1;
                c = p-> plateau.cases[i][j].carte;
                f = p-> plateau.cases[i][j].fac;
                x=i;
                y=j;
                break;
            }
        }
    }
    //active(c, f, p, x, y);
    last_card = c.function_number;
    return c;
}


void victory_manche(plateau* p){
    if (!prevel){
        printf("Nombre de point du %s: %i.\n", p->fa.nom, p->fa.nb_point);
        printf("Nombre de point du %s: %i.\n", p->fb.nom, p->fb.nb_point);
        int i, j;
        if ( p -> fa.nb_point > p-> fb.nb_point){
            p -> fa.nb_v++;
            printf("victoire du %s!\n", p->fa.nom);
        } else if ( p -> fa.nb_point < p-> fb.nb_point){
            p -> fb.nb_v++;
            printf("victoire du %s!\n", p->fb.nom);
        } else {
            for (i = 0; i <4 * HAND_SIZE -1; i++){
            for (j=0; j< 4* HAND_SIZE -1; j++){
                if ((!empty(p-> plateau.cases[i][j].carte))){
                    p-> plateau.cases[i][j].fac->nb_v ++;
                    printf("victoire du %s!\n", p->plateau.cases[i][j].fac->nom);
                    goto END;
                }
            }
                    
            }
        }
    }
    END:;
}

int initialiser_manche(plateau p, faction* f1, faction* f2){
    prevel =0;
    if (f1 == NULL){          
        int r = rand() % 2;
        if (r){
            *f1 = p.fa;
            *f2 = p.fb;
        } else {
            *f1 = p.fb;
            *f2 = p.fa;  
        }
        
    } else if ((f1 -> nb_v == MG) || (f2 -> nb_v == MG)){
        return 1;
    
    }else if (!(f1-> nb_point + f2 -> nb_point)%2){
        int r = rand() % 2;
        if (r){
            *f1 = p.fa;
            *f2 = p.fb;
        } else {
            *f1 = p.fb;
            *f2 = p.fa;  
        }

    } else {
        faction temp = *f1;
        *f1 = *f2;
        *f2= temp;
    }


    f1 -> nb_point=0;
    f2-> nb_point=0;
    clearHand(f1);
    shuffle(f1);
    draw(f1);
    clearHand(f2);
    shuffle(f2);
    draw(f2);

    int i, j;
    for (i = 0; i<p.plateau.size; i++){
        for (j=0; j< p.plateau.size; j++){
            p.plateau.cases[i][j]=CLN;
        }
    }
    return 0;
}



#endif