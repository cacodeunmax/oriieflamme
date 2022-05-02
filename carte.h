/**
* \file carte.h
* \author Nathan VETTER
*
* Décrit les carte et les fonctions associées. 
* 1 type :
* - le type \a carte qui représente les cartes
*/

#ifndef CARTE_H
#define CARTE_H

typedef struct carte carte;

/**
* \brief Get the name of a card
* \param c The card
* \return The name of the card
*/
char* get_name(carte c);

/**
* \brief Get the function number of a card
* \param c The card
* \return The function number of a card
*/
int get_func(carte c);

/**
* \brief Check if two card are equal
* \param c The first card
* \param v The second card
* \return The corresponding boolean
*/
int equals_carte(carte c, carte v);

/**
* \brief Commpare the name of a card and a string
* \param c The card
* \param name The string
* \return The corresponding boolean
*/
int equals(carte c, char* name);

/**
* \brief Check if a card is the empty card
* \param c The card
* \return 1 if empty, else 0
*/
int empty(carte c);

#endif