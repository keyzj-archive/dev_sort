#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define DEBUG 1

void siftDown(int * numbers, int root, int bottom)
//Function for sifting heap.
{
  int maxChild = 0;
  bool isDone = false;

  while ((root * 2 <= bottom) && (!isDone))
  //Until we are at bottom (last row).
  {
    if (root * 2 == bottom)
    //If we are at the bottom, then choose leftChild.
    {
      maxChild = root * 2;
    }
    else if (numbers[root * 2] > numbers[root * 2 + 1])
    //Else choose bigger child.
    {
      maxChild = root * 2;
    }
    else
    {
      maxChild = root * 2 + 1;
    }

    if (numbers[root] < numbers[maxChild])    
    //If root (vertex) element < maxChild, then swap them.
    {
      int temp = numbers[root];
      numbers[root] = numbers[maxChild];
      numbers[maxChild] = temp;
      root = maxChild;
    }
    else
    {
      isDone = true;
    }
  }
}

void heapSort(int * numbers, int size)
{
  for (int i = (size / 2) - 1; i >= 0; i--)
  //Forming low row of pyramid.
  {
    siftDown(numbers, i, size);
  }
  for (int i = size - 1; i >= 1; i--)
  //Sifting other elements through pyramid.
  {
    int temp = numbers[0];
    numbers[0] = numbers[i];
    numbers[i] = temp;
    //Swaped first element of pyramid with the last.
    siftDown(numbers, 0, i - 1);
  }
}

void fillRandomly(int data[], const int size)
{
  srand(time(NULL));
  for (int i = 0; i < size; i++)
  {
    data[i] = rand();
  }
}

void print(int data[], const int size)
{
  for (int i = 0; i < size; i++)
  {
    printf("Data: %d \n", data[i]);
  }
}

int main()
{
  const int SIZE = 5;
  int a[SIZE];
  fillRandomly(a, SIZE);

#if (DEBUG) == 1
  printf("Unsorted data\n");
  print(a, SIZE);
#endif

  double start = omp_get_wtime();
  heapSort(a, SIZE);
  double end = omp_get_wtime();

#if (DEBUG) == 1
  printf("Sorted data\n");
  print(a, SIZE);
#endif

  printf("Time: %f \n", (end - start));

  return 0;
}
