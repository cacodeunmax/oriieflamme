/**
* \file carte.h
* \author Nathan VETTER
*
* Décrit les carte. 
* 1 type :
* - le type \a carte qui représente les cartes
*/

typedef struct not_defined_carte *carte;


char* get_name(carte c);

int get_func(carte c);

int equals_carte(carte c, carte v);

int equals(carte c, char* name);

int empty(carte c);