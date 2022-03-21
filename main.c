#include "interface.h"
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(){
    
    /*initialisation de la partie, du plateau, des factions et des variables que l'on va utiliser*/
    faction* first_player=NULL;
    faction* second_player=NULL;
    int* abscisse=NULL;
    int* ordonne=NULL; 
    int  fin, repioche;
    carte carte_buffer;
    plateau p=create_plateau(); 

    /*corps du jeu*/
    /*on utilise une boucle infinie mais en vérité il ya au maximum 3 manches dans une partie donc on va finir
    par passer dans le if(fin) et donc par le return*/
    
    while (1){
        fin = initialiser_manche(&p,first_player,second_player); 
        if (fin) {
            show_winner(p);
            free_plateau(p);
            return 0;
            } 
        else { /*si personne n'a encore gagne, la manche se deroule :*/
            

            /*on de montre tour a tour aux joueurs 1 et 2 leurs cartes, si ils veulent repiocher et qu'ils ne l'ont pas deja
            fait au cour de la partie on les fait repiocher puis on leur montre leur nouvelle carte*/
            
            show_plateau(p);
            show_hand(*first_player);
            if (! hasRedrawn(*first_player)){
                repioche = show_redraw(*first_player);
                if (repioche==0){
                    redraw(*first_player);
                    show_hand(*first_player);
                }
            }
            show_hand(*second_player);
            if (! hasRedrawn(*second_player)){
                repioche = show_redraw(*second_player);
                if (repioche){
                    redraw(*second_player);
                    show_hand(*second_player);
                }

            /*boucle for pour poser les cartes des joueurs 1 et 2*/
            int i;
            for (i=0; i<8; i++){
                show_plateau(p);
                show_hand(*first_player);
                carte_buffer= chose_card(*first_player);

                chose_pos(p,abscisse,ordonne);
                put_card(&p,carte_buffer,first_player,*abscisse,*ordonne);
                
                
                show_plateau(p);
                show_hand(*second_player);
                carte_buffer= chose_card(*second_player);
                chose_pos(p,abscisse,ordonne);
                put_card(&p,carte_buffer,second_player,*abscisse,*ordonne);
                }

            /*boucle while pour retourner toutes les cartes*/
            /*tant que l'on peut retourner des cartes, c'est a dire tant que flip_card ne renvoie pas null on les retourne*/   
            while (carte_buffer != NULL){
                carte_buffer=flip_card(&p);
                show_effect(carte_buffer);
            }
            /*fonctions supplémentaires qui calcul qui a gagne la manche en cours, et affiche aux joueurs le vainqueur de cette manche*/
            victory_manche(&p);
            show_winner_manche(p);
            }
    }
}
}