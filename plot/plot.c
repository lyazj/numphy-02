#include "defs.h"
#include <math.h>
#include <stdio.h>

#define A 0.5
#define N 8
#define NSEG 1000

static number rt(number t);
static number xt(number t);
static number yt(number t);

int main(void)
{
  number t[N + 1];
  number x[N + 1];
  number y[N + 1];
  number xc[N][4];
  number yc[N][4];
  number tt, xtt, ytt;
  int i;

  fprintf(stderr, "NOTE: M_PI = %.13a\n", M_PI);
  for(i = 0; i <= N; ++i)
  {
    t[i] = i * (2 * M_PI) / N;
    x[i] = xt(t[i]);
    y[i] = yt(t[i]);
    fprintf(stderr, "t = %+-23.13ax = %+-23.13ay = %+-21.13a\n", t[i], x[i], y[i]);
  }
  if(cub_2pp(N, xc, t, x, 0, 0) != N)
  {
    fprintf(stderr, "error interpolating t, x\n");
    return 1;
  }
  fprintf(stderr, "xc = lambda t: {\n");
  for(i = 0; i < N; ++i)
  {
    fprintf(stderr, " %.1e %s t <= %.1e:\n", t[i], i == 0 ? "<=" : "< ", t[i + 1]);
    fprintf(stderr, "  %+.1e*(t%+.1e)**3%+.1e*(t%+.1e)**3%+.1e*(t%+.1e)%+.1e,\n",
        xc[i][0], -t[i + 1], xc[i][1], -t[i], xc[i][2], -t[i], xc[i][3]);
  }
  fprintf(stderr, "}[True]\n");
  if(cub_2pp(N, yc, t, y, 0, 0) != N)
  {
    fprintf(stderr, "error interpolating t, y\n");
    return 1;
  }
  fprintf(stderr, "yc = lambda t: {\n");
  for(i = 0; i < N; ++i)
  {
    fprintf(stderr, " %.1e %s t <= %.1e:\n", t[i], i == 0 ? "<=" : "< ", t[i + 1]);
    fprintf(stderr, "  %+.1e*(t%+.1e)**3%+.1e*(t%+.1e)**3%+.1e*(t%+.1e)%+.1e,\n",
        yc[i][0], -t[i + 1], yc[i][1], -t[i], yc[i][2], -t[i], yc[i][3]);
  }
  fprintf(stderr, "}[True]\n");
  for(i = 0; i <= NSEG; ++i)
  {
    tt = i * (2 * M_PI) / NSEG;
    xtt = cub_eval(N, xc, t, tt);
    ytt = cub_eval(N, yc, t, tt);
    printf("rt(%+21.13a) = %+-23.13a%+21.13a\n", tt, xt(tt), yt(tt));
    printf("rc(%+21.13a) = %+-23.13a%+21.13a\n", tt, xtt, ytt);
  }
  return 0;
}

number rt(number t)
{
  return (2*A) * (1 - cos(t));
}

number xt(number t)
{
  return rt(t) * cos(t);
}

number yt(number t)
{
  return rt(t) * sin(t);
}
