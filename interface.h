/**
* \file interface.h
*
* \author Nathan VETTER
* Décrit les fonctions d'interaction avec les joueurs.
* 9 fonctions :
* - show_plateau(plateau) qui montre le plateau
* - show_main(faction) qui montre la main d'une faction
* - show_redraw(faction) qui propose l'option de repiocher à une faction
* - chose_card(faction) pour permettre au joueur de choisir une carte à jouer
* - carte_adj(plateau p, int x, int y) qui regarde si une carte est adjacente à l'emplacement
* - chose_pos(carte, plateau) pour permettre au joueur de choisir l'emplacement ou il pose sa carte
* - show_effect(carte) qui montre l'effet de la dernière carte jouée
* - show_winner(plateau) qui affiche le gagnant
* - show_winner_manche(plateau) qui affiche le gagnant d'une manche
*/

#ifndef INTERFACE_H
#define INTERFACE_H


#include "plateau.h"





/**
* \brief Show the board
* \param p The board
* \return Nothing
*/
void show_plateau(plateau p);

/**
* \brief Show the hand of a faction
* \param f The faction whose hand is shown
* \return Nothing
*/
void show_hand(faction *f);

/**
* \brief Show the option to redraw
* \param f The faction that could redraw
* \return 1 if the player redraw, 0 otherwise
*/
int show_redraw(faction *f);

/**
* \brief Show the option to chose a card to play
* \param f The faction which is playing
* \return The chosen card
*/
carte chose_card(faction *f);

/**
* \brief Check if a card has been played next to a case
* \param p The board
* \param x The row of the case
* \param y the column of the case
* \return 1 if there is a card
*/
int carte_adj(plateau p, int x, int y);


/**
* \brief Show the option to chose where to play the card
* \param p The board
* \param a A pointer to the column
* \param b A pointer to the line
* \return Nothing
*/
void chose_pos(plateau p, int* a, int* b);

/**
* \brief Show the effect of the last played card
* \param c The last played card
* \return Nothing
*/
void show_effect(carte c);

/**
* \brief Show the winner of the game
* \param p the board
* \return Nothing
*/
void show_winner(plateau p);


/**
* \brief Show the winner of the current round
* \param p the board
* \return Nothing
*/
void show_winner_manche(plateau p);

#endif