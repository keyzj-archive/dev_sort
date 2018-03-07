#include "heap_sort.hpp"

void heapify(int a[], const int size, int i)
{
  int largest = i;
  //Init it as a root.
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  if (left < size && a[left] > a[largest])
  {
    largest = left;
  }
  if (right < size && a[right] > a[largest])
  {
    largest = right;
  }
  if (largest != i)
  //if it's not root.
  {
    int temp = a[i];
    a[i] = a[largest];
    a[largest] = temp;
    heapify(a, size, largest);
  }
}
void heapSort(int a[], int size)
{
  int i = 0;
  #pragma omp parallel for shared(a, size) num_threads(1)
  for (i = size / 2 -1; i >= 0; i--)
  //Building heap.
  {
    heapify(a, size, i);
  }
  #pragma omp parallel for private (i) shared(a, size) num_threads(1)
  for (i = size - 1; i >= 0; i--)
  //Extract elements 1 by 1 from heap.
  {
    int temp = a[0];
    a[0] = a[i];
    a[i] = temp;
    heapify(a, i, 0);
  }
}
