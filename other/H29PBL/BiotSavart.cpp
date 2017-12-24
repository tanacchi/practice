#include <array>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <vector>

using DataType = double;
constexpr DataType offset_size{0.0001};

enum index : std::size_t { x = 0, y = 1, z = 2 };

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
  Domain(DataType b = 0.0, DataType e = 0.0)
    : begin{b}, end{e}, offset{offset_size * (begin < end ? 1.0 : -1.0)}
  {
  }
  DataType begin;
  DataType end;
  DataType offset;
};

struct Route {
  using FuncType = std::function<DataType(DataType)>;
  Route(FuncType f, Domain d)
    : func{f}, domain{d}
  {
    const DataType xlist_size{(domain.end - domain.begin)/domain.offset};
    for (DataType i{0}, x{domain.begin}; i < xlist_size; ++i, x += domain.offset) xlist.push_back(x);
  }
  FuncType func;
  Domain domain;
  std::vector<DataType> xlist;
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
    dir[index::x] = route.domain.offset;
    dir[index::y] = route.func(pos[index::x] + route.domain.offset) - route.func(pos[index::x]);
  }
  void setPosition(Vector::Vector p)
  {
    pos = p;
  }
  void setDirection(Vector::Vector d)
  {
    dir = d;
  }
  void update()
  {
    setPosition();
    setDirection();
  }
  Vector::Vector pos;
  Vector::Vector dir;
  Route route;
  const DataType intensity;
};

Vector::Vector biotSavart(const Vector::Vector& r, const ElectricCurrent& I)
{
  const Vector::Vector R{r - I.pos};
  const DataType k{I.intensity/(4 * M_PI * std::pow(R.size(), 3))};
  return k * cross(I.dir, R);
}

Vector::Vector getMagneticVector(const Vector::Vector& r, ElectricCurrent I)
{
  Vector::Vector B{};
  const std::size_t xnum{I.route.xlist.size()};
  for (auto i{0u}; i < xnum; ++i) {
    B += biotSavart(r, I);
    I.update();
  }
  return B;
}

int main ()
{
  { // Mission 1
    const Vector::Vector r{0.0, 0.0, 0.0};
    Route route1{[](DataType x){ return std::sqrt(1 - x*x); }, {1.0, -1.0}};
    Route route2{[](DataType x){ return -std::sqrt(1 - x*x); }, {1.0, -1.0}};
    ElectricCurrent I1{route1, 1.0};
    Vector::Vector B;
    B += getMagneticVector(r, I1);
    std::fstream fstream{"data1.dat", std::ios_base::out | std::ios_base::trunc};
    B.show(fstream);
    B.show(std::cout);
  }
  { // Mission 2
    // const Vector::Vector r{0.0, 0.0, 0.0};
    // constexpr DataType a{1.0};
    // Route route1{[&](DataType x){ return a*x*x - a; }, {-1.0, 1.0}};
    // ElectricCurrent I1{route1, 1.0};
    // Vector::Vector B;
    // B += getMagneticVector(r, I1);
    // B.show(std::cout);    
  }
  return 0;
}
