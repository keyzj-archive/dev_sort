#include <iostream>
#include <sstream>
#include "utility.hpp"
#include "heapsort.hpp"

void task1(const int n)
{
  if (n > 10000 || n < 1)
  {
    std::cout << "Incorrect n value = " << n << ", must be >=1!\n";
    return;
  }
  int * data = new int[n];
  fillRandomly(data, n, 0, 50);

  bool printable;
  (n <= 100) ? printable = true : printable = false;
  if (printable)
  {
    std::cout << "Unsorted data\n";
    print(data, n);
  }

  heap_sort(data, n);

  if (printable)
  {
    printf("Sorted data\n");
    print(data, n);
  }
  delete[] data;
}

void task2(const int n, const int m)
{
  if (n > 10000 || n < 1)
  {
    std::cout << "Incorrect n value = " << n << ", must be >=1!\n";
    return;
  }
  if ( m < 0 || m > n)
  {
    std::cout << "Incorrect m value = " << m << ", can't be negative or > n!\n";
    return;
  }
  const int size = n / m;
  int * data = new int[n];
  fillRandomly(data, n, 0, 50);

  bool printable;
  (n <= 100) ? printable = true : printable = false;
  if (printable)
  {
    std::cout << "Unsorted data:\n";
    print(data, n);
  }

  int ** seqs = new int*[m];
  split(data, seqs, m, size);

  if (printable)
  {
    std::cout << "Unsorted splitted data:\n";
    print(seqs, m, size);
  }

  for (int i = 0; i < m; i++)
  {
    heap_sort(seqs[i], size);
  }

  if (printable)
  {
    std::cout << "Sorted splitted data:\n";
    print(seqs, m, size);
  }

  get_table(seqs, m, size);
}

int main(int argc, char * argv[])
{
  std::cout << "Enter n (array size) and m (amount of sequences): ";
  unsigned int n = 0;
  unsigned int m = 0;
  std::cin >> n >> m;
  if (std::cin.fail())
  {
    std::cerr << "Invalid input: n and m must be positive integer numbers!\n";
  }
  std::cout << "Starting work.\n";
  task2(n, m);
  system("pause");
  return 0;
}
