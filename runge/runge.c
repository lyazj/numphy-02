#include "defs.h"
#include <stdio.h>

#define NSEG 1000
#define N      20
#define XMIN -1.0
#define XMAX +1.0
#define XSPAN (XMAX - XMIN)

int main(void)
{
  poly_t P;
  number x[N + 1];
  number y[N + 1];
  number t;
  int i;

  for(i = 0; i <= N; ++i)
  {
    t = XSPAN * i / N + XMIN;
    x[i] = t;
    y[i] = runge(t);
  }
  intp_l(&P, N, x, y);
  for(i = 0; i <= 2*N; ++i)
  {
    char buf[64];
    t = XSPAN * i / (2*N) + XMIN;
    sprintf(buf, "runge(%+.2f) = %g", t, runge(t));
    fprintf(stderr, "%-28sS20(%+.2f) = %g\n", buf, t, poly_eval(&P, t));
  }
  for(i = 0; i <= NSEG; ++i)
  {
    t = XSPAN * i / NSEG + XMIN;
    printf("runge(%.17e) = %.17e\n", t, runge(t));
    printf("S20(%.17e) = %.17e\n", t, poly_eval(&P, t));
  }
  return 0;
}
