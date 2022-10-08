#include "defs.h"
#include <math.h>
#include <stdio.h>

#define NSEG 10000

static number f(number x);
static void chelog(int n);

int main(void)
{
  int i;
  number x = -1;

  for(i = 0; i <= NSEG; ++i)
  {
    printf("f(%.17e) = %.17e\n", x, f(x));
    x += 2.0 / NSEG;
  }
  chelog(4);
  chelog(6);
  return 0;
}

number f(number x)
{
  return log(x * 0.5 + 1.5) / log(2);
}

void chelog(int n)
{
  poly_t T[n + 1];
  number c[n + 1];
  int i;
  number x = -1, y;

  che_gen(n, T);
  che_approx(n, c, T, f);

  fprintf(stderr, "%d:", n);
  for(i = 0; i <= n; ++i)
    fprintf(stderr, " %.17e", c[i]);
  fprintf(stderr, "\n");

  for(i = 0; i <= NSEG; ++i)
  {
    y = che_eval(n, c, x);
    printf("S%d(%.17e) = %.17e\n", n, x, y);
    x += 2.0 / NSEG;
  }
}
