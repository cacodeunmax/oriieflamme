/** 
*\file effet.c
*
*\author Noémie TURMEL
*Ce fichier decrit l'ensemble des fonctions associés à l'activation des effets des cartes
*Il contient les 32 fonctions relatives aux 32 cartes
*/

#ifndef EFFETS_C
#define EFFETS_C

#include "struct.h"
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "constante.h"
#include "carte.h"
#include "faction.h"
#include "plateau.h"


/**
*\brief active la carte fise
*\param p un pointeur vers la faction qui a pose la carte
*\return nothing 
*/
void f_fise(faction *p){
  add_point(p,1);
}

/**
*\brief active la carte fisa
*\param f un pointeur vers la faction qui a pose la carte
*\param p le plateau
*\return nothing 
*/
void f_fisa(faction *f,plateau p){
    int count=0;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            carte current_carte=get_c_carte(p,i,j);
            if (!(empty(current_carte)))
             {
                if (get_c_sens(p,i,j)==1){
                    count++;
                }
            }
    }
    if (count%2==0){
        add_point(f,2);
    }
    }
}




/**
*\brief active la carte fc
*\param  p un pointeur vers la faction qui a pose la carte
*\param pl le plateau
*\return nothing 
*/
void f_fc(faction *p,plateau pl){
    
    int au_moins_1=0;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            carte current_carte=get_c_carte(pl,i,j);

            if (equals(current_carte,"FC"))
            {
                if (get_c_sens(pl,i,j)==1){

                int pt=4;
                add_point(p,pt);
                au_moins_1=1;
                break;}
            }
        }
    if (au_moins_1==1){break;}}
}

/**
*\brief active la carte ecologiie
*\param  p un pointeur vers la faction qui a pose la carte
*\param m le plateau
*\return nothing 
*/
void f_ecologiie(faction *p,plateau m){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            carte current_carte=get_c_carte(m,i,j);
            if (equals(current_carte,"FC")||equals(current_carte,"FISE")||equals(current_carte,"FISA"))
            {
                if ((get_c_sens(m,i,j))==1){
                    add_point(p,1);
                }    
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
*\param p un pointeur vers la faction qui a pose la carte
*\param m le plateau
*\param c une carte
*\return nothing 
*/
void haut_gauche(plateau *m,carte c, faction *f){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
           

            int current_sens=get_c_sens(*m,i,j);
            /*carte current_carte=current_cell.carte;*/
            /* le cas current_sens==1 et i=0 n'est pas possible*/
            if (current_sens==1){
                //m.cases[i-1][j]=(cell) {c,0,f};
                //set_c_carte(*m,f,i-1,j,c);
                put_card(m,c,f,(i-1),j);
                goto END;
            }
        }
    }
    END: ;
}
            

/**
*\brief active la carte liiens
*\param p un pointeur vers la faction qui a pose la carte
*\param m un pointeur vers le plateau
*\return nothing 
*/
void f_liiens(faction *p,plateau *m){

    carte cartes_retirees[HAND_SIZE*2];
    for (int k=0; k<(HAND_SIZE*2); k++){
        cartes_retirees[k]=CN;
    }
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){

            carte current_carte=get_c_carte(*m,i,j);
            int current_sens=get_c_sens(*m,i,j);
            if (  (equals(current_carte,"FC")||equals(current_carte,"FISE")||equals(current_carte,"FISA"))&&(current_sens==1))
            {
                carte cc=current_carte;
                //cell cellule ={null,-1,NULL};
             
                set_c_nulle(*m,i,j);

                for (int k=0; k<(HAND_SIZE*2); k++){

                    if     ( empty(cartes_retirees[k])){
                        cartes_retirees[k]=cc;
                        break;}
                }
            }
        }
    } 
    //a ce moment la de la fonction carte_retirees contient les cartes retirées
    randomize(cartes_retirees,(HAND_SIZE*2)); //on shuffle
    for (int k=0; k<(HAND_SIZE*2); k++){
        carte ccc=cartes_retirees[k];
        haut_gauche(m,ccc,p);
        
    }
}



/**
*\brief active les effets de la carte soirée sans alcool

*\param m le plateau
*\return nothing 
*/
void f_ssa(/*faction p,*/plateau m){
    
    //etape 1
    int oui_alcool=0;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            carte current_carte = get_c_carte(m,i,j);
            if (equals(current_carte,"alcool")){
                oui_alcool=1;
                break;
            }
        }
        if (oui_alcool==1){break;}
    }


    if (oui_alcool==1){
    //etape 2
    //on cherches les cartes, et on cherche aussi l'indice de la première ligne et de la dernière ligne
    int fst=-1;
    int lst=-1;

    for (int i=0; i<(N-1); i++){
        for (int j=0; j<N; j++){
            carte current_carte = get_c_carte(m,i,j);
            int current_sens=get_c_sens(m,i,j);
            if (  ((equals(current_carte,"FC"))||equals(current_carte,"FISE")||equals(current_carte,"FISA"))&&(current_sens==1))
            {
                //cell cellule ={null,-1,NULL};
                //set_c_nulle(m,i,j);
                set_c_nulle(m,i,j);
            }


            current_carte = get_c_carte(m,i,j);
            current_sens=get_c_sens(m,i,j);
            if ((current_sens==1)&&(!(empty(current_carte)))){
                lst=i;
                if (fst==-1){fst=i;}
            }
        }
    }

    //etape 3 

    for (int j=0; j<N; j++){
        set_c_nulle(m,fst,j);
        set_c_nulle(m,lst,j);
        //m.cases[0][j]=(cell) {null,-1,NULL};
        //m.cases[N-1][j]=(cell) {null,-1,NULL};
    }
    }

}
/**
*\brief active les effets de la carte alcool

*\param m le plateau
*\param i entier le numéro de ligne de la carte
*\param j un entier la colonne de la carte
*\return nothing 
*/
void f_alcool(plateau m, int i, int j){


    /* avec l'implémenation qu'on à on est jamais au bord du plateau*/
    /*m.plateau.cases[(i-1)][j]= CLN;
    m.plateau.cases[i+1][j]=CLN;
    m.plateau.cases[i][j-1]=CLN;
    m.plateau.cases[i][j+1]=CLN;*/
    set_c_nulle(m,(i-1),j);
    set_c_nulle(m,(i+1),j);
    set_c_nulle(m,i,(j-1));
    set_c_nulle(m,i,(j+1));
}
/**
*\brief active les effets de la carte café
*\param p une faction
*\param m le plateau
*\return nothing 
*/
void f_cafe(faction *p,plateau m){
    int eco;
   for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            carte current_carte = get_c_carte(m,i,j);
            int current_sens=get_c_sens(m,i,j);
            if (((equals(current_carte,"Thé")||equals(current_carte,"Alcool"))&&(current_sens==1))){
                //set_c_nulle(m,i,j);
                set_c_nulle(m,i,j);
            }
            if ((equals(current_carte,"Ecocup")&&(current_sens==1))){
                add_point(p,1);
                eco++;
            }
        }
    }
    if (eco==0){
        add_point(p,(-1));
    }
}
/**
*\brief active les effets de la carte thé
*\param p un pointeur vers la faction qui a posé la carte
*\param m le plateau
*\return nothing 
*/
void f_the(faction *p,plateau m){
int eco;
   for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            carte current_carte = get_c_carte(m,i,j);
            int current_sens=get_c_sens(m,i,j);
            if (((equals(current_carte,"Café")||equals(current_carte,"Alcool"))&&(current_sens==1))){
                set_c_nulle(m,i,j);
            }
            if ((equals(current_carte,"Ecocup")&&(current_sens==1))){
                add_point(p,1);
                eco++;
            }
        }
    }
    if (eco==0){
        add_point(p,(-1));
    }
}

/**
*\brief active les effets de la carte reprographie
*\param p une faction
*\param m le plateau
*\return nothing 
*/
void f_reprographie(faction p,plateau m){

    /*on initialise le tableau des occurences*/
    int occ[33];
    for (int k;k<33;k++){
        occ[k]=0;
    }

    /*on boucle sur la grille pour récolter le nombre d'occurence de chaque carte*/
    for (int i=0;i<N; i++){
        for (int j=0;i<N; i++){
            carte cc=get_c_carte(m,i,j);
            int sens=get_c_sens(m,i,j);
            if (!empty(cc) && sens){
                int x=get_func(cc);
                occ[x]++;
            }
        }
    }

    /*dénombrement : le nombre de paires d'un ensemble fini à n éléments est égal à n(n – 1)/2  */
    int n;
    faction adv= get_adverse( m, p);
    for (int k;k<33;k++){
        n=occ[k];
        int nb=n*(n-1)/2;
        add_point(&adv,(-nb));
    }

}


/**
*\brief active les effets de la carte isolation
*\param p une faction
*\param m le plateau
*\return nothing 
*/
void f_isolation(plateau m, faction p){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            carte cc=get_c_carte(m,i,j);
            int sens=get_c_sens(m,i,j);
            faction *f= get_c_fac(m,i,j);
            if ((sens==0)&&(!empty(cc))){
                add_point(f,1);
            }
        }
    }
}



/**
*\brief active les effets de la carte sobriété

*\param m le plateau
*\return nothing 
*/
void f_sobriete(plateau m){

    for (int i=0; i<N; i++){
        int jg=-1;
        int jd=-1;

        for (int j=0; j<N; j++){
            carte current_carte=get_c_carte(m,i,j);
            int sens=get_c_sens(m,i,j);
            if( (!(empty(current_carte)))&&(jg=-1)&& !sens ){
                jg=j;
            }
            if(!(empty(current_carte))&& !sens){
                jd=j;
            }
        }
    set_c_sens(m,i,jg,1);
    set_c_sens(m,i,jd,1);
    } 
}

/**
*\brief active les effets de la carte heures supplémentaires
*\param p une faction
*\param m le plateau
*\return nothing 
*/
void f_heure(faction p,plateau m){
    faction adv=get_adverse(m,p);

    for (int i=1; i<N; i++){
        for (int j=0; j<N; j++){
            carte current_carte = get_c_carte(m,i,j);
            int current_sens=get_c_sens(m,i,j);
            if ((equals(current_carte,"Heures supplémentaires")&&(current_sens==1))){
                add_point(&adv,(-3));
            }
        }
    }
}

/**
*\brief returns a pseudo-random value between 0 and max included
*\param p une faction
*\param m le plateau
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
*\param p une faction
*\param m le plateau
*\return nothing 
*/
void f_KB(faction p,plateau m){
    int i=0;
    int j=0;
    int current_sens=1;
    int var=1;

    while ((current_sens==0)||(var==0)){
        i =rand_up_to(N-1);
        j=rand_up_to(N-1);
        carte current_carte=get_c_carte(m,i,j);
        current_sens=get_c_sens(m,i,j);
        var=empty(current_carte);
    }
    if ((current_sens==1)&&(!(var)))
    {
        set_c_nulle(m,i,j);
    }
}
;

/**
*\brief active les effets de la carte Kevin Goilard
*\param p un pointeur vers une faction
*\param m le plateau
*\return nothing 
*/
void f_KG(faction *p,plateau m){
    int count=0;

    while(count==0){
        int i =rand_up_to(N-1);
        for (int j=0; j<N; j++){

            carte current_carte = get_c_carte(m,i,j);
            if (!(empty(current_carte))){
                count++;
                set_c_nulle(m,i,j);
            }
        }
    }

    add_point(p,(-2*count));
}



/**
*\brief active l'effet de la carte Merabet 
*\param p une faction
*\param m le plateau

*\return nothing 
*/
void f_MM(faction p,plateau m){}





/**
*\brief active l'effet de la carte Vitera Y
*\param p une faction
*\param m le plateau
*\return nothing 
*/

void f_VY(faction p,plateau m){
    faction q=get_adverse(m, p);
    if (get_point(p)>get_point(q)){
        add_point(&q,3);

    }
    /* si les 2 factions ont le meme nb de points personne n'en gagne avec cette carte*/
    if (get_point(p)<get_point(q)){
        add_point(&p,3);
    }
}


/**
*\brief active l'effet de la carte Jonas Senizergues
*\param p une faction
*\param m le plateau

*\return nothing 
*/

void f_JS(faction p,plateau m){

   for (int i=1; i<N; i++){
        for (int j=0; j<N; j++){
            carte current_carte = get_c_carte(m,i,j);
            int current_sens=get_c_sens(m,i,j);
            if (((equals(current_carte,"Heures supplémentaires")&&(current_sens==1)))){
                set_c_nulle(m,i,j);
            }
        }
   }
}






/**
*\brief active l'effet de la carte Fetia Bannour
*\param p une faction
*\param m le plateau
*\return nothing 
*/

void f_FB(faction p,plateau m){

   for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            carte current_carte = get_c_carte(m,i,j);
            int current_sens=get_c_sens(m,i,j);
            if (((equals(current_carte,"Heures supplémentaires")&&(current_sens==1)))){
                
                for (int k=0; k<N;k++){
                    set_c_nulle(m,i,k);
                    set_c_nulle(m,k,j);
                }
            }
        }
   }
}




/**
*\brief active l'effet de la carte Catherine Dubois
*\param p une faction
*\param m le plateau
*\return nothing 
*/

void f_CD(faction p,plateau m, int i, int j){
    int il=i;
    int jl;
    int ic;
    int jc=j;
    for (int k=0; i<N; i++){
        
        carte current_carte=get_c_carte(m,i,k);
        int current_sens=get_c_sens(m,i,k);
        if (( (!empty(current_carte))&&(current_sens==1))){
            jl=k;
        }
       
        current_carte=get_c_carte(m,k,j);
        current_sens=get_c_sens(m,k,j);
        if (( (!empty(current_carte))&&(current_sens==1))){
            ic=k;
  
        }
    }
    //m.cases[ic][jc]=(cell) {null,-1,NULL};
    //m.cases[il][jl]=(cell) {null,-1,NULL};
    set_c_nulle(m,ic,jc);
    set_c_nulle(m,il,jl);

}

        


void supprime_last(plateau m){
    int x;
    int y;
    for (int i=0; i<N; i++){
            for (int j=0; j<N; j++){
               carte current_carte=get_c_carte(m,i,j); 
               int current_sens=get_c_sens(m,i,j);
                if (( (!empty(current_carte))&&(current_sens==1))){
                    x=i;
                    y=j; 
                }
            }
    }
    set_c_nulle(m,x,y);       
}     

/**
*\brief active l'effet de la carte Anne-Laure Ligozat
*\param p une faction
*\param m le plateau

*\return nothing 
*/

void f_ALL(faction *p,plateau m){

   for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            carte current_carte = get_c_carte(m,i,j);
            int current_sens=get_c_sens(m,i,j);
            if (  (equals(current_carte,"EcologIIE")||equals(current_carte,"parcours Sobriété numérique")||equals(current_carte,"Ecocup")||equals(current_carte,"Isolation du bâtiment"))&&(current_sens==1)){
               add_point(p,3);
                supprime_last(m);
            }
        }
   }
}

/**
*\brief active l'effet de la carte Guillaume burel
*\param p une faction
*\param m le plateau
*\return nothing 
*/

void f_GB(faction p, plateau m){
    faction q=get_adverse(m, p);
    if (get_point(p)>=get_point(q)){
        add_point(&p,3);
        add_point(&q,(-3));
    }
}

/**
*\brief active l'effet de la carte Christophe Mouilleron

*\param m le plateau
*\return nothing 
*/

void f_CM(plateau m){
    int trouve=0;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            carte current_carte = get_c_carte(m,i,j);
            int current_sens=get_c_sens(m,i,j);
            if (((equals(current_carte,"Heures supplémentaires")&&(current_sens==1)))){
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
            carte current_carte = get_c_carte(m,i,j);
            int current_sens=get_c_sens(m,i,j);
            if (  (!equals(current_carte,"Christophe Mouilleron")||!equals(current_carte,"Heures supplémentaires"))&&(current_sens==1)){
                 set_c_nulle(m,i,j);    
            }
        }
        }
    }
}



                
/**
*\brief active l'effet de la carte Thomas LIM 
*\param p un pointeur vers la faction qui pose la carte
*\param q un pointeur vers la faction adverse
*\param m le plateau
*\return nothing 
*/

void f_TM(faction *p, plateau m){
    int forest;
    int cfise;
    faction q=get_adverse(m, *p);
    
    //premières boucles sur le plateau, on cherche forest
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            carte current_carte = get_c_carte(m,i,j);
            int current_sens=get_c_sens(m,i,j);
            if (  (equals(current_carte,"Julien Forest")&&(current_sens==1))){
            forest=1;
            }
            if (  (equals(current_carte,"FISE")&&(current_sens==1))){
            cfise++;
            }
        }
    }
    if (forest!=1){
        //((p).nb_point)=((p).nb_point) +3*cfise;
        add_point(p,(3*cfise));
    }
    else{
        add_point(&q,(-cfise));
    }
}

    


/**
*\brief active l'effet de la carte Julien Forest
*\param p un pointeur vers la faction qui pose la carte
*\param m le plateau
*\return nothing 
*/
void f_JF(faction *p, plateau m){
    int cafe=0;
    int cfise=0;
    
    //premières boucles sur le plateau, on cherche forest
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            carte current_carte = get_c_carte(m,i,j);
            int current_sens=get_c_sens(m,i,j);
            if (  (equals(current_carte,"Café")&&(current_sens==1))){
                cafe=1;
            }
            if (  (equals(current_carte,"FISE")&&(current_sens==1))){
                cfise++;
            }
        }
    }
    if (cafe==1){
        add_point(p,(6*cfise));
    }
}
    
/**
*\brief active l'effet de la carte Dimitri Watel
*\param p un pointeur vers la faction qui pose la carte
*\param m le plateau
*\return nothing 
*/
void f_DW(faction *p, plateau m){
    int the;
    int count=0;   
    //premières boucles sur le plateau, on cherche forest
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            carte current_carte = get_c_carte(m,i,j);
            int current_sens=get_c_sens(m,i,j);
            if ( (equals(current_carte,"FISE"))&&(current_sens==1)){
                count++;
            }
            if ( (equals(current_carte,"FC"))&&(current_sens==1)){
                count++;
            }
            if (  (equals(current_carte,"Thé"))&&(current_sens==1)){
                the=1;
            }
        }
    }
    if (the==1){
        add_point(p,(3*count));
    }
}





    
/**
*\brief active l'effet de la carte Djibril-Aurélien Dembele-Cabot
*\param p un pointeur vers la faction qui pose la carte
*\param m le plateau
*\param x l'entier numéro de ligne de la carte
*\return nothing 
*/

void f_DADC(faction *p, plateau m, int x){
    int count=0;   
    //premières boucles sur le plateau, on cherche forest
    for (int j=0; j<N; j++){
    
        carte current_carte=get_c_carte(m,x,j);
        int current_sens=get_c_sens(m,x,j);
        if (current_sens && !empty(current_carte)){
            count++;
        }
        if (count>=3){
            break;
        }
    }
    if (count>=3){
        add_point(p,(3*count));
    }
}
    

/**
*\brief active l'effet de la carte Eric Lejeune
*\param p un pointeur vers la faction qui pose la carte
*\param m le plateau
*\param x l'entier numéro de ligne de la carte
*\return nothing 
*/
void f_EL(){

}





/**
*\brief active l'effet de la carte Lucienne Pacavé
*\param p un pointeur vers la faction qui pose la carte
*\param m le plateau
*\param x l'entier numéro de ligne de la carte
*\param y l'entier numéro de colonne de la carte
*\return nothing 
*/

void f_LP(plateau m, int x, int y, faction *p){

    carte current_carte;
    int current_sens; 
    int fisa=0;
    for (int k=0; k<N; k++){
        
        current_carte=get_c_carte(m,x,k);
        current_sens=get_c_sens(m,x,k);
        if ( (equals(current_carte,"FISA"))&&(current_sens==1)){
            fisa++;
            break;
        }

         current_carte=get_c_carte(m,k,y);
        current_sens=get_c_sens(m,y,k);
        if ( (equals(current_carte,"FISA"))&&(current_sens==1)){
            fisa++;
            break;
        }
    }
    if (fisa>=1){
        add_point(p,5);
    }
}


/**
*\brief active l'effet de la carte Katrin Salhab
*\param p un pointeur vers la faction qui pose la carte
*\param m le plateau
*\param x l'entier numéro de ligne de la carte

*\return nothing 
*/

void f_KS(faction *p, plateau m, int x){

    int DADC=0;
    int EL=0;
    int LP=0;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            carte cc=get_c_carte(m,i,j);
            int sens=get_c_sens(m,i,j);
            if (equals(cc,"Djibril-Aurélien Djembele-Cabeau")&&(sens==1)){
                DADC=1;
            }
            if (equals(cc,"Lucienne Pacavé")&&(sens==1)){
                LP=1;
            }
            if (equals(cc,"Eric Lejeune")&&(sens==1)){
                EL=1;
            }
            if (DADC+EL+LP==3){break;}
        }
    if (DADC+EL+LP==3){break;}
    }
    if (DADC+EL+LP==3){add_point(p,10);}
    else{
        for(int k=0; k<N;k++){
            set_c_nulle(m,x,k);
        }
    }
}




/**
*\brief active l'effet de la carte Laurent Prevel
*\param p un pointeur vers la faction qui pose la carte
*\param m le plateau

*\return nothing 
*/

void f_PREVEL(faction *p, plateau m){
    //on va d'abord vérifié si PREVEL elle la dernière carte qui est retournée
    int last=1;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            carte cc=get_c_carte(m,i,j);
            int sens=get_c_sens(m,i,j);
            if((!empty(cc))&&(sens==0)){
                last=0;
                break;
            }
        }
    if (last==0){break;}
    }

    if(last==1){ //cad Laurent prevrel est bien la dernière carte qui a été retournée
        set_victory(p);
        prevel = 1;
    }
}






/**
*\brief active l'effet de la carte c
*\param p un pointeur vers la faction qui pose la carte
*\param m le plateau
*\param x l'entier numéro de ligne de la carte
*\param y l'entier numéro de colonne de la carte
*\return nothing 
*/
void active(carte c, faction* p, plateau* m,int i, int j){
    int n=get_func(c);
    switch(n)
    {
        case 1:
        f_fise(p);
        break;
        case 2:
        f_fisa(p,*m);
        break;   
        case 3:
        f_fc(p,*m);
        break;
        case 4: 
        f_ecologiie(p,*m);
        break;
        
        case 5:
        f_liiens(p,m);
        break;
        case 6 :
        f_ssa(*m);
        break;
        case 7 :
        f_alcool(*m,i,j);
        break;
        case 8 :
        f_cafe(p,*m);
        break;
        
        case 9 : 
        f_the(p,*m);
        break;
        
        case 10 : ; //ecocup
        break;
        case 11: 
        f_reprographie(*p,*m);
        break;
        case 12 : 
        f_isolation(*m, *p);
        break;
        case 13 :
        f_sobriete(*m);
        break;
        case 14: 
        f_heure(*p,*m);
        break;
        case 15: f_KB(*p,*m);
        break;
        case 16 :
        f_KG(p,*m);
        break;
        case 17:
        f_MM(*p,*m,c);
        break;
        case 18 :
        f_VY(*p,*m);
        break;
        case 19: 
        f_JS(*p,*m);
        break;

        case 20:
        f_FB(*p,*m);
        break;
        case 21: 
        f_CD(*p,*m,i,j);
        break;
        case 22:
         f_ALL(p,*m);
        break;
        case 23:
         f_GB(*p, *m);
        break;
        case 24:
         f_CM(*m);
        break;
        case 25:
         f_TM(p,*m);
        break;
        case 26:
         f_JS(*p,*m);
        break;
        case 27:
         f_DW(p,*m);
        break;
        case 28:
         f_DADC(p,*m,i);
        break;
        case 29:
         f_EL();
        break;
        case 30:
        f_LP(*m,i,j,p);
        break;
        case 31:
         f_KS(p,*m,i);
        break;
        case 32:
         f_PREVEL(p,*m);
        break;
        default : ;
    }



}

#endif