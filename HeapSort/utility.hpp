#include <stdio.h>
#include <stdlib.h>

template<typename T>
void fillRandomly(T data[], const int & size)
{
  for (int i = 0; i < size; i++)
  {
    data[i] = rand();
  }
}
template<typename T>
void print(T data[], const int & size)
{
  for (int i = 0; i < size; i++)
  {
    printf("Data: %d \n", data[i]);
  }
}
template<typename T>
void mergeArrays(T a[], T b[], T c[], const int size)
{
  int i = 0, j = 0, k = 0;
  while (i < size  && j < size)
  {
    c[k++] = a[i] < b[j] ? a[i++] : b[j++];
  }
  while (i < size)
  {
    c[k++] = a[i++];
  }
  while (j < size)
  {
    c[k++] = b[j++];
  }
}
