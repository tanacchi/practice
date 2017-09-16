#include "../include/GameBoard.hpp"

GameBoard::GameBoard(Position size)
  : board_{Element{0, State::Hide}, static_cast<std::size_t>(size.x*size.y)},
    size_{size}
{
}

inline Point GameBoard::width() const
{
  return size_.x;
}

inline Point GameBoard::height() const
{
  return size_.y;
}

Point GameBoard::size() const
{
  return width() * height();
}

inline Point GameBoard::get_access_num(Point x, Point y) const
{
  return x + width()*y;
}

inline Point GameBoard::get_access_num(Position pos) const
{
  return get_access_num(pos.x, pos.y);
}

bool GameBoard::is_inside(Point x, Point y) const
{
  return x < width() && y < height();
}

bool GameBoard::is_inside(Position pos) const
{
  return is_inside(pos.x, pos.y);
}

void GameBoard::open(Point x, Point y)
{
  board_[get_access_num(x, y)].second = State::Show;
}

void GameBoard::open(Position pos)
{
  open(pos.x, pos.y);
}

void GameBoard::set_bom(Point boms_point)
{
  board_[boms_point].first = state_bom;
}

void GameBoard::disp_element(Element element) const
{
  switch (element.second) {
  case State::Hide: std::cout << '"' << std::flush; break;
  case State::Flag: std::cout << 'P' << std::flush; break;
  case State::Show:
    if (element.first == 0) std::cout << ' ' << std::flush;
    else std::cout << element.first << std::flush;
    break;
  }
}

void GameBoard::show() const
{
  std::cout << "   " << std::flush;
  for (int i{0}; i < width(); std::cout.put(' '), i++) std::cout << i+1 << std::flush;
  std::cout << std::endl;
  std::cout << "  " << std::flush;
  for (int i{0}; i < width()*2+1; i++) std::cout.put('-');
  std::cout << std::endl;
  for (int y{0}; y < height(); std::cout.put('\n'), y++) {
    std::cout << y+1 << "| " << std::flush;
    for (int x{0}; x < width(); std::cout.put(' '), x++)
      disp_element(board_[get_access_num(x, y)]);
    std::cout.put('|');
  }
  std::cout << "  " << std::flush;
  for (int i{0}; i < width()*2+1; i++) std::cout.put('-');
  std::cout << std::endl;
}
