
/**
* \file faction.h
*
* \author Nathan VETTER
* Décrit les factions et leurs fonctions.
* 5 fonctions et 2 types, ainsi que 2 getter et 3 setter:
* - le type \a faction qui représente les faction
* - le type \a couple qui regroupe les 2 factions
* - get_point(faction f)
* - get_vic(faction f)
* - set_point(faction *f, int p)
* - set_vic(faction *f, int v)
* - add_point(faction *f, int p)
* - hasRedrawn(faction f) pour savoir si une faction à repiocher dans la partie
* - redraw(faction *f) pour permettre à une faction de repiocher
* - clearHand(faction *f) pour vider la main d'une faction
* - shuffle(faction *f) pour mélanger les cartes d'une faction
* - draw(faction *f) qui permet à une faction de piocher 
*/

#ifndef FACTION_H
#define FACTION_H

typedef struct faction *faction;
typedef struct couple {
    faction fa;
    faction fb;
} couple;


/**
* \brief Get the number of point of a faction
* \param f The faction 
* \return The number of point of the faction
*/
int get_point(faction f);

/**
* \brief Get the number of round the faction won
* \param f The faction
* \return The number of victory
*/
int get_vic(faction f);

/**
* \brief Set the number of point of a faction to a desired value
* \param f The faction
* \param p The desired value
* \return nothing
*/
void set_point(faction *f, int p);

/**
* \brief Set the number of round a faction has won to a desired value
* \param f A pointer to the faction
* \param v The desired value
* \return nothing
*/
void set_vic(faction *f, int v);

/**
* \brief Add a desired value to the number of point of a faction 
* \param f A pointer to the faction
* \param p The desired value
* \return nothing
*/
void add_point(faction *f, int p);


/**
* \brief Check if a faction has already redrawn during the game
* \param f The faction that is checked
* \return The corresponding boolean
*/
int has_redrawn(faction f);

/**
* \brief Make a faction redraw using \b clearhand and \b shuffle
* \param f A pointer to the faction that redraw
* \return Nothing
*/
void redraw(faction *f);

/**
* \brief Make a faction clear their hand
* \param f A pointer to the faction that empty their hand
* \return Nothing
*/
void clearHand(faction *f);

/**
* \brief Make a faction shuffle their cards
* \param f A pointer to the faction that shuffle
* \return Nothing
*/
void shuffle(faction *f);

/**
* \brief Make a faction draw
* \param f A pointer to the faction that draw
* \return Nothing
*/
void draw(faction *f);

#endif