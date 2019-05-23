#include <main_display.hpp>

MainDisplay::MainDisplay()
  : win_{newwin(20, 10, 0, 0)}
{
  initscr();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);
  refresh();
}
