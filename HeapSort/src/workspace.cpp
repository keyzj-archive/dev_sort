#include "workspace.hpp"
#include <stdexcept>
#include <algorithm>

void split(std::vector<biotype> & data, std::vector<biopart> & parts, std::size_t M)
{
  if (data.size() <= 1 || parts.size() <= 1 || M <= 0)
  {
    throw std::invalid_argument("Invalid arguments in split(): size can't be <= 1!\n");
  }
  for (std::size_t i = 0; i < parts.size(); i++)
  {
    parts[i].part_size = M;
    parts[i].begin = &data[i*M];
    parts[i].end = parts[i].begin + (M-1);
  }
}
void divorce(biopart & lhs, biopart & rhs)
{
  for(std::size_t i = 0; i < lhs.part_size + rhs.part_size; i++)
  {
    #pragma omp parallel for
    for(std::size_t j = (i % 2) ? 0 : 1; j < lhs.part_size + rhs.part_size - 1; j += 2)
    {
      const size_t lj =  j % lhs.part_size;
      const size_t rj = (j + 1) % lhs.part_size;
      biotype_ptr lhs_ptr = (j < lhs.part_size) ? lhs.begin : rhs.begin;
      biotype_ptr rhs_ptr = (j + 1 < lhs.part_size) ? lhs.begin : rhs.begin;
      if(getKey(*(lhs_ptr + lj)) > getKey(*(rhs_ptr + rj)))
      {
        std::swap(*(lhs_ptr + lj), *(rhs_ptr + rj));
      }
    }
  }
}
void dealWithCollisions(std::vector<biopart> & parts, const std::size_t & P)
//Further we need to take care about collisions.
{
  for(std::size_t i = 0; i < P; i++)
  {
    #pragma omp parallel for
    for(std::size_t j =(i % 2); j < P; j++)
    {
      if( (j+1<P) && (is_intersects(parts[j], parts[j+1])) )
      {
        divorce(parts[j], parts[j+1]);
      }
    }
    std::sort(parts.begin(), parts.end());
  }
}
