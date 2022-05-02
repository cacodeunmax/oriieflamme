/** 
*\file plateau.h
*
*\author Noémie TURMEL
*Ce fichier decrit l'ensemble des fonctions associés à la manipulation du plateau
*Il contient 6 fonctions et 1 type : 
*- le type \a plateau 
*- create_plateau() pour créer un nouveau plateau (et les deux factions qui joueront dessus)
*- free_plateau(p) pour libérer la mémoire associée à un plateau p(et ses deux factions)
*
*- initialiser_plateau(p) pour initialiser une nouvelle manche du jeu, ou, le cas échéant, indiquer que le jeu est terminé
*- ask_faction() qui renvoie la liste des deux factions du jeu
*- put_card(p,c) pour permettre à une faction de poser une carte face cachée sur le plateau
*-flip_card(p,c) pour retourner une carte face visible et activer son effet
*/

#ifndef PLATEAU_H
#define PLATEAU_H

#include "carte.h"
#include "faction.h"
#include "struct.h"

/**
*\brief donne le sens de la carte a la postion x y
*\param p le plateau,
*\param x un entier qui représente la position en abscisse
*\param y un entier qui représente la position en ordonne
*\return le sens
*/
int get_c_sens(plateau p, int x, int y);

/**
*\brief donne la carte a la postion x y
*\param p le plateau,
*\param x un entier qui représente la position en abscisse
*\param y un entier qui représente la position en ordonne
*\return la carte a la position x y du plateau
*/
carte get_c_carte(plateau p, int x, int y);

/**
*\brief donne la faction de la carte a la postion x y
*\param p le plateau,
*\param x un entier qui représente la position en abscisse
*\param y un entier qui représente la position en ordonne
*\return une pointeur vers la faction de la carte a la position x y
*/
faction* get_c_fac(plateau p, int x, int y);

/**
*\brief set le sens de la carte a la postion x y
*\param p le plateau,
*\param x un entier qui représente la position en abscisse
*\param y un entier qui représente la position en ordonne
*\param s le nouveau sens de la carte
*\return nothing
*/
void set_c_sens(plateau p, int x, int y, int s);

/**
*\brief donne le sens de la carte a la postion x y
*\param p le plateau,
*\param x un entier qui représente la position en abscisse
*\param y un entier qui représente la position en ordonne
*\return le sens
*/
void set_c_carte(plateau p, int x, int y, carte c);

void set_c_fac(plateau p, int x, int y, faction* f);

void set_c_nulle (plateau p, int x, int y);

/**
*\brief créer un nouveau plateau (et les deux factions qui joueront dessus))
*\return le plateau créé 
*/
plateau create_plateau();


/**
*\brief libérer la mémoire associée à un plateau (et ses deux factions)
*\return nothing 
*/
void free_plateau(plateau p);



/**
*\brief initialiser une nouvelle manche du jeu, ou, le cas échéant, indiquer que le jeu est terminé
*\param p un pointeur vers plateau 
*\param f1 un pointeur vers une faction
*\param f2 un pointeur vers une faction
*\return nothing 
*/
int initialiser_manche(plateau* p, faction* f1, faction* f2);


/**
*\brief renvoie le couple des deux factions du jeu
*\param p un plateau 
*\return le couple des deux factions du jeu
*/
couple get_faction(plateau p);



/**
*\brief pose la carte sur le plateau à la position (x,y)
plateau est modifié, la main de la faction aussi
*\param p un pointeur vers plateau,
*\param c une carte
*\param f un pointeur de faction
*\param x un entier qui représente la position en abscisse
*\param y un entier qui représente la position en ordonne
*\return nothing
*/
void put_card(plateau *p,carte c, faction *f, int x,int y);



/**
*\brief retourne la carte la plus en haut à gauche face visible, active son effet, et renvoie cette carte
plateau est modifié
*\param p un pointeur vers un plateau
*\return une carte
*/
carte flip_card(plateau *p);


/**
*\brief détermine qui a gagné la manche, et actualise le nombre de manche gagné pour chaque faction
le plateau est modifié, en l'occurence les factions définies dans le plateau
*\param p un pointeur plateau
*\return nothing
*/
void victory_manche(plateau* p);

#endif