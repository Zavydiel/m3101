#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "patate.h"

int obtenir_valeur_aleatoire(int borne_superieure)
{
  int i, size = sizeof(int);
  unsigned int val = 0;
  long poids = 1;
  int fd = open("/dev/urandom", O_RDONLY);
  char rand[sizeof(int)];

  read(fd, rand, size);

  for (i = 0; i < size; i++)
    {
      val +=  (int) rand[i] * poids;
      poids = poids * 255;
    }

  close(fd);
  
  return val % borne_superieure;
}

void lancer_patate(int out, int valeur)
{
  if (valeur != -1)
    printf("%d: Je lance la patate %d dans %d!\n", getpid(), valeur, out);
  write(out, (void*) &valeur, sizeof(int));
}

int recevoir_patate(int in)
{
  int val;
  char buf[sizeof(int)];

  //printf("reading....%d\n", in);
  
  if (read(in, &buf, sizeof(int)) == -1)
    {
      perror("read");
      return-1;
    }

  //printf("read\n");

  val = (int) *buf;
  if (val != -1)
    printf("%d: J'ai reçu la patate %d depuis %d\n",getpid(), val, in);
  
  return val;
}

void demarrer_recepteur_patate(int in, int out)
{
  int patate;

  //printf("%d\tin: %d, out: %d\n",getpid() , in, out);

  while ((patate = recevoir_patate(in)) > 1)
    {
      patate--;
      printf("%d: patate à %d, je passe au suivant\n", getpid(), patate);
      lancer_patate(out, patate);      
    }

  if (patate == -1)
    {
      printf("%d: A winrar is me\n", getpid());
    }
  else
    {
      printf("%d: Explosion, c'est perdu\n", getpid());
    }
  
  lancer_patate(out, -1);
  sleep(1);
  exit(0);
}
