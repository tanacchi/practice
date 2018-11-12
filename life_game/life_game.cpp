#include <iostream>
#include <array>
#include <random>
#include <chrono>
#include <thread>

class Cell
{
public:
  Cell(bool is_alive = false)
    : is_alive_{is_alive}
  {
  }

  char to_char() const
  {
    return is_alive_ ? 'O' : ' ';
  }

  bool is_alive() const
  {
    return is_alive_;
  }
  
  void revive()
  {
    is_alive_ = true;
  }

  void kill()
  {
    is_alive_ = false;
  }
private:
  bool is_alive_;
};

class LifeField
{
public:
  LifeField()
    : seed_gen_{},
      random_engine_{seed_gen_()},
      dist_{0, 1}
  { 
    for (auto& row : field_)
    {
      for (auto& elem : row)
      {
        if (dist_(random_engine_))
          elem.revive();
      }
    }
  }   

  void show() const
  {
    std::cout << "===============================" << std::endl;
    for (auto row : field_)
    {
      for (auto elem : row)
      {
        std::cout << ' ' << elem.to_char();
      }
      std::cout << std::endl;
    }
    std::cout << "===============================" << std::endl;
  }

  bool in_range(int x, int y) const
  {
    return (0 <= x && x < field_[0].size()) && (0 <= y && y <= field_.size());
  }
  
  void toggle_cell(std::size_t x, std::size_t y)
  {
    static const std::array<const std::pair<int, int>, 8ul > dirs{
      {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}}
    };

    std::size_t arrive_neighbor_count{0};
    for (const auto& dir : dirs)
    {
      if (!in_range(x + dir.first, y + dir.second))
      {
        continue;
      }
      if (field_[y + dir.second][x + dir.first].is_alive())
      {
        ++arrive_neighbor_count;
      }
    }

    Cell& target{field_[y][x]};
    if (target.is_alive())
    {
      if (arrive_neighbor_count <= 1 || 4 <= arrive_neighbor_count)
      {
        target.kill();
      }
    } else {
      if (arrive_neighbor_count == 3)
      {
        target.revive();
      }
    }
  }

  void update()
  {
    for (std::size_t y{0}; y < field_.size(); ++y)
    {
      for (std::size_t x{0}; x < field_[y].size(); ++x)
      {
        toggle_cell(x, y);
      }
    }
  }
private:
  std::random_device seed_gen_;
  std::default_random_engine random_engine_;
  std::uniform_int_distribution<> dist_;
  std::array<std::array<Cell, 5>, 5> field_;
};

int main()
{
  LifeField life_field{};

  while (true)
  {
    life_field.show();
    life_field.update();
    std::this_thread::sleep_for(std::chrono::seconds(3));
  }
  return 0;
}
