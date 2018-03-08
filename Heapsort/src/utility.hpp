#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <random>
#include <iostream>

template<typename T>
void fillRandomly(T data[], const int size, const int min, const int max)
{
  std::random_device rd;
  std::uniform_int_distribution<T> uid(min, max);
  for (size_t i = 0; i < size; i++)
  {
    data[i] = uid(rd);
  }
}
template<typename T>
void print(T data, const int size)
{
  for (size_t i = 0; i < size; i++)
  {
    std::cout << data[i] << " ";
  }
  std::cout << std::endl;
}
template<typename T>
void print(T ** data, const int m, const int size)
{
  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < size; j++)
    {
      std::cout << "data[" << i << "][" << j << "] = " << data[i][j] << "\n";
    }
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
template<typename T>
void split(T * data, T **result, const int m, const int size)
{
  for (int i = 0; i < m; i++)
  {
    result[i] = &data[i*size];
    std::cout << "result[" << i << "] = " << *result[i] << "\n";
  }
}
template<typename T>
void get_table(T ** data, const int m, const int size)
{
  for (int i = 0; i < m; i++)
  {
    std::cout << "||B" << i << ": " << data[i][0] << ", E" << i << ": " << data[i][size - 1] << "||\n";
    std::cout << "==================\n";
  }
}
#endif
