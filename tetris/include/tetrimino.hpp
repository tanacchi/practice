#ifndef INCLUDED_TETRIMINO_HPP
#define INCLUDED_TETRIMINO_HPP

#include <vector>
#include <cell.hpp>
#include <utility>

enum class Direction : short
{
  Up, Down, Left, Right
};

class Tetrimino
{
  public:
    using Position = std::pair<std::size_t, std::size_t>;

    Tetrimino() noexcept;
    explicit Tetrimino(CellMatrix&& body);  // XXX: Must not be used.
    std::string to_string() const noexcept;
    Position::first_type  get_x() const noexcept;
    Position::second_type get_y() const noexcept;
    const CellMatrix& get_body() const;
    void move(Direction direction);

  private:
    CellMatrix body_;
    Position pos_;
};

#endif  // INCLUDED_TETRIMINO_HPP
