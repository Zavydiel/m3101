#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "patate.h"

int main(int argc, char** argv)
{
  int i, pid, p;
  int pipes[3][2];

  /*int fd = open("toto", O_RDONLY);
  
  lancer_patate(1, 56);
  printf("   <<< lance dans stdout  \n");
  fflush(stdout);

  printf(">>>> %d\n", recevoir_patate(fd));

  close(fd);*/  

  for (i = 0; i < 3; i++)
    {
      pipe(pipes[i]);
      //printf("%d -> %d\n", pipes[i][1], pipes[i][0]);
    }

  //lancer_patate(pipes[0][1], 42);
  //recevoir_patate(pipes[0][0]);
  
  
  p = 0;
  pid = fork();
  if (pid != 0)
    {
      pid = fork();
      if (pid == 0)
	{
	  p = 2;
	}
    }
  else
    {
      p = 1;
    }

  for (i = 0; i < 3; i++)
    {
      if (i != p)
	{
	  close(pipes[i][0]);
	  //printf("%d %d %d : closing %d\n",getpid(), p, i, pipes[i][0]);
	}
      if (i != (p + 1) % 3)
	{
	  close(pipes[i][1]);
	  //printf("%d %d %d : closing %d\n",getpid(), p, i ,pipes[i][1]);		 
	}
      
    }

  sleep(1);

  /*printf("%d %d %d\n", getpid(), p, pid);*/
  if (p == 1)
    {
      lancer_patate(pipes[2][1], obtenir_valeur_aleatoire(10));
    }


  /*if (p == 2)
    {
      recevoir_patate(pipes[2][0]);
      }*/

  //sleep(5);
  
  demarrer_recepteur_patate(pipes[p][0], pipes[(p+1)%3][1]);

  return 0;
}
