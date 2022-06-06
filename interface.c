#ifndef INTERFACE_C
#define INTERFACE_C

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "faction.h"

#include "constante.h"

#include "carte.h"
#include "interface.h"


#include "constante.h"


void show_plateau(plateau p){
    carte temp;
    for (int i =0; i <N; i++ ){
        for (int j =0; j <N; j++ ){
            temp = get_c_carte(p, i, j);
            printf("%i ", !empty(temp));
        }
        printf("\n");
    }
}

void show_hand(faction *f){
    carte temp;
    for (int i = 0; i < HAND_SIZE; i++){
        temp = f->hand[i];
        if (!empty(temp)){
            printf("%i: %s\n", i, temp.name);
        }
    }
}

int show_redraw(faction *f){
    int repioche;
    printf("Voulez-vous repiocher? (1 = oui  0 = non)\n");
    scanf("%d", &repioche);
    f->redraw = repioche;
    return repioche;
}

carte chose_card(faction *f){
    printf("Quelle carte voulez-vous jouer");
    int card_nb;
    scanf("%d", &card_nb);
    carte chosen =f->hand[card_nb];
    f->hand[card_nb] = CN;
    return chosen;
}

int carte_adj(plateau p, int x, int y){
    int max = N-1;
    if ((x ==0 && y ==0)||(x==0 && y == max ) || (x == max && y == 0) || (x ==max && y == max)){
        return 0;
    } else if (x == 0) {
        if (y == max/2  && !equals_carte( get_c_carte(p, x+1, y), CN)) {
            return 1;
        }
        else { 
            return 0;
        }
    } else if (x == max){
        if (y == max/2  && !equals_carte( get_c_carte(p, x-1, y), CN)){
            return 1;
        }
        else { 
            return 0;
        }
    } else if (y == 0) {
        if (x == max/2  && !equals_carte( get_c_carte(p, x, y+1), CN)) {
            return 1;
        }
        else {
            return 0;
        }
    } else if (y == max){
        if (x == max/2 && !equals_carte( get_c_carte(p, x, y-1), CN)) {
            return 1;
        }
        else { 
            return 0;
        }
    } else if (!empty( get_c_carte(p, x, y-1)) || !empty( get_c_carte(p, x+1, y)) || !empty( get_c_carte(p, x-1, y)) || !empty( get_c_carte(p, x, y+1))){
            return 1;
        } else { 
            return 0;
        }
}

void chose_pos(plateau p, int* x, int* y){
    printf("Où souhaitez-vous poser votre carte?\nLes positions possibles sont:\n");
    if (empty(get_c_carte(p, (N-1)/2, (N-1)/2))){
        printf("%3d %3d\n", (N-1)/2, (N-1)/2);
    } else {
        for (int i =0; i < N; i++){
            for (int j =0; j < N; j++){
                if (carte_adj(p, i, j) && empty(get_c_carte(p, i,j))){
                    printf("%3d %3d\n", i, j);
                }
            }
        }
    }
    printf("Ligne:\n");
    scanf("%d", x);
    printf("Colonne:\n");
    scanf("%d", y);
    
}

void show_effect(carte c){
    printf("%s: %s\n", c.name, c.desc);
}

void show_winner(plateau p){
    if (p.fa.nb_v == MG){
        printf("Le gagnant est: Joueur 1\n");
    } else {
        printf("Le gagnant est: Joueur 2\n");
    }
}

void show_winner_manche(plateau p){

    printf("Nombre de victoire de Joueur 1: %i\n", get_vic(p.fa));
    printf("Nombre de victoire de Joueur 2: %i\n", get_vic(p.fb));
}


#endif