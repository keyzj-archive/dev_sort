#include "utility.hpp"
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <iostream>

void fill_randomly(std::vector<biotype> & data, const int first, const int last)
{
  if (data.size() <= 1)
  {
    throw std::invalid_argument("Invalid arguments in fill_randomly(): size can't be <= 1!\n");
  }
  srand(time(0));
  for (std::size_t i = 0; i < data.size(); i++)
  {
    key_type newKey = rand() % (last-first + 1 ) + first;
    setKey(data[i], newKey);
  }
}
void print(const std::vector<biotype> & data)
{
  if (data.size() <= 1)
  {
    throw std::invalid_argument("Invalid arguments in print(): size can't be <= 1!\n");
  }
  for (std::size_t i = 0; i < data.size(); i++)
  {
    std::cout << getKey(data[i]) << " ";
  }
  std::cout << std::endl;
}
