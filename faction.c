#ifndef FACTION_C
#define FACTION_C

#include "struct.h"
#include "struct.c"
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include "constante.h"
#include "carte.c"

/**
* \file faction.c
*
* \author Nathan VETTER
* Implémente les fonctions liées aux factions.
*/


int get_point(faction f){
    return f.nb_point;
}

int get_vic(faction f){
    return f.nb_v;
}

void add_point(faction f, int p){
    f.nb_point += p;
}

void shuffle(faction f){
    srand(time(NULL));
    carte catalogue[DECK_SIZE];
    create_catalogue(catalogue);

    for (int i = 0; i < DECK_SIZE-1; ++i){
        int j = rand() % (DECK_SIZE-i) + i;
        carte temp = catalogue[i];
        catalogue[i] = catalogue[j];
        catalogue[j] = temp;
    }

    pioche piochef = create_empty_pioche();

    for (int i=0; i< DECK_SIZE; i++){
        pioche_add(catalogue[i], &piochef);
    }

    f.pioche= &piochef;



}

void set_point(faction f, int p){
    f.nb_point = p;
}

void set_vic(faction f, int v){
    f.nb_v = v;
}

int has_redrawn(faction f){
    return f.redraw;
}

void draw(faction f){
    pioche* pioche = f.pioche;
    int i;
    for (i=0; i<8; i++){
        (f.hand.hand)[i]=depioche(pioche);
    }
}

void clearHand(faction f){
    int i;
    for (i=0; i<8; i++){
        f.hand.hand[i]=CN;
    }
}

void redraw(faction f){
    clearHand(f);
    shuffle(f);
    draw(f);
}





#endif