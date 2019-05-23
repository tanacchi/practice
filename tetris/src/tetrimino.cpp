#include <sstream>
#include <tetrimino.hpp>

Tetrimino::Tetrimino() noexcept
  : body_{}
  , pos_{}
{
}

Tetrimino::Tetrimino(CellMatrix&& body)
  : body_{std::move(body)}
  , pos_{}
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

Tetrimino::Position::first_type Tetrimino::get_x() const noexcept
{
  return pos_.first;
}

Tetrimino::Position::second_type Tetrimino::get_y() const noexcept
{
  return pos_.second;
}

const CellMatrix& Tetrimino::get_body() const
{
  return body_;
}

void Tetrimino::move(Direction direction)
{
  switch (direction)
  {
    case Direction::Up:    --pos_.second; break;
    case Direction::Down:  ++pos_.second; break;
    case Direction::Left:  --pos_.first;  break;
    case Direction::Right: ++pos_.first;  break;
  }
}
