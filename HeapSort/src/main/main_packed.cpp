#include <omp.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <cstdlib>
#include <ctime>

/////////////////////////////////////////////////////////////////BEGIN OF BIOTYPE///////////////////////
typedef std::size_t key_type;

struct biotype
{
  bool operator<(const biotype & rhs) const;
  bool operator>(const biotype & rhs) const;
  bool operator==(const biotype & rhs) const;
  key_type key;
};
typedef biotype *  biotype_ptr;

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
/////////////////////////////////////////////////////////////////END OF BIOTYPE///////////////////////

/////////////////////////////////////////////////////////////////BEGIN OF BIOPART///////////////////////
struct biopart
{
  biotype_ptr begin;
  biotype_ptr end;
  std::size_t part_size;
  bool operator<(const biopart & rhs) const;
  bool operator>(const biopart & rhs) const;
  bool operator==(const biopart & rhs) const;
};
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
/////////////////////////////////////////////////////////////////END OF BIOPART///////////////////////

/////////////////////////////////////////////////////////////////BEGIN OF UTILITY///////////////////////
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
/////////////////////////////////////////////////////////////////END OF UTILITY///////////////////////

/////////////////////////////////////////////////////////////////BEGIN OF WORKSPACE///////////////////////
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
/////////////////////////////////////////////////////////////////END OF WORKSPACE///////////////////////

/////////////////////////////////////////////////////////////////BEGIN OF HEAPSORT///////////////////////
template<typename T>
void heapify(T & part, const int size, const int root)
{
  if (size < 0 || root < 0)
  {
    throw std::invalid_argument("Invalid arguments in heapify(): size or root can't be < 0 !\n");
  }
  else if (part.begin == NULL || part.end == NULL)
  {
    throw std::invalid_argument("Invalid arguments in heapify(): input data is nullptr!\n");
  }
  int largest = root;
  int left = 2 * root + 1;
  int right = 2 * root + 2;
  if (left < size && *(part.begin+left) > *(part.begin+largest))
  {
    largest = left;
  }
  if (right < size && *(part.begin+right) > *(part.begin+largest))
  {
    largest = right;
  }
  if (largest != root)
  {
    std::swap( *(part.begin+root), *(part.begin+largest));
    heapify(part, size, largest);
  }
}

template<typename T>
double heapsort(T & part)
{
  std::size_t size = part.part_size;
  if (size <= 0)
  {
    throw std::invalid_argument("Invalid arguments in heap_sort(): size can't be <= 0 !\n");
  }
  else if (part.begin == NULL || part.end == NULL)
  {
    throw std::invalid_argument("Invalid arguments in heap_sort(): input data is nullptr!\n");
  }

  int i = 0;
  double start = omp_get_wtime();

  for (i = size / 2 - 1; i >= 0; i--)
  //Building heap.
  {
    heapify(part, size, i);
  }
  for (i = size - 1; i >= 0; i--)
  //Extract elements 1 by 1 from heap.
  {
    std::swap( *(part.begin), *(part.begin + i) );
    heapify(part, i, 0);
  }

  double end = omp_get_wtime();
  double time = end - start;
  return time;
}
/////////////////////////////////////////////////////////////////END OF HEAPSORT///////////////////////

/////////////////////////////////////////////////////////////////BEGIN OF MAIN///////////////////////
void performTask(std::size_t N, std::size_t M)
{
  if (N <= 1)
  {
    throw std::invalid_argument("Invalid arguments in performTask(): n value must be >=1!\n");
  }
  else if (M <= 1 || M > N )
  {
    throw std::invalid_argument("Invalid arguments in performTask(): m value can't be <= 1 || > than n || (n % m != 0)!\n");
  }
    
  const std::size_t S = ((N / M) + ((N % M) ? 1 : 0)) * M;
  //S - total SIZE.
  const std::size_t P = S / M;
  //Amount of parts.
  
  std::vector<biotype> bio_data(S);
  
  fill_randomly(bio_data, 0, 50);
  //Distribution [0;50].

  std::vector<biopart> parts(P);
  split(bio_data, parts, M);

  if (S <= 20)
  {
    std::cout << "Unsorted data:\n";
    print(bio_data);
  }
  
  double total_sort_time = 0.0;
  #pragma omp parallel for reduction(+:total_sort_time)
  for (std::size_t i = 0; i < P; i++)
  {
    double tmp_time = heapsort(parts[i]);
    total_sort_time += tmp_time;
  }
  std::cout << "Total sort time: " << std::fixed << total_sort_time << std::endl;
  if (S <= 20)
  {
    std::cout << "Sorted splitted data:\n";
    print(bio_data);
  }
  double start_of_dealWithCollisions = omp_get_wtime();
  //dealWithCollisions(parts, P);
  std::sort(bio_data.begin(), bio_data.end());
  double end_of_dealWithCollisions = omp_get_wtime();
  double total_dealWithCollisions_time = end_of_dealWithCollisions - start_of_dealWithCollisions;
  if( S <= 20)
  {
    std::cout << "After deal with collisions:\n";
    print(bio_data);
  }
  std::cout << "dealWithCollisions time: " << total_dealWithCollisions_time << std::endl;
  std::cout << "Total time: " << total_sort_time + total_dealWithCollisions_time << std::endl;
}

int main()
{
  std::cout << "Enter n (array size) and m (size of each part): ";
  std::size_t n = 0, m = 0;
  std::cin >> n >> m;
  if (std::cin.fail())
  {
    std::cerr << "Invalid input: n and m must be positive integer numbers!\n";
  }
  std::cout << "Starting work.\n";
  performTask(n, m);
  return 0;
}
/////////////////////////////////////////////////////////////////END OF MAIN///////////////////////
