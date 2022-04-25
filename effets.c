/** 
*\file plateau.h
*
*\author Noémie TURMEL
*Ce fichier decrit l'ensemble des fonctions associés à l'activation des effets des cartes
*Il contient les 32 fonctions relatives aux 32 cartes
*/



#include "struct.h"
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "struct.c"


/* a mettre dans carte.c*/
int equals_carte(carte c, carte v){
    return (strcmp(c.name,v.name)&&(c.function_number==v.function_number));
}


#define N 32
carte null={"null",-1};

/*------------------------------------------------------------------------------------*/
/**
*\brief active la carte fise
*\param p un pointeur vers une faction
*\return nothing 
*/
void f_fise(faction *p){
    ((*p).nb_point)++;
}

/**
*\brief active la carte fisa
*\param p un pointeur vers une faction
*\param m la grille
*\return nothing 
*/
void f_fisa(faction *p,grid m){
    int count=0;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cell current_cell=m.cases[i][j];
            carte current_carte=current_cell.carte;
            //if (current_cell.carte!=null)
            if (!(strcmp(current_carte.name,"null")))
             {
                if (current_cell.sens==1){
                    count++;
                }
            }
    }
    if (count%2==0){
        ((*p).nb_point)=((*p).nb_point) + 2;
    }
    }
}




/**
*\brief active la carte fc
*\param p un pointeur vers une faction
*\param m la grille
*\return nothing 
*/
void f_fc(faction *p,grid m){
    
    int au_moins_1=0;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cell current_cell=m.cases[i][j];
            carte current_carte=current_cell.carte;
            if (strcmp(current_carte.name,"FC"))
            /*if (current_cell.carte.name!="null")*/
            {
                if (current_cell.sens==1){
                ((*p).nb_point)=((*p).nb_point) + 4;
                au_moins_1=1;
                break;}
            }
            /*if (au_moins_1==1){
                break;}*/
        }
    if (au_moins_1==1){break;}}
}

/**
*\brief active la carte ecologiie
*\param p un pointeur vers une faction
*\param m la grille
*\return nothing 
*/
void f_ecologiie(faction *p,grid m){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cell current_cell=m.cases[i][j];
            carte current_carte=current_cell.carte;
            if (strcmp(current_carte.name,"FC")||strcmp(current_carte.name,"FISE")||strcmp(current_carte.name,"FISA"))
            {
                if (current_cell.sens==1){
                ((*p).nb_point)++;}    
            }
        }
    }
}

/*-------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void swap(carte *a, carte *b) {
    carte temp = *a;
    *a = *b;
    *b = temp;
}

void randomize(carte arr[], int n) {
    srand(time(NULL));
    int i;
    for(i = n-1; i > 0; i--) {
        int j = rand() % (i+1);
        swap(&arr[i], &arr[j]);
    }

}

/**
*\brief fonction auxilière a la fonction qui active la carte liien, elle pose la carte c à la gauche de la carte la plus en haut à gauche du plateau
*\param p un pointeur vers une faction
*\param m la grille
*\param c une carte
*\return nothing 
*/
void haut_gauche(grid m,carte c, faction *f){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cell current_cell=m.cases[i][j];

            int current_sens=current_cell.sens;
            /*carte current_carte=current_cell.carte;*/
            /* le cas current_sens==1 et i=0 n'est pas possible*/
            if (current_sens==1){
                m.cases[i-1][j]=(cell) {c,0,f};
                break;
            }
        }
    }
}
            

/**
*\brief active la carte liiens
*\param p un pointeur vers une faction
*\param m la grille
*\return nothing 
*/
void f_liiens(faction *p,grid m){

    carte cartes_retirees[hand_size*2];
    for (int k=0; k<(hand_size*2); k++){
        cartes_retirees[k]=null;
    }
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cell current_cell=m.cases[i][j];
            carte current_carte=current_cell.carte;
            int current_sens=current_cell.sens;
            if (  (strcmp(current_carte.name,"FC")||strcmp(current_carte.name,"FISE")||strcmp(current_carte.name,"FISA"))&&(current_sens==1))
            {
                carte cc=current_carte;
                //cell cellule ={null,-1,NULL};
                m.cases[i][j]=(cell) {null,-1,NULL};

                for (int k=0; k<(hand_size*2); k++){

                    if     ( equals_carte((cartes_retirees[k]),    null )){
                        cartes_retirees[k]=cc;
                        break;}
                }
            }
        }
    } 
    //a ce moment la de la fonction carte_retirees contient les cartes retirées
    randomize(cartes_retirees,(hand_size*2)); //on shuffle
    for (int k=0; k<(hand_size*2); k++){
        carte ccc=cartes_retirees[k];
        haut_gauche(m,ccc,p);
        
    }
}



/**
*\brief active les effets de la carte soirée sans alcool

*\param m la grille
*\return nothing 
*/
void f_ssa(/*faction *p,*/grid m){
    
    //etape 1
    int oui_alcool=0;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cell current_cell=m.cases[i][j];
            carte current_carte=current_cell.carte;
            if (strcmp(current_carte.name,"alcool")){
                oui_alcool=1;
                break;
            }
        }
        if (oui_alcool==1){break;}
    }


    if (oui_alcool==1){
    //etape 2
    for (int i=1; i<(N-1); i++){
        for (int j=0; j<N; j++){
            cell current_cell=m.cases[i][j];
            carte current_carte=current_cell.carte;
            int current_sens=current_cell.sens;
            if (  (strcmp(current_carte.name,"FC")||strcmp(current_carte.name,"FISE")||strcmp(current_carte.name,"FISA"))&&(current_sens==1))
            {
                //cell cellule ={null,-1,NULL};
                m.cases[i][j]=(cell) {null,-1,NULL};
            }
        }
    }

    //etape 3 
    for (int j=0; j<N; j++){
        m.cases[0][j]=(cell) {null,-1,NULL};
        m.cases[N-1][j]=(cell) {null,-1,NULL};
    }
    }

}
/**
*\brief active les effets de la carte alcool

*\param m la grille
*\return nothing 
*/
void f_alcool(grid m, int i, int j){


    /* avec l'implémenation qu'on à on est jamais au bord du plateau*/
    m.cases[(i-1)][j]=(cell) {null,-1,NULL};
    m.cases[i+1][j]=(cell) {null,-1,NULL};
    m.cases[i][j-1]=(cell) {null,-1,NULL};
    m.cases[i][j+1]=(cell) {null,-1,NULL};

}
/**
*\brief active les effets de la carte café
*\param p un pointeur vers une faction
*\param m la grille
*\return nothing 
*/
void f_cafe(faction *p,grid m){
    int eco;
   for (int i=1; i<N; i++){
        for (int j=0; j<N; j++){
            cell current_cell=m.cases[i][j];
            carte current_carte=current_cell.carte;
            int current_sens=current_cell.sens;
            if (((strcmp(current_carte.name,"Thé")||strcmp(current_carte.name,"Alcool"))&&(current_sens==1))){
                m.cases[i][j]=(cell) {null,-1,NULL};
            }
            if ((strcmp(current_carte.name,"Ecocup")&&(current_sens==1))){
                ((*p).nb_point)++;
                eco++;
            }
        }
    }
    if (eco==0){
        ((*p).nb_point=((*p).nb_point) - 1);
    }
}
/**
*\brief active les effets de la carte thé
*\param p un pointeur vers une faction
*\param m la grille
*\return nothing 
*/
void f_the(faction *p,grid m){
    int eco;
   for (int i=1; i<N; i++){
        for (int j=0; j<N; j++){
            cell current_cell=m.cases[i][j];
            carte current_carte=current_cell.carte;
            int current_sens=current_cell.sens;
            if (((strcmp(current_carte.name,"Café")||strcmp(current_carte.name,"Alcool"))&&(current_sens==1))){
                m.cases[i][j]=(cell) {null,-1,NULL};
            }
            if ((strcmp(current_carte.name,"Ecocup")&&(current_sens==1))){
                ((*p).nb_point)++;
                eco++;
            }
        }
    }
    if (eco==0){
        ((*p).nb_point=((*p).nb_point) - 1);
    }
}

/*
void f_reprographie(faction* p, faction *q, grid m){
    liste_double lst;
    

}*/
void f_isolation(){

}
/**
*\brief active les effets de la carte sobriété
*\param p un pointeur vers une faction
*\param m la grille
*\return nothing 
*/
void f_sobriete(grid m){

    for (int i=1; i<N; i++){
    
        cell current_cell=m.cases[i][1];
        carte current_carte=current_cell.carte;
        m.cases[i][1]=(cell) {current_carte,1,current_cell.fac};

        current_cell=m.cases[i][(N-1)];
        current_carte=current_cell.carte;
        m.cases[i][(N-1)]=(cell) {current_carte,1,current_cell.fac};
    }
}

/**
*\brief active les effets de la carte heures supplémentaires
*\param p un pointeur vers une faction
*\param m la grille
*\return nothing 
*/
void f_heure(faction *adv,grid m){
    for (int i=1; i<N; i++){
        for (int j=0; j<N; j++){
            cell current_cell=m.cases[i][j];
            carte current_carte=current_cell.carte;
            int current_sens=current_cell.sens;
            if ((strcmp(current_carte.name,"Heures supplémentaires")&&(current_sens==1))){
                ((*adv).nb_point)=((*adv).nb_point)-3;
            }
        }
    }
}

/**
*\brief returns a pseudo-random value between 0 and max included
*\param p un pointeur vers une faction
*\param m la grille
*\return nothing 
*/
int rand_up_to(int max) {
  int r;
  do
    r = rand();
  while (r >= RAND_MAX - (RAND_MAX % (max + 1)));
  return r % (max + 1);
}



/**
*\brief active les effets de la carte Kahina Bouchama
*\param p un pointeur vers une faction
*\param m la grille
*\return nothing 
*/
void f_KH(faction *p,grid m){
    int i=0;
    int j=0;
    int current_sens=1;
    int var=0;

    while ((current_sens==0)||(var==0)){
        i =rand_up_to(N-1);
        j=rand_up_to(N-1);
        cell current_cell=m.cases[i][j];
        carte current_carte=current_cell.carte;
        int current_sens=current_cell.sens;
        int var=strcmp(current_carte.name,"null");
    }
    if ((current_sens==1)&&(var!=0))
    {
        m.cases[i][j]=(cell) {null,-1,NULL};
    }


;

/**
*\brief active les effets de la carte Kevin Goilard
*\param p un pointeur vers une faction
*\param m la grille
*\return nothing 
*/
void f_KH(faction *p,grid m){
    int count=0;

    while(count==0){
        int i =rand_up_to(N-1);
        for (int j=0; j<N; j++){

            cell current_cell=m.cases[i][j];
            carte current_carte=current_cell.carte;
            if (!(strcmp(current_carte.name,"null"))){
                count++;
                m.cases[i][j]=(cell) {null,-1,NULL};
            }
        }
    }

    ((*p).nb_point)=((*p).nb_point) - 2*count;
}



/**
*\brief active l'effet de la carte Merabet 
*\param p un pointeur vers une faction
*\param m la grille
*\param c la dernière carte qui a été retournée 
*\return nothing 
*/
void f_MM(faction *p,grid m, carte c){}










/**
*\brief active l'effet de la carte Jonas Senizergues
*\param p un pointeur vers une faction
*\param m la grille
*\param c la dernière carte qui a été retournée 
*\return nothing 
*/

void f_JS(faction *p,grid m){

   for (int i=1; i<N; i++){
        for (int j=0; j<N; j++){
            cell current_cell=m.cases[i][j];
            carte current_carte=current_cell.carte;
            int current_sens=current_cell.sens;
            if (((strcmp(current_carte.name,"Heures supplémentaires")&&(current_sens==1)))){
                m.cases[i][j]=(cell) {null,-1,NULL};
            }
        }
   }
}






/**
*\brief active l'effet de la carte Fetia Bannour
*\param p un pointeur vers une faction
*\param m la grille
*\param c la dernière carte qui a été retournée 
*\return nothing 
*/

void f_FB(faction *p,grid m){

   for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cell current_cell=m.cases[i][j];
            carte current_carte=current_cell.carte;
            int current_sens=current_cell.sens;
            if (((strcmp(current_carte.name,"Heures supplémentaires")&&(current_sens==1)))){
                
                for (int k=0; k<N;k++){
                    m.cases[i][k]=(cell) {null,-1,NULL};
                    m.cases[k][j]=(cell) {null,-1,NULL};
                }
            }
        }
   }
}




/**
*\brief active l'effet de la carte Catherine Dubois
*\param p un pointeur vers une faction
*\param m la grille
*\param c la dernière carte qui a été retournée 
*\return nothing 
*/

void f_CD(faction *p,grid m, int i, int j){
    int il=i;
    int jl;
    int ic;
    int jc=j;
    for (int k=0; i<N; i++){
        cell current_cell=m.cases[i][k];
        carte current_carte=current_cell.carte;
        int current_sens=current_cell.sens;
        if (( (!strcmp(current_carte.name,"null"))&&(current_sens==1))){
            jl=k;
        }
        current_cell=m.cases[k][j];
        current_carte=current_cell.carte;
        current_sens=current_cell.sens;
        if (( (!strcmp(current_carte.name,"null"))&&(current_sens==1))){
            ic=k;
  
        }
    }
    m.cases[ic][jc]=(cell) {null,-1,NULL};
    m.cases[il][jl]=(cell) {null,-1,NULL};

}

        


void supprime_last(grid m){
    int x;
    int y;
    for (int i=0; i<N; i++){
            for (int j=0; j<N; j++){
                cell current_cell=m.cases[i][j];
                carte current_carte=current_cell.carte;
                int current_sens=current_cell.sens;
                if (( (!strcmp(current_carte.name,"null"))&&(current_sens==1))){
                    x=i;
                    y=j; 
                }
            }
    }
    m.cases[x][y]=(cell) {null,-1,NULL};         
}     

/**
*\brief active l'effet de la carte Anne-Laure Ligozat
*\param p un pointeur vers une faction
*\param m la grille
*\param c la dernière carte qui a été retournée 
*\return nothing 
*/

void f_ALL(faction *p,grid m){

   for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cell current_cell=m.cases[i][j];
            carte current_carte=current_cell.carte;
            int current_sens=current_cell.sens;
            if (  (strcmp(current_carte.name,"EcologIIE")||strcmp(current_carte.name,"parcours Sobriété numérique")||strcmp(current_carte.name,"Ecocup")||strcmp(current_carte.name,"Isolation du bâtiment"))&&(current_sens==1)){
                ((*p).nb_point)=((*p).nb_point) + 3;
                supprime_last(m);
            }
        }
   }
}

/**
*\brief active l'effet de la carte Guillaume burel
*\param p un pointeur vers une faction

*\param q un pointeur vers une faction
*\param m la grille
*\return nothing 
*/

void f_ALL(faction *p,faction *q){
    
    if (((*p).nb_point)>=((*q).nb_point)){
        ((*q).nb_point)=((*q).nb_point) + 3;
        ((*p).nb_point)=((*p).nb_point)-3;
    }
}

/**
*\brief active l'effet de la carte Christophe Mouilleron

*\param m la grille
*\return nothing 
*/

void f_CM(grid m){
    int trouve=0;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cell current_cell=m.cases[i][j];
            carte current_carte=current_cell.carte;
            int current_sens=current_cell.sens;
            if (((strcmp(current_carte.name,"Heures supplémentaires")&&(current_sens==1)))){
                trouve=1;
                break;
            }
        }
       if (trouve==1){
           break;
       }
    }
    if (trouve==1){
        for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cell current_cell=m.cases[i][j];
            carte current_carte=current_cell.carte;
            int current_sens=current_cell.sens;
            if (  (!strcmp(current_carte.name,"Christophe Mouilleron")||!strcmp(current_carte.name,"Heures supplémentaires"))&&(current_sens==1)){
                 m.cases[i][j]=(cell) {null,-1,NULL};    
            }
        }
        }
    }
}



                
/**
*\brief active l'effet de la carte Thomas LIM 
*\param p un pointeur vers la faction qui pose la carte
*\param q un pointeur vers la faction adverse
*\param m la grille
*\return nothing 
*/

void f_TM(faction *p,faction* q, grid m){
    int forest;
    int cfise;
    
    //premières boucles sur la grille, on cherche forest
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cell current_cell=m.cases[i][j];
            carte current_carte=current_cell.carte;
            int current_sens=current_cell.sens;
            if (  (strcmp(current_carte.name,"Julien Forest")&&(current_sens==1))){
            forest=1;
            }
            if (  (strcmp(current_carte.name,"FISE")&&(current_sens==1))){
            cfise++;
            }
        }
    }
    if (forest!=1){
        ((*p).nb_point)=((*p).nb_point) +3*cfise;
    
    }
    else{
        ((*q).nb_point)=((*q).nb_point) -cfise;
    }
}

    


/**
*\brief active l'effet de la carte Julien Forest
*\param p un pointeur vers la faction qui pose la carte
*\param m la grille
*\return nothing 
*/
void f_JF(faction *p, grid m){
    int cafe;
    int cfise=0;
    
    //premières boucles sur la grille, on cherche forest
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cell current_cell=m.cases[i][j];
            carte current_carte=current_cell.carte;
            int current_sens=current_cell.sens;
            if (  (strcmp(current_carte.name,"Café")&&(current_sens==1))){
                cafe=1;
            }
            if (  (strcmp(current_carte.name,"FISE")&&(current_sens==1))){
                cfise++;
            }
        }
    }
    if (cafe==1){
        ((*p).nb_point)=((*p).nb_point) +6*cfise;}
}
    
/**
*\brief active l'effet de la carte Dimitri Watel
*\param p un pointeur vers la faction qui pose la carte
*\param m la grille
*\return nothing 
*/
void f_DW(faction *p, grid m){
    int the;
    int count=0;   
    //premières boucles sur la grille, on cherche forest
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cell current_cell=m.cases[i][j];
            carte current_carte=current_cell.carte;
            int current_sens=current_cell.sens;
            if ( (strcmp(current_carte.name,"FISE"))&&(current_sens==1))){
                count++;
            }
            if ( (strcmp(current_carte.name,"FC"))&&(current_sens==1))){
                count++;
            }
            if (  (strcmp(current_carte.name,"Thé")&&(current_sens==1))){
                the=1;
            }
        }
    }
    if (the==1){
        ((*p).nb_point)=((*p).nb_point) +3*count;}
}





    
/**
*\brief active l'effet de la carte Djibril-Aurélien Dembele-Cabot
*\param p un pointeur vers la faction qui pose la carte
*\param m la grille
*\param x l'entier numéro de ligne de la carte
*\return nothing 
*/

void f_DW(faction *p, grid m, int x){
    int count=0;   
    //premières boucles sur la grille, on cherche forest
    for (int j=0; j<N; j++){
        cell current_cell=m.cases[x][j];
        carte current_carte=current_cell.carte;
        int current_sens=current_cell.sens;
        if (current_sens==1){
            count++;
        }
        if (count>=3){
            break;
        }
    }
    if (count>=3){
        ((*p).nb_point)=((*p).nb_point) +3*count;
    }
}
    

/**
*\brief active l'effet de la carte Eric Lejeune
*\param p un pointeur vers la faction qui pose la carte
*\param m la grille
*\param x l'entier numéro de ligne de la carte
*\return nothing 
*/







/**
*\brief active l'effet de la carte Lucienne Pacavé
*\param p un pointeur vers la faction qui pose la carte
*\param m la grille
*\param x l'entier numéro de ligne de la carte
*\param y l'entier numéro de colonne de la carte
*\return nothing 
*/

void f_LP(grid m, int x, int y, faction* p){
    cell current_cell;
    carte current_carte;
    int current_sens; 
    int fisa=0;
    for (int k=0; j<N; j++){
        current_cell=m.cases[x][k];
        current_carte=current_cell.carte;
        current_sens=current_cell.sens;
        if ( (strcmp(current_carte.name,"FISA"))&&(current_sens==1))){
            fisa++;
            break;
        }

        current_cell=m.cases[k][y];
        current_carte=current_cell.carte;
        current_sens=current_cell.sens;
        if ( (strcmp(current_carte.name,"FISA"))&&(current_sens==1))){
            fisa++;
            break;
        }
    }
    /*if (fisa>=1){
        //ajouter 5 pts à p
    }*/
}