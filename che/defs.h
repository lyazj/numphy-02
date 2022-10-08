#pragma once

#define number double
#ifndef POLY_MAX
#define POLY_MAX 6
#endif  /* POLY_MAX */

typedef struct {
  int n;
  /* 4-byte hole for double */
  number a[POLY_MAX + 1];
} poly_t;  /* 32/64 bytes for float/double */

// poly.c
void poly_norm(poly_t *P);
void poly_zero(poly_t *P);
void poly_one(poly_t *P);
int poly_iszero(const poly_t *P);
int poly_equ(const poly_t *P, const poly_t *Q);
int poly_neq(const poly_t *P, const poly_t *Q);
int poly_approx(const poly_t *P, const poly_t *Q, number threshold);
void poly_add(poly_t *P, const poly_t *Q);
void poly_sub(poly_t *P, const poly_t *Q);
int poly_mul(poly_t *P, const poly_t *Q);
void poly_copy(poly_t *P, const poly_t *Q);
number poly_eval(const poly_t *P, number x);
char *poly_str(const poly_t *P, char *buf, int size);
const char *poly_sstr(const poly_t *P);

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif  /* M_PI */

// chebyshev.c
int che_gen(int n, poly_t T[n + 1]);
int che_approx(number *c, int n, const poly_t T[n + 1], number f(number));
