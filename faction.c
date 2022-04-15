#ifndef FACTION_C
#define FACTION_C

#include "faction.h"
#include <stddef.h>
#include <stdlib.h>

/**
* \file faction.h
*
* \author Nathan VETTER
* Implémente les fonctions liées aux factions.
*/


int has_redrawn(faction f){
    return f.redraw;
}

void redraw(faction f){
    clearHand(f);
    shuffle(f);
    draw(f);
}

void clearHand(faction f){
    int i;
    carte c;
    c.name="null";
    for (i=0; i<8; i++){
        f.hand.hand[i]=c;
    }
}

void draw(faction f){
    pioche* pioche = f.pioche;
    int i;
    for (i=0; i<8; i++){
        (f.hand.hand)[i]=depioche(pioche);
    }
}


#endif