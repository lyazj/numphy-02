#include "defs.h"

#include <string.h>  // to be removed

int cub_2pp(int n, number c[n][4],
    number x[n + 1], number y[n + 1], number ypp0, number yppn)
{
  number d0x[n];
  number d1y[n];
  number d[n];  // d[0] not used
  number l[n];  // l[0] not used
  number u[n];  // u[0] not used
  number M[n + 1];
  int i, r;

  if(n == 0)
    return 0;
  i = 0;
  d0x[i] = x[i + 1] - x[i];
  d1y[i] = (y[i + 1] - y[i]) / d0x[i];
  M[0] = ypp0;
  for(i = 1; i < n; ++i)
  {
    d0x[i] = x[i + 1] - x[i];
    d1y[i] = (y[i + 1] - y[i]) / d0x[i];
    l[i] = d0x[i - 1] / 6;
    d[i] = (d0x[i - 1] + d0x[i]) / 3;
    u[i] = d0x[i] / 6;
    M[i] = d1y[i] - d1y[i - 1];
  }
  M[n] = yppn;
  if(n > 1)
  {
    M[1] -= l[1] * M[0];
    M[n - 1] -= u[n - 1] * M[n];
    r = tdm_tri(n - 1, 1, &d[1], &l[1], &u[1], (void *)&M[1]);
    if(r < n - 1)
      return r;
  }
  for(i = 0; i < n; ++i)
  {
    c[i][0] = -M[i] / (6 * d0x[i]);  // (x - x[i + 1])^3
    c[i][1] = M[i + 1] / (6 * d0x[i]);  // (x - x[i])^3
    c[i][2] = d1y[i] - d0x[i] * (M[i + 1] - M[i]) / 6;  // (x - x[i])
    c[i][3] = y[i] - M[i] * (d0x[i] * d0x[i]) / 6;  // 1
  }
  return n;
}

number cub_eval(int n,
    const number c[n][4], const number x0[n + 1], number x)
{
  int ml, mr, m;
  number xl, xr, xm;

  if(n == 0)
    return 0.0 / 0.0;
  ml = 0;
  mr = n;
  xl = x0[ml];
  xr = x0[mr];
  if(x < xl)
    return 0.0 / 0.0;
  if(x == xl)
    return cub_eval2(c[0], x0[0], x0[1], x);
  if(x > xr)
    return 0.0 / 0.0;
  while(mr != ml + 1)  // xl < x <= xr
  {
    m = (ml + mr) / 2;
    xm = x0[m];
    if(xm < x)
      ml = m;
    else
      mr = m;
  }
  return cub_eval2(c[ml], x0[ml], x0[mr], x);
}

number cub_eval2(const number c[4], number xl, number xr, number x)
{
  number x1 = x - xl;
  number x2 = x - xr;

  return c[0] * (x2*x2*x2) + c[1] * (x1*x1*x1) + c[2] * x1 + c[3];
}
