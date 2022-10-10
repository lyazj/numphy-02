#include "defs.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>

static void tdm_test_1(void);
static void tdm_test_2(void);
static void tdm_tri_test_1(void);
static void tdm_tri_test_2(void);

int main(void)
{
  tdm_test_1();
  tdm_test_2();
  tdm_tri_test_1();
  tdm_tri_test_2();
  return 0;
}

void tdm_test_1(void)
{
  number A[2][3] = {
    {1, 2, 0},
    {3, 1, 5},
  };
  int i;

  tdm(2, 3, A);
  for(i = 0; i < 2; ++i)
    printf("%g\n", (double)A[i][2]);
  assert(fabs(A[0][2] -  2) < 1e-15);
  assert(fabs(A[1][2] - -1) < 1e-15);
}

void tdm_test_2(void)
{
  number A[4][8] = {
    {1, 2, 0, 0, 1, 0, 0, 0},
    {2, 1, 2, 0, 0, 1, 0, 0},
    {0, 2, 1, 2, 0, 0, 1, 0},
    {0, 0, 2, 1, 0, 0, 0, 1},
  };
  number x[4][4] = {
    {-1.4,  1.2,  0.8, -1.6},
    { 1.2, -0.6, -0.4,  0.8},
    { 0.8, -0.4, -0.6,  1.2},
    {-1.6,  0.8,  1.2, -1.4},
  };
  int i, j;

  tdm(4, 8, A);
  for(i = 0; i < 4; ++i)
  {
    for(j = 4; j < 8; ++j)
      printf("%8g", A[i][j]);
    printf("\n");
  }
  for(i = 0; i < 4; ++i)
    for(j = 4; j < 8; ++j)
      assert(fabs(A[i][j] - x[i][j - 4]) < 1e-15);
}

void tdm_tri_test_1(void)
{
  number d[2] = {1, 1};
  number l[2] = {0.0/0.0, 3};
  number u[2] = {2, 0.0/0.0};
  number r[2] = {0, 5};
  int i;

  tdm_tri(2, 1, d, l, u, (void *)r);
  for(i = 0; i < 2; ++i)
    printf("%g\n", (double)r[i]);
  assert(fabs(r[0] -  2) < 1e-15);
  assert(fabs(r[1] - -1) < 1e-15);
}

void tdm_tri_test_2(void)
{
  number d[4] = {1, 1, 1, 1};
  number l[4] = {0.0/0.0, 2, 2, 2};
  number u[4] = {2, 2, 2, 0.0/0.0};
  number r[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1},
  };
  number x[4][4] = {
    {-1.4,  1.2,  0.8, -1.6},
    { 1.2, -0.6, -0.4,  0.8},
    { 0.8, -0.4, -0.6,  1.2},
    {-1.6,  0.8,  1.2, -1.4},
  };
  int i, j;

  tdm_tri(4, 4, d, l, u, r);
  for(i = 0; i < 4; ++i)
  {
    for(j = 0; j < 4; ++j)
      printf("%8g", r[i][j]);
    printf("\n");
  }
  for(i = 0; i < 4; ++i)
    for(j = 0; j < 4; ++j)
      assert(fabs(r[i][j] - x[i][j]) < 1e-15);
}
