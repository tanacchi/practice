#include <main_display.hpp>

#define HEIGHT 20

MainDisplay::MainDisplay()
  : win_{newwin(HEIGHT, 10, 0, 0)}
{
  initscr();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);
  refresh();
}

void MainDisplay::show(const Pile& pile) const
{
  const auto& body{pile.get_data()};
  for (auto y{0ul}, height{body.size()}; y < height; ++y)
  {
    for (auto x{0ul}, width{body[y].size()}; x < width; ++x)
    {
      mvwaddch(win_.get(), y, x, body[y][x].to_char());
    }
  }
}
