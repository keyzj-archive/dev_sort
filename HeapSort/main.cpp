#include <stdio.h>
#include <omp.h>
#include <time.h>
#include "utility.hpp"
#include "heap_sort.hpp"

void task1()
{
  const int size = 10;
  if (size > 256000 || size < 1)
  {
    printf("Incorrect SIZE value: size must be from 1 to 256'000\n");
    return;
  }
  int a[size];
  srand(time(NULL));
  fillRandomly(a, size);
  if (size <= 100)
  {
    printf("Unsorted data\n");
    print(a, size);
  }
  double start = omp_get_wtime();
  heapSort(a, size);
  double end = omp_get_wtime();
  if (size <= 100)
  {
    printf("Sorted data\n");
    printf("Array a contains:\n");
    print(a, size);
  }
  printf("Time: %f \n", (end - start));
}

void task2()
{
  const int size = 4;
  int a[size];
  int b[size];
  int c[size * 2];

  srand(time(NULL));
  fillRandomly(a, size);
  fillRandomly(b, size);
  if (size <= 100)
  {
    printf("Unsorted data\n");
    print(a, size);
    print(b, size);
  }
  double start = omp_get_wtime();
  heapSort(a, size);
  heapSort(b, size);
  mergeArrays(a, b, c, size);
  double end = omp_get_wtime();
  if (size <= 100)
  {
    printf("Sorted data\n");
    printf("Array a contains:\n");
    print(a, size);
    printf("Array b contains:\n");
    print(b, size);
    printf("Array c contains:\n");
    print(c, size * 2);
  }
  printf("Time: %f \n", (end - start));
}

int main(int argc, char * argv[])
{
  task1();
  //task2();
  system("pause");
  return 0;
}
