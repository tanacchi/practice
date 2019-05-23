#include <pile.hpp>

Pile::Pile() noexcept
  : body_{std::vector<std::vector<Cell>>{std::vector<Cell>(10)}}
{
}

