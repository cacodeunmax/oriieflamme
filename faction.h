
/**
* \file faction.h
*
* \author Nathan VETTER
* Décrit les factions et leurs fonctions.
* 5 fonctions et 2 types :
* - le type \a faction qui représente les faction
* - le type \a couple qui regroupe les 2 factions
* - hasRedrawn(faction) pour savoir si une faction à repiocher dans la partie
* - redraw(faction) pour permettre à une faction de repiocher
* - clearHand(faction) pour vider la main d'une faction
* - shuffle(faction) pour mélanger les cartes d'une faction
* - draw(faction) qui permet à une faction de piocher 
*/

typedef struct faction *faction;
typedef struct couple {
    faction fa;
    faction fb;
} couple;

int get_point(faction f);

int get_vic(faction f);

void set_point(faction f, int p);

void set_vic(faction f, int v);

void add_point(faction f, int p);


/**
* \brief Check if a faction has already redrawn during the game
* \param f The faction that is checked
* \return The corresponding boolean
*/
int has_redrawn(faction);

/**
* \brief Make a faction redraw using \b clearhand and \b shuffle
* \param f The faction that redraw
* \return Nothing
*/
void redraw(faction);

/**
* \brief Make a faction clear their hand
* \param f The faction that empty their hand
* \return Nothing
*/
void clearHand(faction);

/**
* \brief Make a faction shuffle their cards
* \param f The faction that shuffle
* \return Nothing
*/
void shuffle(faction);

/**
* \brief Make a faction draw
* \param f The faction that draw
* \return Nothing
*/
void draw(faction);