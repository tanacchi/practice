#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_

#include <iostream>
#include <valarray>
#include "PlaneVector.hpp"

constexpr auto state_bom{-1};

class GameBoard {
public:
  enum class State {
    Hide,
    Flag,
    Show
  };
  using Point = unsigned char;
  using Position = PlaneVector;
  using Element = std::pair<short, State>;
  GameBoard(const Position& size);
  GameBoard(const GameBoard& src) = default;
  ~GameBoard() = default;
  Point width() const;
  Point height() const;
  Point size() const;
  Point get_access_num(Point x, Point y) const;
  Point get_access_num(const Position& pos) const;
  bool is_inside(Point x, Point y) const;
  bool is_inside(const Position& pos) const;
  void open(Point x, Point y);
  void open(const Position& pos);
  void set_bom(Point boms_point);
  void disp_element(Element element) const;
  void show() const;
private:
  std::valarray<Element> board_;
  const Position size_;
  const GameBoard& operator=(const GameBoard& src);
};

#endif // GAME_BOARD_H_
