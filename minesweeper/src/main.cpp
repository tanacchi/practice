#include <iostream>
#include <random>
#include <valarray>
#include "../include/GameBoard.hpp"

class MineSweeper {
public:
  MineSweeper(Position size = Position{8, 8});
  MineSweeper(const MineSweeper& src);
  const MineSweeper& operator=(const MineSweeper& src);
  ~MineSweeper();
private:
  GameBoard board_;
  std::mt19937 rand_engine;
  std::uniform_int_distribution<Point> rand_pos;
};

MineSweeper::MineSweeper(Position size)
  : board_{size},
    rand_engine{std::random_device{}()},
    rand_pos{board_.size()}
{
}

int main(int argc, char** argv)
{
  GameBoard board{Position{8, 8}};
  board.show();
  board.open(3, 5);
  board.show();
  return 0;
}
