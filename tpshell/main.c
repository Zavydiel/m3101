#include "iutshell.h"
#include <stdio.h>

int main() 
{
  while (1)
    {
      affiche_prompt();

      execute_ligne_commande();
    }
  
  printf("\n");
  return 0;  
}
