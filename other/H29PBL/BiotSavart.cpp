#include <array>
#include <cmath>
#include <functional>
#include <iostream>

using DataType = double;
constexpr DataType offset{0.01};

namespace Vector {
  enum class index { x = 0, y = 1, z = 2 };

  class Vector {
  public:
    Vector(DataType x = {}, DataType y = {}, DataType z = {})
      : elem_{x, y, z}
    {
    }
    const DataType& operator[](int n) const 
    {
      return elem_[n];
    }
    DataType& operator[](int n)
    {
      return elem_[n];
    }
    Vector& operator+=(const Vector& rhs)
    {
      for (auto i{0u}; i < elem_.size(); ++i) elem_[i] += rhs.elem_[i];
      return *this;
    }
    Vector& operator-=(const Vector& rhs)
    {
      for (auto i{0u}; i < elem_.size(); ++i) elem_[i] -= rhs.elem_[i];
      return *this;
    }
    Vector& operator*=(const Vector& rhs)
    {
      for (auto i{0u}; i < elem_.size(); ++i) elem_[i] *= rhs.elem_[i];
      return *this;
    }
    void show()
    {
      std::cout << "========================" << std::endl;
      std::cout << "x = " << elem_[index::x] << '\n'
                << "y = " << elem_[index::y] << '\n'
                << "z = " << elem_[index::z] << '\n' << std::flush;
      std::cout << "========================" << std::endl;
    }
  private:
    std::array<DataType, 3> elem_;
  };
  Vector operator+(Vector A, const Vector& B)
  {
    return A += B;
  }
  Vector operator-(Vector A, const Vector& B)
  {
    return A -= B;
  }
  Vector operator*(Vector A, const Vector& B)
  {
    return A *= B;
  }
  Vector operator*(DataType k, const Vector& A)
  {
    return {k * A[index::x], k * A[index::y], k * A[index::z]};
  }
  Vector operator*(const Vector& A, DataType k)
  {
    return k * A;
  }
  DataType size(const Vector& A)
  {
    return std::sqrt(A * A);
  }
};

struct Domain {
  DataType begin;
  DataType end;
};

struct Route {
  std::function<DataType(DataType)> func;
  Domain domain;
};

struct ElectricCurrent {
  ElectricCurrent(Vector::Vector p, Vector::Vector d, DataType i = 1.0)
    : pos{p}, dir{d}, intensity{i}
  {
  }
  ElectricCurrent(Route r, DataType i = 1.0)
    : route{r}, intensity{i}
  {
    pos[0] = route.domain.begin;
    pos[1] = route.func(route.domain.begin);
    setDirection();
  }
  void setDirection()
  {
    DataType xoffset{(route.domain.end - route.domain.begin) * offset};
    dir[0] = xoffset;
    dir[1] = route.func(pos[0] + xoffset) - route.func(pos[0]);
  }
  void setPosition()
  {
    pos += dir;
  }
  Vector::Vector pos;
  Vector::Vector dir;
  Route route;
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
  {
    // Vector::Vector r{0, 0, 0};
    // ElectricCurrent I{{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
    // ElectricCurrent I2{{-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
    // Vector::Vector B{biotSavart(r, I1)};
    // B.show();
    // B += biotSavart(r, I2);
    // B.show();
  }
  {
    Vector::Vector r{}, B{};
    Route route1{[](DataType x){ return std::sqrt(1 - x*x); }, {-1.0, 1.0}};
    ElectricCurrent I{route1};
    while (I.pos[0] < route1.domain.end) {
      B += biotSavart(r, I);
      I.setPosition();
      I.setDirection();
      B.show();
    }
    B.show();
  }
  return 0;
}
