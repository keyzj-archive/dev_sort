#ifndef BIOTYPE_HPP
#define BIOTYPE_HPP

#include <cstddef>

typedef std::size_t key_type;

struct biotype
{
  bool operator<(const biotype & rhs) const;
  bool operator>(const biotype & rhs) const;
  bool operator==(const biotype & rhs) const;
  key_type key;
};

void setKey(biotype & obj, const key_type & key);
key_type getKey(const biotype & obj);
typedef biotype *  biotype_ptr;
#endif
