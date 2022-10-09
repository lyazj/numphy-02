#include "defs.h"

int intp_l(poly_t *P, int n,
    const number x[n + 1], const number y[n + 1])
{
  int i, j;
  poly_t L, Lj;

  if(n > POLY_MAX)
    return -1;
  poly_zero(P);
  for(i = 0; i <= n; ++i)
  {
    L.n = 0;
    L.a[0] = y[i];
    Lj.n = 1;
    for(j = 0; j < i; ++j)
    {
      Lj.a[1] = 1 / (x[i] - x[j]);
      Lj.a[0] = Lj.a[1] * -x[j];
      poly_mul(&L, &Lj);
    }
    for(j = i + 1; j <= n; ++j)
    {
      Lj.a[1] = 1 / (x[i] - x[j]);
      Lj.a[0] = Lj.a[1] * -x[j];
      poly_mul(&L, &Lj);
    }
    poly_add(P, &L);
  }
  return 0;
}

int intp_n(poly_t *P, int n,
    const number x[n + 1], const number y[n + 1])
{
  int i, j;
  poly_t N[n + 1], Ni;
  number a[n + 1], ai;

  if(n > POLY_MAX)
    return -1;
  poly_one(&N[0]);
  a[0] = y[0];
  for(i = 1; i <= n; ++i)
  {
    poly_copy(&N[i], &N[i - 1]);
    Ni.n = 1;
    Ni.a[1] = 1;
    Ni.a[0] = -x[i - 1];
    poly_mul(&N[i], &Ni);
    ai = y[i];
    for(j = 0; j < i; ++j)
      ai -= poly_eval(&N[j], x[i]) * a[j];
    a[i] = ai / poly_eval(&N[i], x[i]);
  }
  poly_zero(P);
  Ni.n = 0;
  for(i = 0; i <= n; ++i)
  {
    Ni.a[0] = a[i];
    poly_mul(&N[i], &Ni);
    poly_add(P, &N[i]);
  }
  return 0;
}

int intp_v(poly_t *P, int n,
    const number x[n + 1], const number y[n + 1])
{
  int i, j;
  poly_t _Q[2][n + 1], *Q[2] = {_Q[0], _Q[1]}, *Qi, Qij;

  if(n > POLY_MAX)
    return -1;
  for(i = 0; i <= n; ++i)
  {
    Q[0][i].n = 0;
    Q[0][i].a[0] = y[i];
  }
  for(i = 1; i <= n; ++i)
  {
    for(j = i; j <= n; ++j)
    {
      Qij.n = 1;
      Qij.a[1] = 1 / (x[j - i] - x[j]);
      Qij.a[0] = Qij.a[1] * -x[j];
      poly_mul(&Qij, &Q[0][j - 1]);
      poly_copy(&Q[1][j], &Qij);
      Qij.n = 1;
      Qij.a[1] = 1 / (x[j] - x[j - i]);
      Qij.a[0] = Qij.a[1] * -x[j - i];
      poly_mul(&Qij, &Q[0][j]);
      poly_add(&Q[1][j], &Qij);
    }
    Qi = Q[0];
    Q[0] = Q[1];
    Q[1] = Qi;
  }
  poly_copy(P, &Q[0][n]);
  return 0;
}
