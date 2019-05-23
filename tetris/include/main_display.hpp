#ifndef INCLUDED_MAIN_DISPLAY_HPP
#define INCLUDED_MAIN_DISPLAY_HPP

#include <memory>
#include <ncurses.h>

struct WindowPtrDeleter
{
  void operator()(WINDOW* ptr)
  {
    delwin(ptr);
  }
};

class MainDisplay
{
  public:
    MainDisplay();
  private:
    std::unique_ptr<WINDOW> win_;
};

#endif  // INCLUDED_MAIN_DISPLAY_HPP
