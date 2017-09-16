#include "../include/GameBoard.hpp"

GameBoard::GameBoard(const GameBoard::Position& size)
  : board_{GameBoard::Element{0, State::Hide}, static_cast<std::size_t>(size.x*size.y)},
    size_{size}
{
}

inline GameBoard::Point GameBoard::width() const
{
  return size_.x;
}

inline GameBoard::Point GameBoard::height() const
{
  return size_.y;
}

GameBoard::Point GameBoard::size() const
{
  return width() * height();
}

inline GameBoard::Point GameBoard::get_access_num(GameBoard::Point x, GameBoard::Point y) const
{
  return x + width()*y;
}

inline GameBoard::Point GameBoard::get_access_num(const GameBoard::Position& pos) const
{
  return get_access_num(pos.x, pos.y);
}

inline bool GameBoard::is_inside(GameBoard::Point x, GameBoard::Point y) const
{
  return x < width() && y < height();
}

bool GameBoard::is_inside(const GameBoard::Position& pos) const
{
  return is_inside(pos.x, pos.y);
}

void GameBoard::open(GameBoard::Point x, GameBoard::Point y)
{
  if (!is_inside(x, y)) return;
  board_[get_access_num(x, y)].second = State::Show;
}

void GameBoard::open(const GameBoard::Position& pos)
{
  open(pos.x, pos.y);
}

void GameBoard::set_bom(GameBoard::Point boms_point)
{
  board_[boms_point].first = state_bom;
}

void GameBoard::disp_element(GameBoard::Element element) const
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
