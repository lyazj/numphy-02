#pragma once

#ifndef POLY_MAX
#define POLY_MAX 20
#endif  /* POLY_MAX */

#include "../che/defs.h"

// intp.c
int intp_l(poly_t *P, int n, const number x[n + 1], const number y[n + 1]);
int intp_n(poly_t *P, int n, const number x[n + 1], const number y[n + 1]);
int intp_v(poly_t *P, int n, const number x[n + 1], const number y[n + 1]);

typedef int solve_t(int n, int m, number A[n][m]);

// tdm.c
solve_t tdm;
int tdm_tri(int n, int m,
    number d[n], number l[n], number u[n], number r[n][m]);

// cubic.c
int cub_2pp(int n, number c[n][4],
    const number x[n + 1], const number y[n + 1], number ypp0, number yppn);
number cub_eval(int n,
    const number c[n][4], const number x0[n + 1], number x);
number cub_eval2(const number c[4], number xl, number xr, number x);

inline number runge(number x)
{
  x *= x;
  return 1 / (1 + 25 * x);
}
