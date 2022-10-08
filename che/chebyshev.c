#include "defs.h"
#include <math.h>

int che_gen(int n, poly_t T[n + 1])
{
  int i;
  poly_t p_2x;

  if(n > POLY_MAX)
    return -1;

  // T[0] = 1
  T[0].n = 0;
  T[0].a[0] = 1;
  if(n <= 0)
    return 0;

  // T[1] = x
  T[1].n = 1;
  T[1].a[0] = 0;
  T[1].a[1] = 1;
  if(n <= 1)
    return 0;

  // p_2x = 2*x
  p_2x.n = 1;
  p_2x.a[0] = 0;
  p_2x.a[1] = 2;

  // T[i] = T[i - 1] * p_2x - T[i - 2]
  for(i = 2; i <= n; ++i)
  {
    poly_copy(&T[i], &T[i - 1]);
    poly_mul(&T[i], &p_2x);
    poly_sub(&T[i], &T[i - 2]);
  }
  return 0;
}

int che_approx(int n, number c[n + 1], const poly_t T[n + 1], number f(number))
{
  number x_step = M_PI / (n + 1);
  number x_base = x_step / 2;
  number x[n + 1];
  number y[n + 1];
  number t, tx;
  int i, j;

  if(n > POLY_MAX)
    return -1;

  t = x_base;
  for(i = 0; i <= n; ++i)
  {
    tx = cos(t);
    x[i] = tx;     // x[i] = M_PI / (n + 1) * (1/2 + i)
    y[i] = f(tx);  // y[i] = f(x[i])
    t += x_step;
  }

  for(i = 0; i <= n; ++i)
  {
    t = 0;
    for(j = 0; j <= n; ++j)
      t += poly_eval(&T[i], x[j]) * y[j];
    c[i] = t * (2 - !i) / (n + 1);
  }
  return 0;
}

number che_eval(int n, const number c[n + 1], number x)
{
  number T0, T1, T2, y;
  int i;

  if(n <= 0)
    return c[0];
  if(n <= 1)
    return c[0] + c[1] * x;

  T0 = 1;
  T1 = x;
  y = c[0] + c[1] * x;
  for(i = 2; i <= n; ++i)
  {
    T2 = 2 * x * T1 - T0;
    y += c[i] * T2;
    T0 = T1;
    T1 = T2;
  }
  return y;
}
