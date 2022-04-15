#ifndef STRUCT_H
#define STRUCT_H

#define hand_size 8
/**
* \file interface.h
*
* \author Nathan VETTER
* define the type of structures used in all the other files
*/

/* nom et ref a la fonction */
typedef struct carte {
    char* name;
    int function_number;
} carte;



/* pile de carte */
typedef struct cartePioche{
  carte carte;
  struct cartePioche *suivant;
} *pioche;

/* tableau */
typedef struct hand{
    carte hand[hand_size];
} hand; 

/* nbr de point, main, redraw, nbr de victoire, pioche*/
typedef struct faction{
    int nb_point;
    hand hand;
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