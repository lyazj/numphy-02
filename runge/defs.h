#pragma once

#ifndef POLY_MAX
#define POLY_MAX 20
#endif  /* POLY_MAX */

#include "../che/defs.h"

// intp.c
int intp_l(poly_t *P, int n, const number x[n + 1], const number y[n + 1]);
int intp_n(poly_t *P, int n, const number x[n + 1], const number y[n + 1]);
int intp_v(poly_t *P, int n, const number x[n + 1], const number y[n + 1]);

inline number runge(number x)
{
  x *= x;
  return 1 / (1 + 25 * x);
}
