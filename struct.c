#ifndef STRUCT_C
#define STRUCT_C

#include "struct.h"
#include <stddef.h>
#include <stdlib.h>

/**
* \file interface.h
*
* \author Nathan VETTER
* define the functions used on structures.
*/



grid grid_create(int size) {
    grid g;
    g.size = size;
    g.cases = (cell**)malloc(size * sizeof(cell*));

    int i;
    for (i = 0; i < size; i=i+1) {
    g.cases[i] = (cell*)calloc(size, sizeof(cell));
    }

    return g;
}

void grid_free(grid g) {
    int s = g.size;

    int i;
    for (i = 0; i < s; i=i+1) {
    free(g.cases[i]);
    
    }
    
    free(g.cases);

}
/*
void grid_show(matrix mat){
    int size = mat.size;
    int i, j;
    for (i=0; i< size; i=i+1){
        for (j=0; j < size; j=j+1)
            printf("%8i ", mat.cells[i][j]);
        printf("\n") ;   
    }
    printf("\n") ;
}
*/

pioche create_empty_pioche(){
    return NULL;
}

pioche make(carte c, pioche p) {
    pioche res = malloc(sizeof(struct cartePioche));

    res->carte = c;
    res->suivant = p;

    return res;
}

void pioche_add(carte c, pioche *p){
    *p= make(c, *p);
}

carte depioche(pioche *p){
    carte c = (*p)->carte;
    *p = (*p)->suivant;
    return c;
}

#endif