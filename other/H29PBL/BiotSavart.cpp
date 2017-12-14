#include <array>
#include <cmath>
#include <functional>
#include <iostream>

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
  ElectricCurrent(Vector::Vector p, Vector::Vector d, DataType i = 1.0)
    : pos{p}, dir{d}, intensity{i}
  {
  }
  Vector::Vector pos;
  Vector::Vector dir;
  const DataType intensity;
};

Vector::Vector biotSavart(Vector::Vector r, ElectricCurrent I)
{
  Vector::Vector R{r - I.pos};
  const DataType k{1/(4 * M_PI * std::pow(Vector::size(R), 3))};
  return k * I.dir * R;
}

int main ()
{
  Vector::Vector r{0, 0, 1};
  ElectricCurrent I{{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
  Vector::Vector B{biotSavart(r, I)};
  B.show();
  B += biotSavart(r, {{-1.0, 0.0, 0.0}, {0.0, -1.0, 0.0}});
  B.show();
  return 0;
}
