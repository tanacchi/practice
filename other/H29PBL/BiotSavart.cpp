#include <array>
#include <cmath>
#include <functional>
#include <iostream>

using DataType = double;
constexpr DataType offset{0.0001};

enum index : std::size_t {
  x = 0,
  y = 1,
  z = 2
};

namespace Vector {
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
    Vector& operator/=(const Vector& rhs)
    {
      for (auto i{0u}; i < elem_.size(); ++i) elem_[i] /= rhs.elem_[i];
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
      std::cout << "========================" << '\n'
                << "x = " << elem_[index::x]  << '\n'
                << "y = " << elem_[index::y]  << '\n'
                << "z = " << elem_[index::z]  << '\n'
                << "========================" << std::endl;
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
  Vector operator/(Vector A, const Vector& B)
  {
    return A /= B;
  }
  Vector operator/(const Vector& A, DataType k)
  {
    return {A[index::x] / k, A[index::y] / k, A[index::z] / k};
  }
  Vector cross(const Vector& lhs, const Vector& rhs)
  {
    return {
      lhs[index::y]*rhs[index::z] - lhs[index::z]*rhs[index::y],
      lhs[index::z]*rhs[index::x] - lhs[index::x]*rhs[index::z],
      lhs[index::x]*rhs[index::y] - lhs[index::y]*rhs[index::x]
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
    pos[index::x] = route.domain.begin;
    pos[index::y] = route.func(route.domain.begin);
    setDirection();
  }
  void setDirection()
  {
    dir[index::x] = offset;
    dir[index::y] = route.func(pos[index::x] + offset) - route.func(pos[index::x]);
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
  return k * cross(I.dir / I.dir.size(), R);
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
    // Route route1{[](DataType x){ return std::sqrt(1.0 - x*x); }, {-1.0, 1.0}};
    // ElectricCurrent I1{route1};
    // for (DataType x{route1.domain.begin}; x < route1.domain.end - offset; x += offset) {
    //   I1.setDirection();
    //   B += biotSavart(r, I1) * offset;
    //   I1.setPosition();
    //   B.show();
    // }
    Route route2{[](DataType x){ return -1 * std::sqrt(1.0 - x*x); }, {1.0, -1.0}};
    ElectricCurrent I2{route2};
    for (DataType x{route2.domain.begin - offset}; x > route2.domain.end; x -= offset) {
      I2.setDirection();
      B += biotSavart(r, I2) * offset;
      I2.setPosition();
      B.show();
    }
  }
  return 0;
}
