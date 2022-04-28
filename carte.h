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