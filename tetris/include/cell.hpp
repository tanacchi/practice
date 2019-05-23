#ifndef INCLUDED_CELL_HPP
#define INCLUDED_CELL_HPP

class Cell
{
  public:
    explicit Cell(bool is_present = false) noexcept;
    explicit operator bool() const noexcept;

  private:
    bool is_present_;
};

#endif  // INCLUDED_CELL_HPP
