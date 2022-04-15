#include "struct.h"
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "struct.c"

int equals_carte(carte c, carte v){
    return (strcmp(c.name,v.name)&&(c.function_number==v.function_number));
}


#define N 32
carte null={"null",-1};



void f_fise(faction *p){
    ((*p).nb_point)++;
}

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

//=========================================================================

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


void haut_gauche(grid m,carte c, faction *f){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cell current_cell=m.cases[i][j];
            
            int current_sens=current_cell.sens;
            if (current_sens==1){
                if (i<(N-1)){
                    m.cases[i+1][j]=(cell) {c,0,f};
                    break;}
                if (i==(N-1)){
                    m.cases[0][j+1]=(cell) {c,0,f};
                    break;
                }
            }
        }
    }
}
            


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

void f_alcool(grid m, int x, int y){


    //si on est pas du tout aux bords
    if (  (i!=(N-1) )  && (j!= (N-1) )   ){
    m[i-1][j]=(cell) {null,-1,NULL};
    m[i+1][j-1]=(cell) {null,-1,NULL};
    m[i][j-1]=(cell) {null,-1,NULL};
    m[i][j+1]=(cell) {null,-1,NULL};
    }


    

}