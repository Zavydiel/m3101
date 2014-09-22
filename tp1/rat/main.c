#include <stdio.h>
#include "rat.h"

int main() {
  struct rat r1, r2, r3;
  struct rat liste[] = {{2,3}, {5,6}, {2,3}, {1, 4}, {5,0}};
  r1.num = 1;
  r1.den = 5;
  r2.num = 6;
  r2.den = 3;
  

  r3 = rat_produit(r1, r2);

  rat_print(r3);
  
  r3 = rat_somme(r1, r2);
  
  rat_print(r3);
    
  rat_print(rat_plus_petit(liste));
  
  rat_print(rat_simplifie(r3));

  return 1;
}
