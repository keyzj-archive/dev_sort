#include "biopart.hpp"

#include <iostream>

bool biopart::operator<(const biopart & rhs) const
{
  for(std::size_t i = 0; i < part_size; i++)
  {
    if (*(begin+i) > *(rhs.begin+i))
    { 
      return false;
    }
  }
  return true;
}
bool biopart::operator>(const biopart & rhs) const
{
  return *begin > *rhs.begin;
}
bool biopart::operator ==(const biopart& rhs) const
{
  return (begin == rhs.begin) && (end == rhs.end);
}
bool is_intersects(const biopart & current, const biopart & next)
{
  return (*next.begin < *current.end);
}
