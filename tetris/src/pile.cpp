#include <pile.hpp>

Pile::Pile() noexcept
  : body_{CellMatrix{std::vector<Cell>(10)}}
{
}

const CellMatrix& Pile::get_data() const
{
  return body_;
}
