#include "biotype.hpp"

void setKey(biotype & obj, const key_type & key)
{
  obj.key = key;
}
key_type getKey(const biotype & obj)
{
  return (obj.key);
}
bool biotype::operator<(const biotype & rhs) const
{
  return (getKey(*this) < getKey(rhs));
}
bool biotype::operator>(const biotype & rhs) const
{
  return (getKey(*this) > getKey(rhs));
}
bool biotype::operator==(const biotype & rhs) const
{
  return (getKey(*this) == getKey(rhs));
}
