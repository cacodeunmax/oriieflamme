#ifndef STRUCT_H
#define STRUCT_H

#include "constante.h"

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
    carte hand[HAND_SIZE];
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


/**
* \brief Create a grid
* \param size The size of the grid
* \return The created grid
*/
grid grid_create(int size);


/**
* \brief Free a grid
* \param g The grid
* \return Nothing
*/
void grid_free(grid g);


/**
* \brief Create a pioche
* \return The created pioche
*/
pioche create_empty_pioche();


/**
* \brief Make a pioche starting with a specified
* \param c The card
* \param p The pioche
* \return Nothing
*/
pioche make(carte c, pioche p);


/**
* \brief Add a carte to a pioche
* \param p A pointer to the pioche
* \param c The carte to add
* \return Nothing
*/
void pioche_add(carte c, pioche *p);


/**
* \brief Remove a carte from a pioche
* \param p A pointer to the pioche
* \return The removed carte
*/
carte depioche(pioche *p);

#endif