#ifndef INCLUDED_PILE_HPP
#define INCLUDED_PILE_HPP

#include <vector>
#include <cell.hpp>

class Pile
{
  public:
    Pile() noexcept;
    Pile(CellMatrix&& cells) noexcept;
    const CellMatrix& get_data() const;

  private:
    CellMatrix body_;
};

#endif  // INCLUDED_PILE_HPP
