#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>

int main()
{
  std::vector<std::unique_ptr<std::size_t>> size_ptrs;
  for (std::size_t i{0}; i < 5ul; ++i)
         size_ptrs.emplace_back(std::move(new std::size_t{i}));


  std::vector<std::unique_ptr<std::size_t> > size_ptrs_copy;

  // size_ptrs_copy.assign(size_ptrs.begin(), size_ptrs.end());
  size_ptrs_copy.assign(std::make_move_iterator(size_ptrs.begin()),
                        std::make_move_iterator(size_ptrs.end()));
  
  std::for_each(std::begin(size_ptrs_copy), std::begin(size_ptrs_copy),
      [](const std::unique_ptr<std::size_t>& v){
        std::cout << *v << std::endl;
      });

  return 0;
}
