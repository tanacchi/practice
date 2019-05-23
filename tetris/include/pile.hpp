#ifndef INCLUDED_PILE_HPP
#define INCLUDED_PILE_HPP

#include <vector>
#include <cell.hpp>

class Pile
{
  public:
    Pile() noexcept;
    const std::vector<std::vector<Cell>>& get_data() const;

  private:
    std::vector<std::vector<Cell>> body_;
};

#endif  // INCLUDED_PILE_HPP
