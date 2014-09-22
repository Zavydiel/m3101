#include "rat.h"
#include <stdio.h>

struct rat rat_produit(struct rat n1, struct rat n2)
{
  struct rat out;
  out.den = n1.den * n2.den;
  out.num = n1.num * n2.num;
  return out;
}

struct rat rat_somme(struct rat n1, struct rat n2)
{
  struct rat out;
  out.num = n1.num * n2.den + n2.num * n1.den;
  out.den = n1.den * n2.den;
  return out;
}

void rat_print(struct rat n)
{
  printf("%d/%d\n", n.num, n.den);
}

struct rat rat_plus_petit(struct rat list[])
{
  int i = 1;
  struct rat min = list[0];
  while (list[i].den != 0)
    {
      min = rat_min(min, list[i]);
      i++;
    }
  return min;
}

struct rat rat_min(struct rat r1, struct rat r2) 
{
  if (r1.num * r2.den > r2.num * r1.den) 
    return r2;
  return r1;
}

int pgcd(int a, int b)
{
  int p = a, q = b, r;
  while (p%q != 0) 
    {
      r = p%q;
      p = q;
      q = r;
    }
  return r;
}

struct rat rat_simplifie(struct rat r)
{
  int gcd = pgcd(r.num, r.den);
  struct rat out;
  out.num = r.num / gcd;
  out.den = r.den / gcd;
  return out;
}
  
