#include <iostream>
#include <tetrimino.hpp>
#include <pile.hpp>
#include <main_display.hpp>

#include <unistd.h>  // XXX: sleep function

int main()
{
  // Tetrimino tetrimino{{
    // {Cell(true),  Cell(true), Cell(false)},
    // {Cell(false), Cell(true), Cell(true)}
  // }};
  // std::cout << tetrimino.to_string() << std::endl;

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
  disp.show(pile);

  sleep(3);  // XXX: Avoid to use it.

  endwin();

  return 0;
}
