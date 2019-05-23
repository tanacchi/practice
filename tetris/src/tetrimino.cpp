#include <sstream>
#include <tetrimino.hpp>

Tetrimino::Tetrimino() noexcept
  : body_{}
{
}

Tetrimino::Tetrimino(CellMatrix&& body)
  : body_{std::move(body)}
{
}

std::string Tetrimino::to_string() const noexcept
{
  std::stringstream ss{};
  for (const auto row: body_)
  {
    for (const auto cell: row)
    {
      ss << ' ' << (cell ? 'X' : ' ');
    }
    ss << std::endl;
  }
  return ss.str();
}
