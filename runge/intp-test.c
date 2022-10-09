#include "defs.h"
#include <assert.h>
#include <stdio.h>

static void intp_test_l0(void);
static void intp_test_l1(void);
static void intp_test_l2(void);
static void intp_test_n0(void);
static void intp_test_n1(void);
static void intp_test_n2(void);
static void intp_test_v0(void);
static void intp_test_v1(void);
static void intp_test_v2(void);

int main(void)
{
  intp_test_l0();
  intp_test_l1();
  intp_test_l2();
  intp_test_n0();
  intp_test_n1();
  intp_test_n2();
  intp_test_v0();
  intp_test_v1();
  intp_test_v2();
  return 0;
}

void intp_test_l0(void)
{
  poly_t P, Q;

  number x[1] = {2};
  number y[1] = {2};
  intp_l(&P, 0, x, y);
  Q.n = 0;
  Q.a[0] = 2;
  assert(poly_approx(&P, &Q, 1e-10));
}

void intp_test_l1(void)
{
  poly_t P, Q;

  number x[2] = {2, 3};
  number y[2] = {1, 5};
  intp_l(&P, 1, x, y);
  Q.n = 1;
  Q.a[1] = 4;
  Q.a[0] = -7;
  assert(poly_approx(&P, &Q, 1e-10));
}

void intp_test_l2(void)
{
  poly_t P, Q, E;
  char buf[128];

  number x[3] = {2, -3, 5};
  number y[3] = {33, 13, 141};
  intp_l(&P, 2, x, y);
  Q.n = 2;
  Q.a[2] = 4;
  Q.a[1] = 8;
  Q.a[0] = 1;
  fprintf(stderr, "  result: %s\n", poly_str(&P, buf, sizeof buf));
  poly_copy(&E, &P);
  poly_sub(&E, &Q);
  fprintf(stderr, "  error: %s\n", poly_str(&E, buf, sizeof buf));
  assert(poly_approx(&P, &Q, 1e-10));
}

void intp_test_n0(void)
{
  poly_t P, Q;

  number x[1] = {2};
  number y[1] = {2};
  intp_n(&P, 0, x, y);
  Q.n = 0;
  Q.a[0] = 2;
  assert(poly_approx(&P, &Q, 1e-10));
}

void intp_test_n1(void)
{
  poly_t P, Q;

  number x[2] = {2, 3};
  number y[2] = {1, 5};
  intp_n(&P, 1, x, y);
  Q.n = 1;
  Q.a[1] = 4;
  Q.a[0] = -7;
  assert(poly_approx(&P, &Q, 1e-10));
}

void intp_test_n2(void)
{
  poly_t P, Q, E;
  char buf[128];

  number x[3] = {2, -3, 5};
  number y[3] = {33, 13, 141};
  intp_n(&P, 2, x, y);
  Q.n = 2;
  Q.a[2] = 4;
  Q.a[1] = 8;
  Q.a[0] = 1;
  fprintf(stderr, "  result: %s\n", poly_str(&P, buf, sizeof buf));
  poly_copy(&E, &P);
  poly_sub(&E, &Q);
  fprintf(stderr, "  error: %s\n", poly_str(&E, buf, sizeof buf));
  assert(poly_approx(&P, &Q, 1e-10));
}

void intp_test_v0(void)
{
  poly_t P, Q;

  number x[1] = {2};
  number y[1] = {2};
  intp_v(&P, 0, x, y);
  Q.n = 0;
  Q.a[0] = 2;
  assert(poly_approx(&P, &Q, 1e-10));
}

void intp_test_v1(void)
{
  poly_t P, Q;

  number x[2] = {2, 3};
  number y[2] = {1, 5};
  intp_v(&P, 1, x, y);
  Q.n = 1;
  Q.a[1] = 4;
  Q.a[0] = -7;
  assert(poly_approx(&P, &Q, 1e-10));
}

void intp_test_v2(void)
{
  poly_t P, Q, E;
  char buf[128];

  number x[3] = {2, -3, 5};
  number y[3] = {33, 13, 141};
  intp_v(&P, 2, x, y);
  Q.n = 2;
  Q.a[2] = 4;
  Q.a[1] = 8;
  Q.a[0] = 1;
  fprintf(stderr, "  result: %s\n", poly_str(&P, buf, sizeof buf));
  poly_copy(&E, &P);
  poly_sub(&E, &Q);
  fprintf(stderr, "  error: %s\n", poly_str(&E, buf, sizeof buf));
  assert(poly_approx(&P, &Q, 1e-10));
}
