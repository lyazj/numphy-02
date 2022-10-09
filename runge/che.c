#include "defs.h"
#include <stdio.h>
#include <math.h>

#define NSEG 1000
#define N      20
#define XMIN -1.0
#define XMAX +1.0
#define XSPAN (XMAX - XMIN)

static number f(number x);

int main(void)
{
  poly_t T[N];
  number c[N];
  number t;
  int i;

  che_gen(N - 1, T);
  che_approx(N - 1, c, T, f);
  for(i = 2*N; i >= 0; --i)
  {
    char buf[64];
    double r, s;
    t = cos(i / (2.0*N) * M_PI);
    r = runge(t);
    s = che_eval(N - 1, c, t);
    sprintf(buf, "runge(%+.3f) = %g", t, r);
    fprintf(stderr, "%-28s", buf);
    sprintf(buf, "S19(%+.3f) = %g", t, s);
    fprintf(stderr, "%-28s", buf);
    fprintf(stderr, "diff = %g\n", fabs(s - r));
  }
  for(i = 0; i <= NSEG; ++i)
  {
    t = XSPAN * i / NSEG + XMIN;
    printf("runge(%.17e) = %.17e\n", t, runge(t));
    printf("S19(%.17e) = %.17e\n", t, che_eval(N - 1, c, t));
  }
  return 0;
}

number f(number x)
{
  return runge(x);
}
