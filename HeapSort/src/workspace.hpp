#ifndef WORKSPACE_HPP
#define WORKSPACE_HPP

#include <vector>
#include <cstddef>
#include "biopart.hpp"

void split(std::vector<biotype> & data, std::vector<biopart> & parts, std::size_t M);
void divorce(biopart & lhs, biopart & rhs);
void dealWithCollisions(std::vector<biopart> & parts, const std::size_t & P);
#endif
