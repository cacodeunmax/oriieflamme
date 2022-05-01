#ifndef CARTE_C
#define CARTE_C

#include "struct.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "struct.c"
#include "constante.h"


char* get_name(carte c){
    return c.name;
}

int get_func(carte c){
    return c.function_number;
}

int equals_carte(carte c, carte v){
    return (strcmp(c.name,v.name)==0 && (c.function_number==v.function_number));
}

int equals(carte c, char* name){
    return strcmp(c.name, name)==0;
}

int empty(carte c){
    return (equals_carte(c, CN));
}

void create_catalogue(carte catalogue[]){
    carte FISE;
    FISE.name="FISE";
    FISE.function_number=1;
    FISE.desc="La faction qui a posé cette carte gagne 1 point DDRS.";

    carte FISA;
    FISA.name="FISA";
    FISA.function_number=2;
    FISA.desc="La faction qui a posé cette carte gagne 2 points DDRS si le nombre de cartes retournées sur le plateau (y compris celle-ci) est pair, et 0 sinon.";

    carte FC;
    FC.name="FC";
    FC.function_number=3;
    FC.desc="La faction qui a posé cette carte gagne 4 points DDRS si au moins une autre carte FC est retournée sur le plateau et 0 sinon";

    carte EcologIIE;
    EcologIIE.name="EcologIIE";
    EcologIIE.function_number=4;
    EcologIIE.desc="La faction qui a posé cette carte gagne 1 point DDRS par carte FISE/FISA/FC retournée.";

    carte lIIEns;
    lIIEns.name="lIIEns";
    lIIEns.function_number=5;
    lIIEns.desc="Prenez toutes les cartes FISE/FISA/FC retournées, retirez les du plateau, mélangez les et reposez les face cachées une par une sur la gauche de la carte la plus en haut à gauche du plateau, dans cet ordre. Les prochaines cartes à être retournées sont ces cartes là.";

    carte ssa;
    ssa.name="Soirée sans alcool";
    ssa.function_number=6;
    ssa.desc="Si au moins une carte alcool est retournée, supprimez toutes les cartes FISE/FISA/FC retournées du plateau. Supprimez ensuite la première et la dernière ligne du plateau. Sinon la faction qui a posé cette carte gagne 5 points DDRS.";

    carte alcool;
    alcool.name="Alcool";
    alcool.function_number=7;
    alcool.desc="Supprimez du plateau toutes les cartes qui touchent cette carte-ci (mais laissez la carte Alcool sur le plateau).";

    carte cafe;
    cafe.name="Café";
    cafe.function_number=8;
    cafe.desc="Supprimez toutes les cartes Thé et Alcool retournées sur le plateau. Si une carte Ecocup est retournée sur le plateau, la faction qui a posé cette carte gagne 1 point DDRS. Sinon elle perd 1 point DDRS.";

    carte the;
    the.name="Thé";
    the.function_number=9;
    the.desc="Supprimez toutes les cartes Café et Alcool retournées sur le plateau. Si une carte Ecocup est retournée sur le plateau, la faction qui a posé cette carte gagne 1 point DDRS. Sinon elle perd 1 point DDRS.";

    carte ecocup;
    ecocup.name="Ecocup";
    ecocup.function_number=10;
    ecocup.desc="Cette carte est sans effet.";

    carte repro;
    repro.name="Reprographie";
    repro.function_number=11;
    repro.desc="La faction adverse de celle qui a posé cette carte perd 1 points DDRS pour chaque paire de cartes retournées et identiques sur le plateau. (S'il y a 3 cartes identiques, cela fait 3 paires).";

    carte idb;
    idb.name="Isolation du bâtiment";
    idb.function_number=12;
    idb.desc="Chaque faction gagne 1 point DDRS par carte non retournée et non supprimée du plateau qu'elle a posée sur le plateau.";

    carte psn;
    psn.name="Parcours sobriété numérique";
    psn.function_number=13;
    psn.desc="Retournez toutes les cartes non retournées les plus à gauche et à droite de chaque ligne, sans appliquer leur effet.";

    carte hs;
    hs.name="Heures supplémentaires";
    hs.function_number=14;
    hs.desc="La faction adverse de celle qui a posé cette carte perd 3 points DDRS par carte Heures supplémentaires retournée sur le plateau (y compris celle-ci).";

    carte kb;
    kb.name="Kahina Bouchma";
    kb.function_number=15;
    kb.desc="Supprimez une carte non retournée du plateau choisie au hasard.";

    carte kg;
    kg.name="Kevin Goilard";
    kg.function_number=16;
    kg.desc="Supprimez une ligne au hasard, la faction qui a posé cette carte gagne 2 points DDRS par carte supprimée ainsi.";

    carte mm;
    mm.name="Massinissa Merabet";
    mm.function_number=17;
    mm.desc="La faction qui a posé cette carte réactive l'effet de la dernière carte retournée avant Massinissa Merabet, en faisant comme elle l'avait posée elle-même, même si ce n'est pas le cas. 	";

    carte vy;
    vy.name="Vitéra Y";
    vy.function_number=18;
    vy.desc="La faction qui a le moins de points DDRS gagne 3 points DDRS.";

    carte js;
    js.name="Jonas Senizergues";
    js.function_number=19;
    js.desc="Supprimez toutes les cartes Heures supplémentaires retournées du plateau.";

    carte fb;
    fb.name="Fetia Bannour";
    fb.function_number=20;
    fb.desc="Si la carte Heures supplémentaires est retournée sur le plateau, supprimez toutes les cartes de la ligne et de la colonne où est posée cette carte (y compris celle-ci). Sinon la faction qui a posé cette carte gagne 1 point DDRS par carte Catherine Dubois, Anne-Laure Ligozat, Guillaume Burel, Christophe Mouilleron, Thomas Lim, Julien Forest et Dimitri Watel retournée sur le plateau.";

    carte cd;
    cd.name="Catherine Dubois";
    cd.function_number=21;
    cd.desc="Supprimez la première et la dernière cartes de la ligne et de la colonne où est posée cette carte.";

    carte all;
    all.name="Anne-Laure Ligozat";
    all.function_number=22;
    all.desc="Pour chaque carte EcologIIE, Ecocup, Isolation du bâtiment et parcours Sobriété numérique retournées, la faction qui a posé cette carte gagne 3 points DDRS et la dernière carte non retournée du plateau est supprimée.";

    carte gb;
    gb.name="Guillaume Burel";
    gb.function_number=23;
    gb.desc="Si la faction adverse de celle qui a posé cette carte a plus de points DDRS, la seconde lui vole 3 points DDRS.";

    carte cm;
    cm.name="Cristophe Mouilleron";
    cm.function_number=24;
    cm.desc="Si la carte Heures supplémentaires est retournée sur le plateau, supprimez toutes les cartes retournées du plateau sauf les cartes Christophe Mouilleron et Heures supplémentaires.";

    carte tl;
    tl.name="Thomas Lim";
    tl.function_number=25;
    tl.desc="Si Julien Forest n'est par retourné sur le plateau, la faction qui a posé cette carte gagne 3 points DDRS par carte FISE retournée sur le plateau. Sinon la faction adverse perd 1 point DDRS par carte FISE retournée sur le plateau.";

    carte jf;
    jf.name="Julien Forest";
    jf.function_number=26;
    jf.desc="La faction qui a posé cette carte gagne 6 points DDRS par carte FISE retournée sur le plateau si au moins une carte Café est retournée sur le plateau.";

    carte dw;
    dw.name="Dimitri Watel";
    dw.function_number=27;
    dw.desc="La faction qui a posé cette carte gagne 3 points DDRS par carte FISA ou FC retournée sur le plateau si au moins une carte Thé est retournée sur le plateau.";

    carte dadc;
    dadc.name="Djibril-Aurélien Dembele-Cabot";
    dadc.function_number=28;
    dadc.desc="S'il y a plus de 3 cartes retournées sur la ligne de cette carte, la faction qui a posé cette carte gagne 5 points DDRS.";

    carte el;
    el.name="Eric Lejeune";
    el.function_number=29;
    el.desc="Prenez au hasard 5 cartes retournées du plateau (ou toutes les cartes retournées du plateau s'il y a moins de 5). Si une de ces cartes est une carte Catherine Dubois, Anne-Laure Ligozat, Guillaume Burel, Christophe Mouilleron, Thomas Lim, Julien Forest ou Dimitri Watel, mélangez les et placez les à gauche de la case la plus à gauche de la première ligne. Les prochaines cartes à être retournées sont ces cartes là. Sinon, supprimez ces cartes du plateau.";

    carte lp;
    lp.name="Lucienne Pacavé";
    lp.function_number=30;
    lp.desc="S'il y a une carte FISA retournée dans la même ligne ou la même colonne que cette carte, la faction qui a posé cette carte gagne 5 points DDRS.";

    carte ks;
    ks.name="Katrin Salhab";
    ks.function_number=31;
    ks.desc="Si les cartes Djibril-Aurélien Djembele-Cabeau, Eric Lejeune et Lucienne Pacavé sont retournées, la faction qui a posé cette carte gagne 10 points DDRS. Sinon, retournez toutes les cartes dans la même ligne de cette carte sans appliquer leurs effets.";

    carte prevel;
    prevel.name="Laurent Prével";
    prevel.function_number=32;
    prevel.desc="Si Laurent Prével est la dernière carte retournée du plateau, la faction qui a posé cette carte gagne la manche, quel que soit le nombre de points DDRS des deux factions";

    for (int i =0; i<4; i++){
        catalogue[i] = FISE;
    }
    for (int i =0; i<4; i++){
        catalogue[4+i] = FISA;
    }
    for (int i =0; i<4; i++){
        catalogue[8+i] = FC;
    }
    for (int i =0; i<2; i++){
        catalogue[12+i] = EcologIIE;
    }
    for (int i =0; i<2; i++){
        catalogue[14+i] = lIIEns;
    }
    catalogue[16]=ssa;
    catalogue[17]=alcool;
    for (int i =0; i<3; i++){
        catalogue[18+i] = cafe;
    }
    for (int i =0; i<3; i++){
        catalogue[21+i] = the;
    }
    catalogue[24]=ecocup;
    catalogue[25]=repro;
    catalogue[26]=idb;
    catalogue[27]=psn;
    catalogue[28]=hs;
    catalogue[29]=kb;
    catalogue[30]=kg;
    catalogue[31]=mm;
    catalogue[32]=vy;
    catalogue[33]=js;
    catalogue[34]=fb;
    catalogue[35]=cd;
    catalogue[36]=all;
    catalogue[37]=gb;
    catalogue[38]=cm;
    catalogue[39]=tl;
    catalogue[40]=jf;
    catalogue[41]=dw;
    catalogue[42]=dadc;
    catalogue[43]=el;
    catalogue[44]=lp;
    catalogue[45]=ks;
    catalogue[46]=prevel;

}

#endif