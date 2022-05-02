#ifndef CONSTANTE_H
#define CONSTANTE_H


#include "struct.h"

#define N 32
#define HAND_SIZE 8
#define DECK_SIZE 47

#define MG 2 

const carte CN = { "null", -1, "carte nulle"};
const faction FN = {};
const cell CLN = {{ "null", -1, "carte nulle"}, 0, NULL};

int last_card;
int prevel;

#endif