#include <main_display.hpp>

#define HEIGHT 20

MainDisplay::MainDisplay()
  : win_{newwin(22, 12, 0, 0)}
{
}

void MainDisplay::show(const Pile& pile) const
{
  wclear(win_.get());
  const auto& body{pile.get_data()};
  for (auto y{0ul}, height{body.size()}; y < height; ++y)
  {
    for (auto x{0ul}, width{body[y].size()}; x < width; ++x)
    {
      mvwaddch(win_.get(), HEIGHT - y, x + 1, body[y][x].to_char());
    }
  }
  box(win_.get(), ACS_VLINE, ACS_HLINE);
  wrefresh(win_.get());
}
