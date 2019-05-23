#ifndef INCLUDED_PILE_HPP
#define INCLUDED_PILE_HPP

#include <vector>
#include <cell.hpp>

class Pile
{
  public:
    Pile() noexcept;

  private:
    std::vector<std::vector<Cell>> body_;
};

#endif  // INCLUDED_PILE_HPP
