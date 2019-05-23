#ifndef INCLUDED_TETRIMINO_HPP
#define INCLUDED_TETRIMINO_HPP

#include <vector>
#include <cell.hpp>
#include <utility>

class Tetrimino
{
  public:
    using Position = std::pair<int, int>;

    Tetrimino() noexcept;
    explicit Tetrimino(CellMatrix&& body);  // XXX: Must not be used.
    std::string to_string() const noexcept;
    Position::first_type  get_x() const noexcept;
    Position::second_type get_y() const noexcept;
    const CellMatrix& get_body() const;

  private:
    CellMatrix body_;
    Position pos_;
};

#endif  // INCLUDED_TETRIMINO_HPP