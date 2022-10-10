#include "defs.h"
#include <math.h>
#include <assert.h>
#include <stdio.h>

static number cosx2(number x);
static void test_cub_2pp(void);
static void test_cub_eval(void);

int main(void)
{
  test_cub_2pp();
  test_cub_eval();
  return 0;
}

number cosx2(number x)
{
  return cos(x*x);
}

void test_cub_2pp(void)
{
  number x[3] = {0, 0.6, 0.9};
  number y[3];
  number c[2][4];
  int i, j, r;

  for(i = 0; i < 3; ++i)
    y[i] = cosx2(x[i]);
  r = cub_2pp(2, c, x, y, 0, 0);
  assert(r == 2);
  for(i = 0; i < 2; ++i)
  {
    for(j = 0; j < 4; ++j)
      printf("%16e", c[i][j]);
    printf("\n");
  }
  for(i = 0; i <= 2; ++i)
    assert(fabs(cub_eval(2, c, x, x[i]) - y[i]) < 1e-15);
}

void test_cub_eval(void)
{
  number c[3][4] = {
    {0, 0, 0, -1},
    {0, 0, 0,  0},
    {0, 0, 0,  1},
  };
  number x[4] = {-1, 0, 1, 2};

  assert(isnan(cub_eval(0, c, x, -1)));

  assert(isnan(cub_eval(1, c, x, -1.5)));
  assert(cub_eval(1, c, x, -1) == -1);
  assert(cub_eval(1, c, x, -0.5) == -1);
  assert(cub_eval(1, c, x, 0) == -1);
  assert(isnan(cub_eval(1, c, x, 0.5)));

  assert(isnan(cub_eval(2, c, x, -1.5)));
  assert(cub_eval(2, c, x, -1) == -1);
  assert(cub_eval(2, c, x, -0.5) == -1);
  assert(cub_eval(2, c, x, 0) == -1);
  assert(cub_eval(2, c, x, 0.5) == 0);
  assert(cub_eval(2, c, x, 1) == 0);
  assert(isnan(cub_eval(2, c, x, 1.5)));

  assert(isnan(cub_eval(3, c, x, -1.5)));
  assert(cub_eval(3, c, x, -1) == -1);
  assert(cub_eval(3, c, x, -0.5) == -1);
  assert(cub_eval(3, c, x, 0) == -1);
  assert(cub_eval(3, c, x, 0.5) == 0);
  assert(cub_eval(3, c, x, 1) == 0);
  assert(cub_eval(3, c, x, 1.5) == 1);
  assert(cub_eval(3, c, x, 2) == 1);
  assert(isnan(cub_eval(3, c, x, 2.5)));
}
