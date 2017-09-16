#include <iostream>
#include <random>
#include <valarray>
#include "../include/GameBoard.hpp"

class MineSweeper {
public:
  MineSweeper(GameBoard::Position size = GameBoard::Position{8, 8});
  MineSweeper(const MineSweeper& src);
  const MineSweeper& operator=(const MineSweeper& src);
  ~MineSweeper();
private:
  GameBoard board_;
  std::mt19937 rand_engine;
  std::uniform_int_distribution<GameBoard::Point> rand_pos;
};

MineSweeper::MineSweeper(GameBoard::Position size)
  : board_{size},
    rand_engine{std::random_device{}()},
    rand_pos{board_.size()}
{
}

int main(int argc, char** argv)
{
  GameBoard board{GameBoard::Position{8, 8}};
  board.show();
  board.open(3, 5);
  board.show();
  return 0;
}
