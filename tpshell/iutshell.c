#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "ligne_commande.h"


void affiche_prompt() 
{
  char* dir;
  char host[21] = "host";
  char* user = getenv("USER");
  dir = getcwd(NULL, 128);
  gethostname(host, 20);

  printf("%s@%s:%s$ ", user, host, dir);
  fflush(stdout);  

  free(dir);
}

void execute_ligne_commande()
{
  int flag, nb, i, pid, status;
  
  char ***megaptr = ligne_commande(&flag, &nb);
  
  if (flag == -1)
    {
      free(megaptr);
      return;
    }

  for (i = 0; i < nb; i++) 
    {
      pid = fork();
      if (pid == 0)
	{
	  status = execvp(megaptr[i][0], megaptr[i]);
	  perror(megaptr[i][0]);
	  exit(status);
	} 
      else 
	{
	  if (flag == 0)
	    waitpid(pid, NULL, 0);
	}
    }
  
  free(megaptr);
}
