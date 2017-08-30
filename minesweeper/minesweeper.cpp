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
  GameBoard();
  GameBoard(const GameBoard& src);
  const GameBoard& operator=(const GameBoard& src);
  ~GameBoard();
private:
  std::valarray<std::pair<short, State>> board_;
  const position size_;
};

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
