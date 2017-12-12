#include <array>
#include <iostream>
#include <cmath>

using DataType = double;

namespace Vector {
  enum { x = 0, y = 1, z = 2 };
  class Vector {
  public:
    Vector(DataType x = 0.0, DataType y = 0.0, DataType z = 0.0)
      : elem_{x, y, z}
    {
    }
    const DataType& operator[](int n) const
    {
      return elem_[n];
    }
    const Vector& operator+=(const Vector rhs)
    {
      for (auto i{0}; i < elem_.size(); ++i) elem_[i] += rhs.elem_[i];
      return *this;
    }
    const Vector& operator-=(const Vector rhs)
    {
      for (auto i{0}; i < elem_.size(); ++i) elem_[i] -= rhs.elem_[i];
      return *this;
    }
    void show()
    {
      std::cout << "========================" << std::endl;
      std::cout << "x = " << elem_[x] << '\n'
                << "y = " << elem_[y] << '\n'
                << "z = " << elem_[z] << '\n' << std::flush;
      std::cout << "========================" << std::endl;
    }
  private:
    std::array<DataType, 3> elem_;
  };
  Vector operator+(const Vector A, const Vector B)
  {
    return {A[x] + B[x],  A[y] + B[y], A[z] + B[z]};
  }
  Vector operator-(const Vector A, const Vector B)
  {
    return {A[x] - B[x],  A[y] - B[y], A[z] - B[z]};
  }
  Vector operator*(const Vector A, const Vector B)
  {
    return {A[y]*B[z] - A[z]*B[y], A[z]*B[x] - A[x]*B[z], A[x]*B[y] - A[y]*B[x]};
  }
};

void circle()
{
  const DataType unit{M_PI/10};
  for (DataType theta{0}; theta <= M_PI; theta += unit) {
    std::cout << "-----------------" << std::endl;
    std::cout << "x = " << std::cos(theta) << '\n'
              << "y = " << std::sin(theta) << std::endl;
    std::cout << "-----------------" << std::endl;
  }
}

template <typename F>
void test(F func)
{
  for (DataType x{-1}; x < 1; x += 0.1) {
    DataType y = func(x);
    std::cout << "-----------------" << std::endl;
    std::cout << "x = " << x << '\n'
              << "y = " << y << std::endl;
    std::cout << "-----------------" << std::endl;
  }
}

int main ()
{
  test([](DataType x){ return std::sqrt(1.0 - x*x); });
  circle();
  return 0;
}
