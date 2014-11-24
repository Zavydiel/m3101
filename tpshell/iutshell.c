#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "ligne_commande.h"
#include <sys/types.h>
#include <sys/wait.h>


void affiche_prompt() 
{
  printf("iutshell$ ");
  fflush(stdout);
}

void execute_ligne_commande()
{
  int flag, nb, i, pid;
  
  char ***megaptr = ligne_commande(&flag, &nb);
  
  for (i = 0; i < nb; i++) 
    {
      pid = fork();
      if (pid == 0)
	{
	  execvp(megaptr[i][0], megaptr[i]);
	} 
      else 
	{
	  waitpid(pid, NULL, 0);
	}
    }
  free(megaptr);
}
