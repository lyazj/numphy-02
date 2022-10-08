#include "defs.h"
#include <assert.h>
#include <stdio.h>

static void che_test_gen(void);
static void che_test_eval(void);

int main(void)
{
  che_test_gen();
  che_test_eval();
  return 0;
}

void che_test_gen(void)
{
  poly_t T[4];
  poly_t T_ref[4] = {
    {0, { 1}},
    {1, { 0,  1}},
    {2, {-1,  0,  2}},
    {3, { 0, -3,  0,  4}},
  };
  int i;

  che_gen(3, T);
  for(i = 0; i <= 3; ++i)
  {
    printf("T[%d] = %s\n", i, poly_sstr(&T[i]));
    assert(poly_equ(&T[i], &T_ref[i]));
  }
}

void che_test_eval(void)
{
  {
    number c[1] = {2};
    assert(che_eval(0, c, 8) == 2);
  }
  {
    number c[2] = {2, 4};
    assert(che_eval(1, c, 8) == 34);
  }
  {
    number c[4] = {0, 1, 0, 1};
    assert(che_eval(3, c, 8) == 2032);
  }
}
