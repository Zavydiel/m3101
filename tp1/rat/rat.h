struct rat
{
  int num;
  int den;
};

struct rat rat_produit(struct rat n1, struct rat n2);

struct rat rat_somme(struct rat n1, struct rat n2);

void rat_print(struct rat r);

struct rat rat_plus_petit(struct rat list[]);

struct rat rat_min(struct rat r1, struct rat r2);

int pgcd(int a, int b);

struct rat rat_simplifie(struct rat r);
