#ifndef BIOPART_HPP
#define BIOPART_HPP

#include "biotype.hpp"
#include <cstddef>
#include <ostream>

struct biopart
{
  biotype_ptr begin;
  biotype_ptr end;
  std::size_t part_size;
  bool operator<(const biopart & rhs) const;
  bool operator>(const biopart & rhs) const;
  bool operator==(const biopart & rhs) const;
};
bool is_intersects(const biopart & current, const biopart & next);
#endif
