#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "ligne_commande.h"
#include "iutshell.h"


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

int lance_commande(int in, int out, char *com, char ** argv)
{
  int pid, status;

  pid = fork();
  if (pid == 0)
    {
      if (in != 0)
	{
	  if (close(0) < 0) 
	    {
	      perror("redirection de l'entree(1): ");
	      return -1;
	    }
	  if ((dup(in) == -1))
	    {
	      perror("redirection de l'entree(2): ");
	      return -1;
	    }
	}
      if (out != 1)
	{
	  if (close(1) < 0 || dup(out) < 0)
	    {
	  perror("redirection de la sortie: ");
	  return -1;
	    }
	}
      
      status = execvp(com, argv);
      perror(com);
      exit(status);
    } 
  else 
    {
      /*if (flag == 0)
	waitpid(pid, NULL, 0);*/
      if (in != 0)
	close(in);
      if (out != 1)
	close(out);
    }

  return pid;
}

void execute_ligne_commande()
{
  int flag, nb, i;
  int in, out;
  int pipefd[2] = {0, 1};
  int sin = dup(0);
  int sout = dup(1);
  
  char ***megaptr = ligne_commande(&flag, &nb);
  
  /*printf("in: %d; out: %d\n", sin, sout);*/

  if (flag == -1)
    {
      free(megaptr);
      return;
    }

  for (i = 0; i < nb; i++) 
    {
      in = sin;
      out = sout;

      if (i != 0)
	  in = pipefd[0];
     
      if (nb > 1 && i != nb - 1) {
	pipe(pipefd);
      }

      if (i != nb - 1)
	out = pipefd[1];

      /*printf("nb: %d; in: %d; out: %d, pipe: %d %d\n", i, in, out, pipefd[1], pipefd[0]);*/

      lance_commande(in, out, megaptr[i][0], megaptr[i]);
    }

  if (flag == 0) {
    for (i = 0; i < nb; i++) 
      wait(0);
  }
    

  /*close(0);
  dup(sin);
  close(1);
  dup(sout);*/
  
  free(megaptr);
}
