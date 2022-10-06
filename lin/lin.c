#include "defs.h"
#include <stdio.h>

#define NR 4
#define NC 5

const number EQU[NR][NC] = {
  {0.05, 0.07, 0.06, 0.05, 0.23},
  {0.07, 0.10, 0.08, 0.07, 0.32},
  {0.06, 0.08, 0.10, 0.09, 0.33},
  {0.05, 0.07, 0.09, 0.10, 0.31},
};

static void do_solve(const char *name, solve_t solve);

int main(void)
{
  do_solve("gem", gem);
  do_solve("cholesky", cholesky);
  do_solve("cdm", cdm);
  return 0;
}

void do_solve(const char *name, solve_t solve)
{
  number A[NR][NC];
  int i, j;

  for(i = 0; i < NR; ++i)
    for(j = 0; j < NC; ++j)
      A[i][j] = EQU[i][j];
  solve(NR, NC, A);
  printf("%s:\n", name);
  for(i = 0; i < NR; ++i)
  {
    for(j = 0; j < NC; ++j)
      printf("%16g", A[i][j]);
    printf("\n");
  }
}
