#ifndef STRUCT_H
#define STRUCT_H

/**
* \file struct.h
*
* \author Nathan VETTER
* define the type of structures used in all the other files
*/

/* nom et ref a la fonction */
typedef struct carte {
    char* name;
    int function_number;
    char* desc;
} carte;



/* pile de carte */
typedef struct cartePioche{
  carte carte;
  struct cartePioche *suivant;
} *pioche;

/* tableau */
typedef struct hand{
    carte hand[8];
} hand; 

/* nbr de point, main, redraw, nbr de victoire, pioche*/
typedef struct faction{
    char* nom;
    int nb_point;
    carte hand[8];
    int redraw;
    int nb_v;
    pioche* pioche;
} faction;  

/* couple de faction*/
typedef struct couple {
    faction fa;
    faction fb;
} couple;

/* carte et bool sens */
typedef struct cell{
    carte carte;
    int sens;
    faction* fac;
} cell; 

/* matrice*/
typedef struct grid{
    int size;
    cell** cases;
} grid;  

/* grid et 2 factions*/
typedef struct plateau{
    grid plateau;
    faction fa;
    faction fb;
} plateau;  






#endif