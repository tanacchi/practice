#include <cell.hpp>

Cell::Cell(bool is_present) noexcept
  : is_present_{is_present}
{
}

Cell::operator bool() const noexcept
{
  return is_present_;
}
