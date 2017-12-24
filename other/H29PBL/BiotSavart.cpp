#include <array>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>

using DataType = double;
constexpr DataType offset_size{0.0001};

enum index : std::size_t { x = 0, y = 1, z = 2 };

namespace Vector {
  enum : std::size_t { Demention = 3 };
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
      for (auto i{0u}; i < Demention; ++i) elem_[i] += rhs.elem_[i];
      return *this;
    }
    Vector& operator-=(const Vector& rhs)
    {
      for (auto i{0u}; i < Demention; ++i) elem_[i] -= rhs.elem_[i];
      return *this;
    }
    Vector& operator*=(const Vector& rhs)
    {
      for (auto i{0u}; i < Demention; ++i) elem_[i] *= rhs.elem_[i];
      return *this;
    }
    Vector& operator/=(const Vector& rhs)
    {
      for (auto i{0u}; i < Demention; ++i) elem_[i] /= rhs.elem_[i];
      return *this;
    }
    DataType size() const
    {
      DataType sizesq{};
      for (const auto& e : elem_) sizesq += e*e;
      return std::sqrt(sizesq);
    }
    void show(std::ostream& stream) const
    {
      stream << elem_[index::x] << '\t'
             << elem_[index::y] << '\t'
             << elem_[index::z] << std::endl;
    }
  private:
    std::array<DataType, Demention> elem_;
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
  Domain(DataType b = 0.0, DataType e = 0.0)
    : begin{b}, end{e}
  {
  }
  DataType begin;
  DataType end;
};

struct Route {
  using FuncType = std::function<DataType(DataType)>;
  Route(FuncType f, Domain d)
    : func{f},
      domain{d},
      offset{offset_size * (domain.begin < domain.end ? 1.0 : -1.0)},
      xnum{(domain.end - domain.begin)/offset}
  {
  }
  FuncType func;
  Domain domain;
  DataType offset;
  DataType xnum;
};

struct ElectricCurrent {
  ElectricCurrent(Route r, DataType i = 1.0)
    : route{r}, intensity{i}
  {
    setPosition(Vector::Vector{route.domain.begin, route.func(route.domain.begin)});
    setDirection();
  }
  void setPosition()
  {
    pos += dir;
  }
  void setDirection()
  {
    dir[index::x] = route.offset;
    dir[index::y] = route.func(pos[index::x] + route.offset) - route.func(pos[index::x]);
  }
  void setPosition(Vector::Vector p)
  {
    pos = p;
  }
  void setDirection(Vector::Vector d)
  {
    dir = d;
  }
  Vector::Vector pos;
  Vector::Vector dir;
  Route route;
  DataType intensity;
};

Vector::Vector biotSavart(const Vector::Vector& r, const ElectricCurrent& I)
{
  const Vector::Vector R{r - I.pos};
  const DataType k{I.intensity/(4 * M_PI * std::pow(R.size(), 3))};
  return k * Vector::cross(I.dir, R);
}

Vector::Vector getMagneticVector(const Vector::Vector& r, ElectricCurrent I)
{
  Vector::Vector B{};
  for (auto i{0u}; i < I.route.xnum; I.setPosition(), I.setDirection(), ++i)
    B += biotSavart(r, I);
  return B;
}

int main ()
{
  { // Mission 1
    const Vector::Vector r{0.0, 0.0, 0.0};
    Route route1{[](DataType x){ return std::sqrt(1 - x*x); }, {-1.0, 1.0}};
    Route route2{[](DataType x){ return -std::sqrt(1 - x*x); }, {1.0, -1.0}};
    ElectricCurrent I1{route1, 1.0};
    ElectricCurrent I2{route2, 1.0};
    Vector::Vector B;
    B += getMagneticVector(r, I1);    
    B += getMagneticVector(r, I2);    
    std::fstream fstream{"data1.dat", std::ios_base::out | std::ios_base::trunc};
    B.show(fstream);
    B.show(std::cout);
  }
  { // Mission 2
    const Vector::Vector r{0.0, 0.0, 0.0};
    constexpr DataType a{1.0};
    Route route1{[&](DataType x){ return a*x*x - a; }, {-1.0, 1.0}};
    ElectricCurrent I1{route1, 1.0};
    Vector::Vector B;
    B += getMagneticVector(r, I1);
    B.show(std::cout);    
  }
  return 0;
}
