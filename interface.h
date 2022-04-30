/**
* \file interface.h
*
* \author Nathan VETTER
* Décrit les fonctions d'interaction avec les joueurs.
* 7 fonctions :
* - show_plateau(plateau) qui montre le plateau
* - show_main(faction) qui montre la main d'une faction
* - show_redraw(faction) qui propose l'option de repiocher à une faction
* - chose_card(faction) pour permettre au joueur de choisir une carte à jouer
* - chose_pos(carte, plateau) pour permettre au joueur de choisir l'emplacement ou il pose sa carte
* - show_effect(carte) qui montre l'effet de la dernière carte jouée
* - show_winner() qui affiche le gagnant
*/



#include "plateau.h"




/**
* \brief Show the board
* \param p The board
* \return Nothing
*/
void show_plateau(plateau);

/**
* \brief Show the hand of a faction
* \param f The faction whose hand is shown
* \return Nothing
*/
void show_hand(faction);

/**
* \brief Show the option to redraw
* \param f The faction that could redraw
* \return 1 if the player redraw, 0 otherwise
*/
int show_redraw(faction);

/**
* \brief Show the option to chose a card to play
* \param f The faction which is playing
* \return The chosen card
*/
carte chose_card(faction);

/**
* \brief Show the option to chose where to play the card
* \param p The board
* \param a A pointer to the column
* \param b A pointer to the line
* \return Nothing
*/
void chose_pos(plateau, int*, int*);

/**
* \brief Show the effect of the last played card
* \param c The last played card
* \return Nothing
*/
void show_effect(carte);

/**
* \brief Show the winner of the game
* \param p the board
* \return Nothing
*/
void show_winner(plateau);


/**
* \brief Show the winner of the current round
* \param p the board
* \return Nothing
*/
void show_winner_manche(plateau);