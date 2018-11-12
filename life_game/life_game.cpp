#include <iostream>
#include <array>
#include <random>

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
    for (auto row : field_)
    {
      for (auto elem : row)
      {
        std::cout << ' ' << elem.to_char();
      }
      std::cout << std::endl;
    }
  }
private:
  std::random_device seed_gen_;
  std::default_random_engine random_engine_;
  std::uniform_int_distribution<> dist_;
  std::array<std::array<Cell, 30>, 30> field_;
};

int main()
{
  LifeField life_field{};

  life_field.show();
  return 0;
}
