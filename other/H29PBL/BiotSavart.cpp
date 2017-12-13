#include <array>
#include <iostream>
#include <cmath>

using DataType = double;

namespace Vector {
  enum { x = 0, y = 1, z = 2 };
  
  constexpr DataType myu = 4 * M_PI * std::pow(10, -7); // [H/m]
  
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
  Vector operator*(DataType k, const Vector A)
  {
    return {k * A[x], k * A[y], k * A[z]};
  }
  Vector operator*(const Vector A, DataType k)
  {
    return k * A;
  }
  DataType size(Vector A)
  {
    return std::sqrt(A[x]*A[x] + A[y]*A[y] + A[z]*A[z]);
  }
};

struct ElectricCurrent {
  ElectricCurrent(Vector::Vector p = {0.0, 0.0, 0.0},
                  Vector::Vector d = {0.0, 0.0, 0.0},
                  DataType i = 1.0)
    : pos{p}, dir{d}, intensity{i}
  {
  }
  Vector::Vector pos;
  Vector::Vector dir;
  const DataType intensity;
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

Vector::Vector biotSavart(Vector::Vector r, ElectricCurrent I)
{
  Vector::Vector R{r - I.pos};
  const DataType k{1/(4 * M_PI * std::pow(size(R), 3))};
  return k * I.dir * R;
}

int main ()
{
  // test([](DataType x){ return std::sqrt(1.0 - x*x); });
  Vector::Vector r{0, 0, 1};
  ElectricCurrent I{{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, 1};
  Vector::Vector B = biotSavart(r, I);
  B.show();
  return 0;
}
