#include <iostream>
#include <random>
#include <valarray>

constexpr auto state_bom{-1};

using Point = unsigned char;
using Position = std::pair<Point, Point>;

class GameBoard {
public:
  enum class State {
    Hide,
    Flag,
    Show
  };
  using Element = std::pair<short, State>;
  GameBoard(Position size = Position{8, 8});
  GameBoard(const GameBoard& src);
  ~GameBoard() = default;
  Point width() const;
  Point height() const;
  Point get_access_num(Position pos) const;
  Point get_access_num(Point x, Point y) const;
  bool is_inside(Point x, Point y) const;
  bool is_inside(Position pos) const;
  void open(Point x, Point y);
  void open(Position pos);
  void set_bom(int boms_num);
private:
  std::valarray<std::pair<short, State>> board_;
  const Position size_;
  std::mt19937 rand_engine;
  const GameBoard& operator=(const GameBoard& src);
};

GameBoard::GameBoard(Position size)
  : board_{Element{0, State::Hide}, static_cast<std::size_t>(size.first*size.second)},
    size_{size},
    rand_engine{std::random_device}
{
}

GameBoard::GameBoard(const GameBoard& src)
  : board_{src.board_},
    size_{src.size_},
    rand_engine{src.rand_engine}
{
}

inline Point GameBoard::width() const
{
  return size_.first;
}

inline Point GameBoard::height() const
{
  return size_.second;
}

inline Point GameBoard::get_access_num(Point x, Point y) const
{
  return x + width()*y;
}

inline Point GameBoard::get_access_num(Position pos) const
{
  return get_access_num(pos.first, pos.second);
}

bool GameBoard::is_inside(Point x, Point y) const
{
  return x < width() && y < height();
}

bool GameBoard::is_inside(Position pos) const
{
  return is_inside(pos.first, pos.second);
}

void GameBoard::open(Point x, Point y)
{
  board_[get_access_num(x, y)].second = State::Show;
}

void GameBoard::open(Position pos)
{
  board_[get_access_num(pos)].second = State::Show;
}

void GameBoard::set_bom(int boms_num)
{
  std::uniform_int_distribution<Point> rand_pos(board_size());
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
