#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "interface.c"
//#include "effets.c"

int main(){
    
    srand(time(NULL));
    /*initialisation de la partie, du plateau, des factions et des variables que l'on va utiliser*/
    faction* first_player=NULL;
    first_player = malloc(sizeof(faction));
    faction* second_player=NULL;
    second_player = malloc(sizeof(faction));
    int* abscisse=malloc(sizeof(int));
    int* ordonne=malloc(sizeof(int));
    int  fin, repioche;
    carte carte_buffer;
    plateau p=create_plateau();
    printf("Début de la partie!\n");

    /*corps du jeu*/
    /*on utilise une boucle infinie mais en vérité il ya au maximum 3 manches dans une partie donc on va finir
    par passer dans le if(fin) et donc par le return*/
    
    while (1){


        fin = initialiser_manche(p,first_player,second_player);
        if (fin) {
            show_winner(p);
            free_plateau(p);
            free(first_player);
            free(second_player);
            return 0;
            } 
        else { /*si personne n'a encore gagne, la manche se deroule :*/
            

            /*on de montre tour a tour aux joueurs 1 et 2 leurs cartes, si ils veulent repiocher et qu'ils ne l'ont pas deja
            fait au cour de la partie on les fait repiocher puis on leur montre leur nouvelle carte*/
            printf("Tour du %s:\n", first_player->nom);
            show_hand(first_player);
            if (! has_redrawn(*first_player)){
                repioche = show_redraw(first_player);
                if (repioche){
                    redraw(first_player);
                    first_player->nb_point++;
                    show_hand(first_player);
                }
            }

            //add_point(first_player, 2);
            printf("\n\nTour du %s:\n", second_player->nom);
            show_hand(second_player);
            if (! has_redrawn(*second_player)){
                repioche = show_redraw(second_player);
                if (repioche){
                    redraw(second_player);
                    show_hand(second_player);
                }

            /*boucle for pour poser les cartes des joueurs 1 et 2*/
            int i;
            for (i=0; i<HAND_SIZE; i++){
                printf("\n\nTour du %s:\n", first_player->nom);
                show_plateau(p);
                show_hand(first_player);
                carte_buffer= chose_card(first_player);

                chose_pos(p,abscisse,ordonne);
                put_card(&p,carte_buffer,first_player,*abscisse,*ordonne);
                
                printf("\n\nTour du %s:\n", second_player->nom);
                show_plateau(p);
                show_hand(second_player);
                carte_buffer= chose_card(second_player);
                chose_pos(p,abscisse,ordonne);
                put_card(&p,carte_buffer,second_player,*abscisse,*ordonne);
                }

            /*boucle while pour retourner toutes les cartes*/
            /*tant que l'on peut retourner des cartes, c'est a dire tant que flip_card ne renvoie pas null on les retourne*/   
            while (!empty(carte_buffer)){
                carte_buffer=flip_card(&p);
                if (!empty(carte_buffer)){
                    show_effect(carte_buffer);
                }
                
            }
            /*fonctions supplémentaires qui calcul qui a gagne la manche en cours, et affiche aux joueurs le vainqueur de cette manche*/
            victory_manche(&p);
            show_winner_manche(p);
            }
    }
}
}