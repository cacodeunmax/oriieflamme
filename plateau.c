#include "struct.c"
#include "struct.h"
#include <stddef.h>
#include <stdlib.h>
#include "faction.c"
#include <string.h>

#define HAND_SIZE 8
#define MG 2

/**
* \file faction.h
*
* \author Nathan VETTER
* Implémente les fonctions liées aux factions.
*/


plateau create_plateau(){
    plateau p;
    p.plateau = grid_create(31);
    int i, j;
    cell cl;
    carte c;
    c.name="null";
    faction* fn;
    cl.carte = c;
    cl.sens=0;
    cl.fac = fn;
    for (i = 0; i<p.plateau.size; i++){
        for (j=0; j< p.plateau.size; j++){
            p.plateau.cases[i][j]=cl;
        }
    }

    faction fa;
    faction fb;

    fa.nb_v=0;
    fa.nb_point=0;
    fa.redraw=0;
    clearHand(fa);
    shuffle(fa);

    fb.nb_v=0;
    fb.nb_point=0;
    fb.redraw=0;
    clearHand(fb);
    shuffle(fb);

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
    carte c;
    c.name= "null";
    faction *f;
    for (i = 0; i <31; i++){
        for (j=0; j< 31; j++){
            if ((!strcmp(p-> plateau.cases[i][j].carte.name, "null"))&&(p-> plateau.cases[i][j].sens)){
                c = p-> plateau.cases[i][j].carte;
                f = p-> plateau.cases[i][j].fac;
                break;
            }
            if ( !strcmp(c.name, "null")){
                break;
            }
        }
    }
    connec_carte(*p, f, c.function_number);
    return c;
}


void victory_manche(plateau* p){
    int i, j;
    if ( p -> fa.nb_point > p-> fb.nb_point){
        p-> fa.nb_v += 1;
    } else if ( p -> fa.nb_point < p-> fb.nb_point){
        p-> fb.nb_v += 1;
    } else {
        for (i = 0; i <31; i++){
        for (j=0; j< 31; j++){
            if ((!strcmp(p-> plateau.cases[i][j].carte.name, "null"))){
                p-> plateau.cases[i][j].fac->nb_point+=1;
                goto END;
            }
        }
                

    }
    }
    END:;
}

int initialiser_manche(plateau* p, faction* f1, faction* f2){
    if (*f1 = fn){
        goto RAND;
    }
    else if ((f1-> nb_point + f2 -> nb_point)%2){
        goto RAND;
    } else if ((f1 -> nb_v == MG) || (f2 -> nb_v == MG)){
        return 1;

    } else {
        faction temp = *f1;
        *f1 = *f2;
        *f2= temp;
    }

    int r = rand() % 2;

    RAND:
        
        if (r){
            *f1 = p-> fa;
            *f2 = p-> fb;
        } else {
            *f1 = p-> fb;
            *f2 = p-> fa;  
        }
        

    f1 -> nb_point=0;
    f2-> nb_point=0;
    clearHand(*f1);
    shuffle(*f1);
    clearHand(*f2);
    shuffle(*f2);

    grid_free(p->plateau);
    p-> plateau = grid_create( 4* HAND_SIZE - 1);
    return 0;
}