#include <array>
#include <cmath>
#include <functional>
#include <iostream>

using DataType = double;
constexpr DataType offset{0.01};

namespace Vector {
  enum { x = 0, y = 1, z = 2 };

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
    DataType size() const
    {
      DataType sizesq{0};
      for (const auto& e : elem_) sizesq += e*e;
      return std::sqrt(sizesq);
    }
    void show() const
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
    return {k * A[x], k * A[y], k * A[z]};
  }
  Vector operator*(const Vector& A, DataType k)
  {
    return k * A;
  }
  Vector cross(const Vector& lhs, const Vector& rhs)
  {
    return {
      lhs[y]*rhs[z] - lhs[z]*rhs[y],
        lhs[z]*rhs[x] - lhs[x]*rhs[z],
        lhs[x]*rhs[y] - lhs[y]*rhs[x]
        };
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
    dir[0] = offset;
    dir[1] = route.func(pos[0] + offset) - route.func(pos[0]);
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
  const DataType k{1/(4 * M_PI * std::pow(R.size(), 3))};
  return k * cross(I.dir / I.dir.size() , R);
}

Vector::Vector polarToRectangular(DataType radian, DataType theta)
{
  return {radian * std::cos(theta), radian*std::sin(theta)};
}

int main ()
{
  {
    // Vector::Vector r{0, 0, 0};
    // ElectricCurrent I1{{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
    // ElectricCurrent I2{{-1.0, 0.0, 0.0}, {0.0, -1.0, 0.0}};
    // Vector::Vector B{biotSavart(r, I1)};
    // B.show();
    // B += biotSavart(r, I2);
    // B.show();
  }
  {
    Vector::Vector r{}, B{};
    Route route1{[](DataType x){ return std::sqrt(1 - x*x); }, {0.0, 1.0}};
    ElectricCurrent I{route1};
    for (DataType x{route1.domain.begin}; x < route1.domain.end - offset; x += offset) {
      //     I.pos.show();
      I.setDirection();
      B += biotSavart(r, I);
      I.setPosition();
      B.show();
    }
  }
  return 0;
}
