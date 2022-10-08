#include "defs.h"
#include <assert.h>
#include <stdio.h>

static void che_test_gen(void);

int main(void)
{
  che_test_gen();
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
