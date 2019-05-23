#include <iostream>
#include <tetrimino.hpp>

int main()
{
  Tetrimino tetrimino{{
    {Cell(true),  Cell(true), Cell(false)},
    {Cell(false), Cell(true), Cell(true)}
  }};

  std::cout << tetrimino.to_string() << std::endl;

  return 0;
}
