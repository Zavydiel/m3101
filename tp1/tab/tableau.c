#include <stdio.h>

void afficher(int liste[], int taille) 
{
  int i;
  for(i = 0; i < taille; i++) {
    printf("%d ", liste[i]);
  }
  printf("\n");
}

int somme (int liste[], int taille)
{
  int i, s = 0;
  for(i = 0; i < taille; i++) {
    s = s + liste[i];
  }
  return s;
}

int *copie_dans(int dest[], int src[], int taille)
{
  int i;
  for(i = 0; i < taille; i++) {
    dest[i] = src[i];
  }
  return dest;
}

int *ajoute_apres(int dest[], int taille_dest, int src[], int taille_src)
{
  int i;
  for(i = 0; i < taille_src; i++) {
    dest[taille_dest + i] = src[i];
  }
  return dest;
}
