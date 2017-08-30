#include <iostream>
#include <valarray>

#define STATE_BOM -1

using point = unsigned char;
using position = std::pair<point, point>;

class GameBoard {
public:
  enum class State {
    Hide,
    Flag,
    Show
  };
  GameBoard(position size = std::make_pair(8, 8));
  GameBoard(const GameBoard& src);
  ~GameBoard() = default;
  position::first_type width() const;
  position::second_type height() const;
  std::size_t get_access_num(position pos) const;
  std::size_t get_access_num(point x, point y) const;
  bool is_inside(point x, point y) const;
  bool is_inside(position pos) const;
  void open(point x, point y);
  void open(position pos);
private:
  std::valarray<std::pair<short, State>> board_;
  const position size_;
  const GameBoard& operator=(const GameBoard& src);
};

GameBoard::GameBoard(position size)
  : board_{std::make_pair(0, State::Hide), (std::size_t)size.first*size.second},
    size_{size}
{
}

GameBoard::GameBoard(const GameBoard& src)
  : board_{src.board_},
    size_{src.size_}
{
}

inline position::first_type GameBoard::width() const
{
  return size_.first;
}

inline position::second_type GameBoard::height() const
{
  return size_.second;
}

inline std::size_t GameBoard::get_access_num(point x, point y) const
{
  return (std::size_t)(x + width()*y);
}

inline std::size_t GameBoard::get_access_num(position pos) const
{
  return get_access_num(pos.first, pos.second);
}

bool GameBoard::is_inside(point x, point y) const
{
  return x < width() && y < height();
}

bool GameBoard::is_inside(position pos) const
{
  return is_inside(pos.first, pos.second);
}

void open(point x, point y)
{
  board_[get_access_num(x, y)].second = State::Show;;
}

void open(position pos)
{
  board_[get_access_num(pos)].second = State::Show;
}

class MineSweeper {
public:
  MineSweeper();
  MineSweeper(const MineSweeper& src);
  const MineSweeper& operator=(const MineSweeper& src);
  ~MineSweeper();
private:
};

int main(int argc, char** argv)
{

  return 0;
}
