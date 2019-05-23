#ifndef INCLUDED_TETRIMINO_HPP
#define INCLUDED_TETRIMINO_HPP

#include <vector>
#include <cell.hpp>

class Tetrimino
{
  public:
    Tetrimino() noexcept;
    explicit Tetrimino(std::vector<std::vector<Cell>>&& body);  // XXX: Must not be used.
    std::string to_string() const noexcept;

  private:
    std::vector<std::vector<Cell>> body_;
};

#endif  // INCLUDED_TETRIMINO_HPP
