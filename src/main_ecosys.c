#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"



#define NB_PROIES 30
#define NB_PREDATEURS 30
#define T_WAIT 200000

#define NRJ_PROIES 50.0
#define NRJ_PREDATEURS 100.0


/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
//float p_ch_dir=0.01;
//float p_reproduce_proie=0.4;
//float p_reproduce_predateur=0.5;
//int temps_repousse_herbe=-5;


int main(void) {
  srand(time(NULL));

  FILE *fp=fopen("Evol_Pop.txt", "w");
  if(!fp) {printf("File can't be opened.\n"); return 1;}

/* Part 2. Exercice 7, question 2 */
int herbe[SIZE_X][SIZE_Y];
  int i,j;
  for(i=0;i<SIZE_X;i++){
    for(j=0;j<SIZE_Y;j++){
      herbe[i][j] = 0;
    }
  }

  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;
  

  for (i=0;i<NB_PROIES;i++){ // création des proies
    ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y, NRJ_PROIES, &liste_proie);
  }

  for (i=0;i<NB_PREDATEURS;i++){ // création des prédateurs
    ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y, NRJ_PREDATEURS, &liste_predateur);
  }

  //afficherliste(liste_proie); 
  //afficherliste(liste_predateur);
  //afficher_ecosys(liste_proie,liste_predateur);

  /*EXERCICE 5-6*/
  j=0;
  while(j<100 && (liste_proie!=NULL && liste_predateur!=NULL)) {
    j++;
    fprintf(fp,"%d %d %d\n", j, compte_animal_rec(liste_proie), compte_animal_rec(liste_predateur));
    afficher_ecosys(liste_proie,liste_predateur);
    printf("iterations numeros %d\n",j);
    rafraichir_monde(herbe);
    rafraichir_proies(&liste_proie, herbe);
    rafraichir_predateurs(&liste_predateur, &liste_proie);
    clear_screen();
    usleep(T_WAIT);
  }
printf("etat final\n");
afficher_ecosys(liste_proie,liste_predateur);


  /*EXERCICE 4*/
  
  /*bouger animaux
  Animal* test_animal=
  bouger_animaux2(a4,-1,1);
  bouger_animaux2(a8,1,1);
  bouger_animaux(liste_proie);
  bouger_animaux(liste_predateur);*/

  /*reproduce animaux
  reproduce(&liste_proie,p_reproduce_proie);
  reproduce(&liste_predateur,p_reproduce_predateur);*/

  fclose(fp);
  liberer_liste_animaux(liste_proie);
  liberer_liste_animaux(liste_predateur);
  return 0;
 }
