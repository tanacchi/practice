#include <iostream>
#include <tetrimino.hpp>
#include <pile.hpp>
#include <main_display.hpp>

#include <unistd.h>  // XXX: sleep function

int main()
{
  Tetrimino tetrimino{{
    {Cell(true),  Cell(true), Cell(true)},
    {Cell(false), Cell(true), Cell(false)}
  }};
  std::cout << tetrimino.to_string() << std::endl;

  initscr();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);
  refresh();

  MainDisplay disp{};
  Pile pile{{
    {Cell(true),  Cell(true),  Cell(true), Cell(true),  Cell(true)},
    {Cell(true),  Cell(true),  Cell(true), Cell(true),  Cell(true)},
    {Cell(false), Cell(true),  Cell(true), Cell(true),  Cell(false)},
    {Cell(false), Cell(true),  Cell(true), Cell(true),  Cell(false)},
    {Cell(false), Cell(false), Cell(true), Cell(false), Cell(false)},
  }};

  while (true)
  {
    disp.show(pile, tetrimino);
    sleep(1);  // XXX: Avoid to use it.
    tetrimino.move(Direction::Down);
  }
  endwin();

  return 0;
}
