#include "defs.h"
#include <stdio.h>
#include <math.h>

#define NSEG 1000
#define N      20
#define XMIN -1.0
#define XMAX +1.0
#define XSPAN (XMAX - XMIN)

int main(void)
{
  number c[N][4];
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
  cub_2pp(N, c, x, y, 0, 0);
  for(i = 0; i <= 2*N; ++i)
  {
    char buf[128];
    double r, s;
    t = XSPAN * i / (2*N) + XMIN;
    r = runge(t);
    s = cub_eval(N, c, x, t);
    sprintf(buf, "runge(%+.2f) = %g", t, r);
    fprintf(stderr, "%-28s", buf);
    sprintf(buf, "S%d(%+.2f) = %g", N, t, s);
    fprintf(stderr, "%-28s", buf);
    fprintf(stderr, "diff = %g\n", fabs(s - r));
  }
  for(i = 0; i <= NSEG; ++i)
  {
    t = XSPAN * i / NSEG + XMIN;
    printf("runge(%.17e) = %.17e\n", t, runge(t));
    printf("S%d(%.17e) = %.17e\n", N, t, cub_eval(N, c, x, t));
  }
  return 0;
}
