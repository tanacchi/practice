#ifndef INCLUDED_TETRIMINO_HPP
#define INCLUDED_TETRIMINO_HPP

#include <vector>
#include <cell.hpp>

class Tetrimino
{
  public:
    Tetrimino() noexcept;
    explicit Tetrimino(CellMatrix&& body);  // XXX: Must not be used.
    std::string to_string() const noexcept;

  private:
    CellMatrix body_;
};

#endif  // INCLUDED_TETRIMINO_HPP
