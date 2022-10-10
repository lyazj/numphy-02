#include "defs.h"
#include <stdio.h>

int tdm(int n, int m, number A[n][m])
{
  number a, b;
  int i, j;

  if(n == 0)
    return 0;
  // LU decomposition
  if((a = A[0][0]) == 0)
    return 0;
  for(i = 1; i < n; ++i)
  {
    b = A[i][i - 1] / a;
    A[i][i - 1] = b;
    a = A[i][i] - b * A[i - 1][i];
    A[i][i] = a;
    if(a == 0)
      return i;
  }

  for(i = 1; i < n; ++i)
    for(j = n; j < m; ++j)
      A[i][j] -= A[i][i - 1] * A[i - 1][j];
  for(j = n; j < m; ++j)
    A[n - 1][j] /= A[n - 1][n - 1];
  for(i = n - 2; i >= 0; --i)
    for(j = n; j < m; ++j)
      A[i][j] = (A[i][j] - A[i][i + 1] * A[i + 1][j]) / A[i][i];
  return n;
}

int tdm_tri(int n, int m,
    number d[n], number l[n], number u[n], number r[n][m])
{
  number a, b;
  int i, j;

  if(n == 0)
    return 0;
  // LU decomposition
  if((a = d[0]) == 0)
    return 0;
  for(i = 1; i < n; ++i)
  {
    b = l[i] / a;
    l[i] = b;
    a = d[i] - b * u[i - 1];
    d[i] = a;
    if(a == 0)
      return i;
  }

  for(i = 1; i < n; ++i)
    for(j = 0; j < m; ++j)
      r[i][j] -= l[i] * r[i - 1][j];
  for(j = 0; j < m; ++j)
    r[n - 1][j] /= d[n - 1];
  for(i = n - 2; i >= 0; --i)
    for(j = 0; j < m; ++j)
      r[i][j] = (r[i][j] - u[i] * r[i + 1][j]) / d[i];
  return n;
}
