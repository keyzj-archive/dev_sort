#ifndef HEAPSORT_HPP
#define HEAPSORT_HPP

#include <algorithm>
#include <omp.h>
#include <iostream>

template<typename T>
void heapify(T *a, const int size, int i)
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
    std::swap(a[i], a[largest]);
    heapify(a, size, largest);
  }
}
template<typename T>
void heap_sort(T *a, const int size)
{
  int i = 0;
  double start = omp_get_wtime();

  #pragma omp parallel for shared(a, size) num_threads(1)
  for (i = size / 2 - 1; i >= 0; i--)
    //Building heap.
  {
    heapify(a, size, i);
  }
  #pragma omp parallel for private (i) shared(a, size) num_threads(1)
  for (i = size - 1; i >= 0; i--)
    //Extract elements 1 by 1 from heap.
  {
    std::swap(a[0], a[i]);
    heapify(a, i, 0);
  }

  double end = omp_get_wtime();
  std::cout << "Numbers sorted: " << size << "\n";
  std::cout << std::fixed << "Time: " << (end - start) << "\n";
}
#endif
