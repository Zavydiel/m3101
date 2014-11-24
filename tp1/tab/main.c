#include <stdio.h>

#include "tableau.h"

int main(void)
{
  int tab[] = {1, 2, 3, 4, 5};
  int taille = sizeof(tab) / sizeof(tab[0]);
  int tab2[28];
  
  afficher(tab, taille);
  
  printf("%d\n", somme(tab, taille));

  tab[3] = 42;
  afficher(copie_dans(tab2, tab, taille), taille);
  afficher(ajoute_apres(tab2, taille, tab, taille), taille * 2);
  
  return 0;
}
