#include <pile.hpp>

Pile::Pile() noexcept
  : body_{std::vector<std::vector<Cell>>{std::vector<Cell>(10)}}
{
}

const std::vector<std::vector<Cell>>& Pile::get_data() const
{
  return body_;
}
