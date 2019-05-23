#ifndef INCLUDED_CELL_HPP
#define INCLUDED_CELL_HPP

#include <vector>

class Cell
{
  public:
    explicit Cell(bool is_present = false) noexcept;
    explicit operator bool() const noexcept;
    char to_char() const noexcept;

  private:
    bool is_present_;
};

using CellMatrix = std::vector<std::vector<Cell>>;

#endif  // INCLUDED_CELL_HPP
