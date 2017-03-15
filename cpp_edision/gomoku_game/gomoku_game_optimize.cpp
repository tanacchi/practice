#include <cstddef>
#include <iostream>
#include <memory>
#include <numeric>
#include <stdexcept>
#include <utility>
#include <valarray>

//! The point class. But I implement it.
using point = std::pair<std::size_t, std::size_t>;

//! The game field class.
class field
{
public:
  //! The kind of field state.
  enum class kind
  {
    space,
    white,
    black
  };

  //! Create the field [size.second][size.first]
  field(const point& size)
    : size_ {size},
      data_ {size.second * size.first}
  {
  }

  void put(point p, kind k)
  {
    if (!is_valid(p)) throw std::out_of_range {"field: fail access on put the stone"};
    access(p) = k;
  }

  bool is_valid(point p) const noexcept
  {
    if (p.first >= width(), p.second >= height()) return false; // out range
    return kind::space == access(p); // if exist value, false.
  }

  point::first_type width() const noexcept
  {
    return size_.first;
  }

  point::second_type height() const noexcept
  {
    return size_.second;
  }

private:
  using data_type = std::valarray<kind>;

  data_type::value_type& access(point p) noexcept
  {
    return data_[width() * p.second + p.first];
  }

  const data_type::value_type& access(point p) const noexcept
  {
    return data_[width() * p.second + p.first];
  }

  point     size_;
  data_type data_;
};

class player
{
public:
  virtual ~player() = default;
  virtual point get_point(const field&) = 0;
};

class human_player
  : public player
{
public:
  point get_point(const field& valid_area) override
  {
    point p;
    do {
      std::cout << "where set to? [x y]\n > " << std::flush;
      std::cin >> p.first >> p.second;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (!valid_area.is_valid(p) && std::cout << "wrong input." << std::endl); // out range
    return p;
  }
};

class computer_player
  : public player
{
public:
  computer_player()
    : rand_ {std::random_device{}()}
  {
  }

  point get_point(const field& valid_area) override
  {
    std::uniform_int_distribution<point::first_type> dist_x {0, valid_area.width() - 1};
    std::uniform_int_distribution<point::second_type> dist_y {0, valid_area.height() - 1};
    return {dist_x(rand_), dist_y(rand_)};
  }

private:
  std::default_random_engine rand_;
};

class game_master
{
public:
  template<typename Player1, typename Player2>
  game_master(std::unique_ptr<Player1> player1, std::unique_ptr<Player2> player2, const point& size)
    : player1_       {player1.release()},
      player2_       {player2.release()},
      active_player_ {player1_.get()},
      board_         {size}
  {
  }

  void run()
  {
    while (!is_game_finish()) {
      draw();
      update();
    }
    draw();
    std::cout << is_first_player();
  }

  void draw()
  {
  }

  void update()
  {
    board_.put(active_player_->get_point(board_), get_active_kind());
    switch_player();
  }

private:
  bool is_first_player() const noexcept
  {
    return player1_.get() == active_player_;
  }

  void switch_player() noexcept
  {
    active_player_ = (is_first_player() ? player2_.get() : player1_.get());
  }

  field::kind get_active_kind() const noexcept
  {
    return is_first_player() ? field::kind::black : field::kind::white;
  }

  bool is_game_finish() const noexcept
  {
    return true; // TODO: implement me;
  }

  std::unique_ptr<player> player1_;
  std::unique_ptr<player> player2_;
  player*                 active_player_;
  field                   board_;
};

int main(int argc, char** argv)
{
  std::ios_base::sync_with_stdio(false);
  game_master master {std::make_unique<computer_player>(), std::make_unique<computer_player>(), point{9, 9}};
  master.run();
}
