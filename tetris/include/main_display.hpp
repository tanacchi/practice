#ifndef INCLUDED_MAIN_DISPLAY_HPP
#define INCLUDED_MAIN_DISPLAY_HPP

#include <memory>
#include <ncurses.h>
#include <pile.hpp>

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
    void show(const Pile& pile) const;
  private:
    std::unique_ptr<WINDOW> win_;
};

#endif  // INCLUDED_MAIN_DISPLAY_HPP
