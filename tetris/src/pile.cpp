#include <pile.hpp>

Pile::Pile() noexcept
  : body_{CellMatrix{std::vector<Cell>(10)}}
{
}

Pile::Pile(CellMatrix&& body) noexcept
  : body_{std::move(body)}
{
}

const CellMatrix& Pile::get_data() const
{
  return body_;
}
