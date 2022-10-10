#pragma once

#define number double

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif  /* M_PI */

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
