#include "defs.h"
#include <assert.h>

static void poly_test_norm(void);
static void poly_test_zero(void);
static void poly_test_add(void);
static void poly_test_mul(void);
static void poly_test_eval(void);

int main(void)
{
  poly_test_norm();
  poly_test_zero();
  poly_test_add();
  poly_test_mul();
  poly_test_eval();
  return 0;
}

void poly_test_norm(void)
{
  poly_t P;

  P.n = 0;
  P.a[0] = 0;
  poly_norm(&P);
  assert(P.n == 0 && P.a[0] == 0);

  P.n = 0;
  P.a[0] = 1;
  poly_norm(&P);
  assert(P.n == 0 && P.a[0] == 1);

  P.n = 1;
  P.a[0] = 0;
  P.a[1] = 1;
  poly_norm(&P);
  assert(P.n == 1 && P.a[0] == 0 && P.a[1] == 1);

  P.n = 1;
  P.a[0] = 1;
  P.a[1] = 0;
  poly_norm(&P);
  assert(P.n == 0 && P.a[0] == 1);
}

void poly_test_zero(void)
{
  poly_t P;

  poly_zero(&P);
  assert(P.n == 0 && P.a[0] == 0);
  assert(poly_iszero(&P));
  P.a[0] = 1;
  assert(poly_iszero(&P) == 0);
  P.n = 1;
  P.a[0] = 0;
  P.a[1] = 1;
  assert(poly_iszero(&P) == 0);
}

void poly_test_add(void)
{
  poly_t P, P0, Q;
  
  poly_zero(&P);
  poly_zero(&Q);
  poly_add(&P, &Q);
  assert(poly_iszero(&P));

  P.n = 2;
  P.a[2] = 2;
  P.a[1] = 1;
  P.a[0] = 0;
  poly_copy(&P0, &P);
  poly_zero(&Q);
  poly_add(&P, &Q);
  assert(poly_equ(&P, &P0));

  Q.n = 2;
  Q.a[2] = 2;
  Q.a[1] = 1;
  Q.a[0] = 0;
  poly_zero(&P);
  poly_add(&P, &Q);
  assert(poly_equ(&P, &Q));

  P.n = 2;
  P.a[2] = 2;
  P.a[1] = 1;
  P.a[0] = 0;
  Q.n = 1;
  Q.a[1] = 8;
  Q.a[0] = 4;
  poly_add(&P, &Q);
  Q.n = 2;
  Q.a[2] = 2;
  Q.a[1] = 9;
  Q.a[0] = 4;
  assert(poly_equ(&P, &Q));

  Q.n = 2;
  Q.a[2] = 2;
  Q.a[1] = 1;
  Q.a[0] = 0;
  P.n = 1;
  P.a[1] = 8;
  P.a[0] = 4;
  poly_add(&P, &Q);
  Q.n = 2;
  Q.a[2] = 2;
  Q.a[1] = 9;
  Q.a[0] = 4;
  assert(poly_equ(&P, &Q));

  P.n = 2;
  P.a[2] = 2;
  P.a[1] = 1;
  P.a[0] = 0;
  poly_sub(&P, &P);
  assert(poly_iszero(&P));

  P.n = 2;
  P.a[2] = 2;
  P.a[1] = 1;
  P.a[0] = 0;
  Q.n = 2;
  Q.a[2] = 2;
  Q.a[1] = 0;
  Q.a[0] = 0;
  poly_sub(&P, &Q);
  Q.n = 1;
  Q.a[1] = 1;
  Q.a[0] = 0;
  assert(poly_equ(&P, &Q));
}

void poly_test_mul(void)
{
  poly_t P, Q;

  P.n = 1;
  P.a[1] = 1;
  P.a[0] = 1;
  poly_zero(&Q);
  poly_mul(&P, &Q);
  assert(poly_iszero(&P));

  P.n = 1;
  P.a[1] = 1;
  P.a[0] = 1;
  poly_mul(&P, &P);
  Q.n = 2;
  Q.a[2] = 1;
  Q.a[1] = 2;
  Q.a[0] = 1;
  assert(poly_equ(&P, &Q));

  P.n = 1;
  P.a[1] = 1;
  P.a[0] = -1;
  Q.n = 2;
  Q.a[2] = 1;
  Q.a[1] = 1;
  Q.a[0] = 1;
  poly_mul(&P, &Q);
  Q.n = 3;
  Q.a[3] = 1;
  Q.a[2] = 0;
  Q.a[1] = 0;
  Q.a[0] = -1;
  assert(poly_equ(&P, &Q));
}

void poly_test_eval(void)
{
  poly_t P;
  number x = -2;

  poly_zero(&P);
  assert(poly_eval(&P, x) == 0);

  P.n = 0;
  P.a[0] = 2;
  assert(poly_eval(&P, x) == 2);

  P.n = 2;
  P.a[2] = 8;
  P.a[1] = 4;
  P.a[0] = 2;
  assert(poly_eval(&P, x) == 8 * x*x + 4 * x + 2);
}
