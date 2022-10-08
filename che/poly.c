#include "defs.h"
#include <math.h>
#include <stdio.h>

void poly_norm(poly_t *P)
{
  int n = P->n;

  while(n > 0 && P->a[n] == 0)
    --n;
  P->n = n;
}

void poly_zero(poly_t *P)
{
  P->n = 0;
  P->a[0] = 0;
}

void poly_one(poly_t *P)
{
  P->n = 0;
  P->a[0] = 1;
}

int poly_equ(const poly_t *P, const poly_t *Q)
{
  int i, n = P->n;

  if(Q->n != n)
    return 0;
  for(i = 0; i <= n; ++i)
    if((P->a[i] == Q->a[i]) == 0)
      return 0;
  return 1;
}

int poly_neq(const poly_t *P, const poly_t *Q)
{
  int i, n = P->n;

  if(Q->n != n)
    return 1;
  for(i = 0; i <= n; ++i)
    if(P->a[i] != Q->a[i])
      return 1;
  return 0;
}

int poly_approx(const poly_t *P, const poly_t *Q, number threshold)
{
  int i, n = P->n;

  if(Q->n != n)
    return 0;
  if(threshold < 0)
    threshold = 0;
  for(i = 0; i <= n; ++i)
    if(fabs(P->a[i] - Q->a[i]) > threshold)
      return 0;
  return 1;
}

int poly_iszero(const poly_t *P)
{
  return P->n == 0 && P->a[0] == 0;
}

void poly_add(poly_t *P, const poly_t *Q)
{
  int i, nP = P->n, nQ = Q->n;

  if(nP > nQ)
  {
    for(i = 0; i <= nQ; ++i)
      P->a[i] += Q->a[i];
  }
  else if(nP == nQ)
  {
    for(i = 0; i <= nQ; ++i)
      P->a[i] += Q->a[i];
    poly_norm(P);
  }
  else
  {
    for(i = 0; i <= nP; ++i)
      P->a[i] += Q->a[i];
    for(; i <= nQ; ++i)
      P->a[i] = Q->a[i];
    P->n = nQ;
  }
}

void poly_sub(poly_t *P, const poly_t *Q)
{
  int i, nP = P->n, nQ = Q->n;

  if(nP > nQ)
  {
    for(i = 0; i <= nQ; ++i)
      P->a[i] -= Q->a[i];
  }
  else if(nP == nQ)
  {
    for(i = 0; i <= nQ; ++i)
      P->a[i] -= Q->a[i];
    poly_norm(P);
  }
  else
  {
    for(i = 0; i <= nP; ++i)
      P->a[i] -= Q->a[i];
    for(; i <= nQ; ++i)
      P->a[i] = -Q->a[i];
    P->n = nQ;
  }
}

int poly_mul(poly_t *P, const poly_t *Q)
{
  int i, j, nP = P->n, nQ = Q->n, n = nP + nQ;
  poly_t PQ;

  if(poly_iszero(P) || poly_iszero(Q))
  {
    poly_zero(P);
    return 0;
  }
  if(n > POLY_MAX)
    return -1;
  PQ.n = n;
  for(i = 0; i <= n; ++i)
    PQ.a[i] = 0;
  for(i = 0; i <= nP; ++i)
    for(j = 0; j <= nQ; ++j)
      PQ.a[i + j] += P->a[i] * Q->a[j];
  poly_norm(&PQ);  /* NOTE: underflow might occur */
  poly_copy(P, &PQ);
  return 0;
}

void poly_copy(poly_t *P, const poly_t *Q)
{
  int i, n = Q->n;

  P->n = n;
  for(i = 0; i <= n; ++i)
    P->a[i] = Q->a[i];
}

number poly_eval(const poly_t *P, number x)
{
  int i, n = P->n;
  number xi = x, y = P->a[0];

  for(i = 1; i <= n; ++i)
  {
    y += P->a[i] * xi;
    xi *= x;
  }
  return y;
}

char *poly_str(const poly_t *P, char *buf, int size)
{
  int i, n = P->n;
  char *p = buf;

  for(i = n; i > 1; --i)
  {
    if(P->a[i] == 0)
      continue;
    n = snprintf(p, size, "%s%gx^%d", p == buf ? "" : " + ", P->a[i], i);
    if(n < 0  /* see 'man snprintf' NOTES: glibc < 2.0.6 */
        || n >= size)
      return NULL;
    size -= n;
    p += n;
  }
  if(i == 1 && P->a[i] != 0)
  {
    n = snprintf(p, size, "%s%gx", p == buf ? "" : " + ", P->a[i]);
    if(n < 0 || n >= size)
      return NULL;
    size -= n;
    p += n;
  }
  if(P->a[0] != 0 || p == buf)
  {
    n = snprintf(p, size, "%s%g", p == buf ? "" : " + ", P->a[0]);
    if(n < 0 || n >= size)
      return NULL;
  }
  return buf;
}

const char *poly_sstr(const poly_t *P)
{
  static char buf[BUFSIZ];

  return poly_str(P, buf, sizeof buf);
}
