#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ecosys.h"


float p_ch_dir=0.01;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-5;

/* PARTIE 1*/
/* Fourni: Part 1, exercice 4, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 4, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
  Animal *na = creer_animal(x,y,energie);
  assert(na);
  assert(na->x >= 0 && na->x <=SIZE_X); 
  assert(na->y >= 0 && na->y <= SIZE_Y);
  *liste_animal = ajouter_en_tete_animal(*liste_animal, na);
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
  Animal *temp = *liste; 
  Animal *prec = NULL;
  if (*liste == NULL) return;

  while((temp) && (temp != animal)){
    prec = temp;
    temp = temp ->suivant;
  }
  if (prec == NULL) {
    *liste = (*liste)->suivant;
  }
  else {
    prec->suivant = temp->suivant;
  }
  
  free(temp);
}

/* A Faire. Part 1, exercice 5, question 2 */
Animal* liberer_liste_animaux(Animal *liste) {
   Animal *temp = NULL;
   while(liste){
     temp = liste;
     liste = liste->suivant;
     free(temp);
   }
  return NULL;
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la=la->suivant;
  }
  return cpt;
}



/* Part 1. Exercice 5, question 1, ATTENTION, ce code est susceptible de contenir des erreurs... */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  Animal *pa=NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; ++i) {
    for (j = 0; j < SIZE_Y; ++j) {
      ecosys[i][j]=' ';
    }
  }

  /* on ajoute les proies */
  pa = liste_proie;
  while (pa) {
    ecosys[pa->x][pa->y] = '*';
    pa=pa->suivant;
  }

  /* on ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
      if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
        ecosys[pa->x][pa->y] = '@';
      } else {
        ecosys[pa->x][pa->y] = 'O';
      }
    pa = pa->suivant;
  }

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) {
    printf("-");
  }  
  printf("+\n");
  for (i = 0; i < SIZE_X; ++i) {
    printf("|");
    for (j = 0; j < SIZE_Y; ++j) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j<SIZE_Y; ++j) {
    printf("-");
  }
  printf("+\n");
  int nbproie=compte_animal_it(liste_proie);
  int nbpred=compte_animal_it(liste_predateur);
  
  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);

}

void afficherliste(Animal *liste){ //fonction test
  if (liste==NULL) printf("liste vide");
  while(liste!=NULL){
    printf("x:%d y:%d E:%.2f | ",liste->x,liste->y, liste->energie);
    liste = liste->suivant;
  }
  printf("\n");
  return;
}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 3*/

void ecrire_ecosys(const char* nom_fichier, Animal* liste_predateurs, Animal* liste_proies){
    FILE* f=fopen(nom_fichier,"w");
    if (f==NULL){
        printf("erreur ouverture fichier\n");
        return;
    }
    fprintf(f,"<proies>\n");
    Animal* tmp1=liste_proies;
    while(tmp1){
        fprintf(f,"x=%d y=%d dir=[%d %d] e=%f\n",tmp1->x,tmp1->y,tmp1->dir[0],tmp1->dir[1],tmp1->energie);
        tmp1=tmp1->suivant;
    }
    fprintf(f,"</proies>\n");

    fprintf(f,"<predateurs>\n");
    Animal* tmp2=liste_predateurs;
    while(tmp2){
        fprintf(f,"x=%d y=%d dir=[%d %d] e=%f\n",tmp2->x,tmp2->y,tmp2->dir[0],tmp2->dir[1],tmp2->energie);
        tmp2=tmp2->suivant;
    }
    fprintf(f,"</predateurs>\n");
    fclose(f);
}


void lire_ecosys(const char *nom_fichier, Animal **liste_predateur, Animal **liste_proie){
    FILE *f = fopen (nom_fichier, "r"); //lecture
    char buff[256];//suffisemment grand pour mettre toute la chaine dedans
    int x_lu, y_lu, dir_lu[2];
    float e_lu;

    if (f==NULL){
        printf ("Erreur ouverture (lecture) : %s\n", nom_fichier);
        return; 
    }

    //proies : 

    fgets(buff, 256,f); // lit "<proies>\n" 
    assert(strncmp(buff,"<proies>\n",8)==0);
    fgets(buff, 256, f); //lecture 1ère proie
    while (strncmp(buff,"</proies>",9)!=0){//pour trouver la fin des proies
        sscanf(buff, "x=%d y=%d dir=[%d %d] e=%f\n", &x_lu, &y_lu, &dir_lu[0], &dir_lu[1], &e_lu);
        
        //création Animal
        Animal *a_lu=creer_animal(x_lu, y_lu, e_lu);
        a_lu->dir[0]=dir_lu[0]; //car creer_animal met dir[0 1] aléatoirement, on doit donc les remettre bien
        a_lu->dir[1]=dir_lu[1];

        //ajout animal dans la liste
        a_lu->suivant=*liste_proie; 
        *liste_proie=a_lu; 

        //preparation iteration suivante
        fgets(buff, 256, f);
    }

    //prédateurs : 

    fgets(buff, 256,f); // lit "<predateur>\n" 
    assert(strncmp(buff,"<predateurs>\n",12)==0); 
    fgets(buff, 256, f); //lecture 1er prédateur
    while (strncmp(buff,"</predateurs>",13)!=0){
        sscanf(buff, "x=%d y=%d dir=[%d %d] e=%f\n", &x_lu, &y_lu, &dir_lu[0], &dir_lu[1], &e_lu); 
        Animal *a_lu=creer_animal(x_lu, y_lu, e_lu);
        a_lu->dir[0]=dir_lu[0]; 
        a_lu->dir[1]=dir_lu[1];
        a_lu->suivant=*liste_predateur; 
        *liste_predateur=a_lu; 
        fgets(buff, 256, f);
    }
    fclose(f);
}

/* Part 2. Exercice 4, question 1 */

void bouger_animaux(Animal *la) {
    while(la){
      if(((float)rand() / (float)RAND_MAX) <= p_ch_dir) {
        la->dir[0] = rand() % 3 - 1; //valeurs entre [-1;1]
        la->dir[1] = rand() % 3 - 1;
      }
        
        la->x = (la->x + la->dir[0] + SIZE_X) % SIZE_X;
        assert(la->x >= 0 && la->x < SIZE_X); //pour tester
        la->y = (la->y + la->dir[1] + SIZE_Y) % SIZE_Y;
        assert(la->y >= 0 && la->y < SIZE_Y);
      la = la->suivant;
  }
}


void bouger_animaux2(Animal *la,int dir0,int dir1) {
    while(la){
      if(((float)rand() / (float)RAND_MAX) < p_ch_dir) {
        la->dir[0] = dir0;
        la->dir[1] = dir1;
      }
        
        la->x = (la->x + la->dir[0] + SIZE_X) % SIZE_X;
        assert(la->x > 0 && la->x < SIZE_X); //pour tester
        la->y = (la->y + la->dir[1] + SIZE_Y) % SIZE_Y;// 
        assert(la->y > 0 && la->y < SIZE_Y);
      la = la->suivant;
  }
}


/* Part 2. Exercice 4, question 2 */
void reproduce(Animal **liste_animal, float p_reproduce){
    Animal *ani=*liste_animal;
    while (ani){
        if((rand()/(float)RAND_MAX)<=p_reproduce){
            ajouter_animal(ani->x, ani->y, ani->energie/2.0, liste_animal);
            ani->energie/=2.0;
        }
        ani=ani->suivant;
    }
}



/* Part 2. Exercice 5, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
    Animal *temp = *liste_proie;
    Animal *prev = NULL;
    bouger_animaux(*liste_proie);
    while(temp){
    temp->energie--;


      //nos proies se nourissent d'herbe
    	if(monde[temp->x][temp->y] > 0.0){
        temp->energie+=(float)monde[temp->x][temp->y];
        monde[temp->x][temp->y] = temps_repousse_herbe;
      }

      //on elimine nos proies epuises
    	if(temp->energie <= 0.0) {
        	if(prev==NULL){
        	 enlever_animal(liste_proie, temp); 
        	 temp=*liste_proie;}
        
        	else{ 
        	enlever_animal(liste_proie, temp); 
        	temp=prev->suivant;}
      	}
        else{ 
        prev=temp; 
        temp=temp->suivant;}
    }
		reproduce(liste_proie, p_reproduce_proie);
}
 

/* Part 2. Exercice 6, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
    Animal *temp=l;
		while(temp){
			if(temp->x==x && temp->y==y) return temp;
			temp=temp->suivant;
		}
  return NULL;
} 

/* Part 2. Exercice 6, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
      Animal *temp = *liste_predateur; 
      Animal *prev = NULL;
    bouger_animaux(*liste_predateur);
    while(temp){
      temp->energie--;
      //nos predateurs mangent les proies
			if(animal_en_XY(*liste_proie, temp->x, temp->y)!=NULL){
        temp->energie+=(animal_en_XY(*liste_proie, temp->x, temp->y))->energie;
        enlever_animal(liste_proie, animal_en_XY(*liste_proie, temp->x, temp->y));
      }
      //on elimine nos predateurs epuises
      if(temp->energie <= 0.0){
        if(prev==NULL){ 
          enlever_animal(liste_predateur, temp); 
          temp=*liste_predateur;
        }
        
        else{ 
          enlever_animal(liste_predateur, temp); 
          temp=prev->suivant;
        }
      }
      else{
      prev=temp; 
      temp=temp->suivant;
      }
    }
		reproduce(liste_predateur, p_reproduce_predateur);
}

/* Part 2. Exercice 7, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
  int i,j;
  for(i=0;i<SIZE_X;i++){
    for(j=0;j<SIZE_Y;j++){
      monde[i][j]++;
    }
  }
  return;
}

