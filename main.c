#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "interface.h"
#include "constante.h"
#include "constantenn.h"

int main(){
    
    srand(time(NULL));
    /*initialisation de la partie, du plateau, des factions et des variables que l'on va utiliser*/
    faction* first_player=NULL;
    faction* second_player=NULL;
    int* abscisse=malloc(sizeof(int));
    int* ordonne=malloc(sizeof(int));
    int  fin, repioche;
    carte carte_buffer;
    plateau p=create_plateau();
    printf("Début de la partie!\n");

    /*corps du jeu*/
    /*on utilise une boucle infinie mais en vérité il ya au maximum 3 manches dans une partie donc on va finir
    par passer dans le if(fin) et donc par le return. Présentement, l'assignation des points ne fonctionne pas
    et la partie ne se finie donc jamais */

    int r = rand() % 2;
        if (r){
            first_player = &p.fa;
            second_player = &p.fb;
        } else {
            first_player = &p.fb;
            second_player = &p.fa;  
        }
    while (1){


        fin = initialiser_manche(p,first_player,second_player);
        if (fin) {
            show_winner(p);
            return 0;
            } 
        else { /*si personne n'a encore gagne, la manche se deroule :*/
            

            /*on de montre tour a tour aux joueurs 1 et 2 leurs cartes, si ils veulent repiocher et qu'ils ne l'ont pas deja
            fait au cour de la partie on les fait repiocher puis on leur montre leur nouvelle carte*/

            if (!((first_player)-> nb_point + (second_player) -> nb_point)%2){
            int r = rand() % 2;
            if (r){
                first_player = &p.fa;
                second_player = &p.fb;
            } else {
                first_player = &p.fb;
                second_player = &p.fa;  
            }

            } else {
                faction* temp = first_player;
                first_player = second_player;
                second_player= temp;
            }

            
            printf("Tour du %s:\n", first_player->nom);
            show_hand(first_player);
            if (! has_redrawn(*first_player)){
                repioche = show_redraw(first_player);
                if (repioche){
                    redraw(first_player);
                    show_hand(first_player);
                }
            }

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
            for (i=0; i<5; i++){
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

                if (get_func(carte_buffer)!=17){
                    merabet=get_func(carte_buffer);}

                if (!empty(carte_buffer)){
                   
                    printf("\n mon effet de carte \n");
                    show_effect(carte_buffer);
                    show_plateau(p);

                    printf("\n\nPoints joueur 1: %i\n", p.fa.nb_point);
                    printf("Points joueur 2: %i\n\n", p.fb.nb_point);
                }
                
            }
            /*fonctions supplémentaires qui calcul qui a gagne la manche en cours, et affiche aux joueurs le vainqueur de cette manche*/
            victory_manche(&p);
            show_winner_manche(p);
            }
    }
}
}