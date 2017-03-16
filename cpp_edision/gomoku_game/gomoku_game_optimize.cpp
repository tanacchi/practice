#include <array>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <memory>
#include <numeric>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <valarray>

//! The point class. But I don't implement it.
using point = std::pair<std::size_t, std::size_t>;
constexpr point invalid_point {-1, -1};

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

  using data_type = std::valarray<kind>;

  //! Create the field [size.second][size.first]
  field(const point size)
    : size_ {size},
      data_ {size.second * size.first}
  {
  }

  void put(point p, kind k)
  {
    if (!is_valid(p)) throw std::out_of_range {"field: fail access on put the stone"};
    access(std::move(p)) = k;
  }

  bool is_valid(point p) const noexcept
  {
    if (p.first >= width() || p.second >= height()) return false; // out range
    return kind::space == access(std::move(p)); // if exist value, false.
  }

  bool is_valid(point::first_type x, point::second_type y) const noexcept
  {
    return is_valid({x, y});
  }

  point::first_type width() const noexcept
  {
    return size_.first;
  }

  point::second_type height() const noexcept
  {
    return size_.second;
  }

  std::size_t get_access_number(point::first_type x, point::second_type y) const noexcept
  {
    return width() * y + x;
  }

  std::size_t get_access_number(const point p) const noexcept
  {
    return get_access_number(p.first, p.second);
  }

  template<typename T>
  data_type get_col(T x) const noexcept
  {
    return data_[std::slice(get_access_number(x, 0), height(), width())];
  }

  template<typename T>
  data_type get_row(T y) const noexcept
  {
    return data_[std::slice(get_access_number(0, y), width(), 1)];
  }

  template<typename T>
  data_type get_data(const T& specify) const
  {
    return data_[specify];
  }

  const data_type& get_data() const noexcept
  {
    return data_;
  }

  void init()
  {
    data_ = kind::space;
  }

private:
  data_type::value_type& access(point p) noexcept
  {
    return data_[get_access_number(std::move(p))];
  }

  const data_type::value_type& access(point p) const noexcept
  {
    return data_[get_access_number(std::move(p))];
  }

  point     size_;
  data_type data_;
};

char to_string(field::kind k) noexcept
{
  return k == field::kind::space ? ' ' :
         k == field::kind::white ? 'O' :
         '*';
}

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
    while (true) { // return when get valid point.
      std::cout << "where set to? [x y]\n > " << std::flush;
      point p;
      std::cin >> p.first >> p.second;
      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "please input double numbers.\n"; // wrong input.
        continue;
      }
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      --p.first;
      --p.second;
      if (valid_area.is_valid(p))
        return p;
      std::cout << "wrong input..\n"; // out range or exist value.
    }
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
    while (true) { // return when get valid point.
      std::uniform_int_distribution<point::first_type> dist_x {0, valid_area.width() - 1};
      std::uniform_int_distribution<point::second_type> dist_y {0, valid_area.height() - 1};
      point p {dist_x(rand_), dist_y(rand_)};
      if (valid_area.is_valid(p))
        return p;
    }
  }

private:
  std::default_random_engine rand_;
};

class cout_renderer
{
public:
  struct turn {std::size_t player_number; std::size_t turn_number;};
  struct winner {std::size_t player_number;};

  void operator()() const noexcept
  {
    std::cout << std::endl;
  }

  template<typename T, typename... Rest>
  void operator()(const T& head, const Rest&... rest) const
  {
    draw(head);
    operator()(rest...);
  }

  void draw(const field& value) const noexcept
  {
    auto fp {[digit = std::log10(value.width()) + 1](const auto& e){std::cout << std::setw(digit) << e;}}; // format print
    fp(' ');
    for (std::size_t i {}; i < value.width(); ++i)
      fp(i + 1);
    std::cout << '\n';
    for (std::size_t y {}; y < value.height(); ++y) {
      fp(y + 1);
      auto line {value.get_row(y)};
      std::for_each(std::begin(line), std::end(line), [fp](auto e){fp(to_string(e));});
      std::cout << '\n';
    }
  }

  void draw(turn t) const noexcept
  {
    std::cout << "\nThe turn of player " << t.player_number << ".\n";
  }

  void draw(winner w) const noexcept
  {
    std::cout << "winner player " << w.player_number << ".\n";
  }
};

class game_master
{
public:
  template<typename Player1, typename Player2>
  game_master(std::unique_ptr<Player1> player1, std::unique_ptr<Player2> player2, point size, std::size_t finish_length = 5)
    : board_         {std::move(size)},
      finish_length_ {board_.is_valid(finish_length - 1, finish_length - 1) ? 
                      finish_length :
                      throw std::out_of_range{"game_master: cannot clear with finish_length > board_size"}},
      player1_       {player1.release()},
      player2_       {player2.release()},
      active_player_ {player1_.get()}
  {
  }

  void run()
  {
    init();
    while (true) { // when is_game_finish to break to end.
      cout_renderer{}(board_, cout_renderer::turn{get_player_number()});
      update();
      if (is_game_finish())
        break;
      switch_player();
    }
    cout_renderer{}(board_, cout_renderer::winner{get_player_number()});
  }

private:
  void init()
  {
    active_player_ = player1_.get();
    current_put_ = invalid_point;
    board_.init();
  }

  void update()
  {
    current_put_ = active_player_->get_point(board_);
    board_.put(current_put_, get_active_kind());
  }

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

  std::size_t get_player_number() const noexcept
  {
    return is_first_player() ? 1 : 2;
  }

  bool is_game_finish() const noexcept
  {
    const point::first_type horizon_limit {board_.width() - finish_length_ + 1};
    const point::second_type vertical_limit {board_.height() - finish_length_ + 1};

    using search_data = std::tuple<point, point, std::size_t>;
    const std::array<const search_data, 4> search_datas {
      search_data{{0, horizon_limit}, {0, board_.height()}, 1}, // horizon
      search_data{{0, board_.width()}, {0, vertical_limit}, board_.width()}, // vertical
      search_data{{0, horizon_limit}, {0, vertical_limit}, board_.width() + 1}, // falling
      search_data{{finish_length_ - 1, board_.width()}, {0, vertical_limit}, board_.width() - 1}}; // soaring

    const auto active_kind {get_active_kind()};
    for (const auto& e : search_datas)
      for (point::second_type y {std::get<1>(e).first}; y < std::get<1>(e).second; ++y)
        for (point::first_type x {std::get<0>(e).first}; x < std::get<0>(e).second; ++x) {
          const auto line {board_.get_data(std::slice{board_.get_access_number(x, y), finish_length_, std::get<2>(e)})};
          if (std::all_of(std::begin(line), std::end(line), [active_kind](auto e){return e == active_kind;})) return true;
        }
    const auto& all_area {board_.get_data()};
    if (std::none_of(std::begin(all_area), std::end(all_area), [](auto e){return e == field::kind::space;})) return true;
    return false;
  }

  field                   board_;
  std::size_t             finish_length_;
  point                   current_put_ {invalid_point};
  std::unique_ptr<player> player1_;
  std::unique_ptr<player> player2_;
  player*                 active_player_;
};

int main(int argc, char** argv)
{
  std::ios_base::sync_with_stdio(false);
  std::unique_ptr<player> player1 {new human_player};
  std::unique_ptr<player> player2 {new computer_player};
  if (argc > 1) {
    using namespace std::literals::string_literals;
    if (argv[1] == "--auto"s)
      player1.reset(new computer_player);
    if (argv[1] == "--player"s)
      player2.reset(new human_player);
    if (argv[1] == "--com"s)
      ; // not working
  }
  std::size_t finish_size {5};
  if (argc > 2)
    finish_size = std::stoul(argv[2]);
  std::size_t board_size {9};
  if (argc > 3)
    board_size = std::stoul(argv[3]);

  game_master master {std::move(player1), std::move(player2), point{board_size, board_size}, finish_size};
  master.run();
}
