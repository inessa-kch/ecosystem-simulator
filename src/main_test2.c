#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "ecosys.h"

 #define NB_PROIES 20
#define NB_PREDATEURS 20



// int main(void) {

// srand(time(NULL));
// int i =0;
// Animal *liste_proie=NULL;
// Animal *liste_predateur=NULL;


// for(i=0; i<NB_PROIES; i++){
//   ajouter_animal((rand()%(SIZE_X)), (rand()%(SIZE_Y)),100.0, &liste_proie);
// }

// for(i=0; i<NB_PREDATEURS; i++){
//   ajouter_animal((rand()%(SIZE_X)), (rand()%(SIZE_Y)),100.0, &liste_predateur);
// }


// Animal* AnimalX1=creer_animal((rand()%(SIZE_X)), (rand()%(SIZE_Y)),100.0);
// liste_proie=ajouter_en_tete_animal(liste_proie,AnimalX1);

// Animal* AnimalX2=creer_animal((rand()%(SIZE_X)), (rand()%(SIZE_Y)),100.0);
// liste_predateur=ajouter_en_tete_animal(liste_predateur,AnimalX2);

// printf("le nombre de proies est %d, le nombre de predateurs est %d\n",compte_animal_rec(liste_proie),compte_animal_rec(liste_predateur));
// afficher_ecosys(liste_proie,liste_predateur);


// printf("On enleve une proie et un predateur\n");
//  enlever_animal(&liste_proie,AnimalX1);
//  enlever_animal(&liste_predateur,AnimalX2);

// printf("le nombre de proies est %d, le nombre de predateurs est %d\n",compte_animal_rec(liste_proie),compte_animal_rec(liste_predateur));
// afficher_ecosys(liste_proie,liste_predateur);


//  //liberer_liste_animaux(liste_predateur);
//  //liberer_liste_animaux(liste_proie);

//  /*ecriture lecture ecosys*/
//  ecrire_ecosys("fichier.txt", liste_predateur, liste_proie);

//  Animal* liste_proie2=NULL;
//  Animal* liste_predateur2=NULL;

//  lire_ecosys("fichier.txt",&liste_predateur2,&liste_proie2);

//  printf("Lecture de notre ecosysteme dans de nouvelles listes\n");

//  afficher_ecosys(liste_proie2,liste_predateur2);
 
//  liberer_liste_animaux(liste_predateur);
//  liberer_liste_animaux(liste_proie);
//  liberer_liste_animaux(liste_predateur2);
//  liberer_liste_animaux(liste_proie2);
  

//  return 0;

// }
