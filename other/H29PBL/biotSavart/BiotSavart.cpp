#include <array>
#include <cmath>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <vector>

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
  using FuncType = std::function<Vector::Vector(DataType)>;
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
    setPosition(Vector::Vector{route.func(route.domain.begin)});
    setDirection();
  }
  void setPosition()
  {
    pos += dir;
  }
  void setDirection()
  {
    dir = route.func(pos[index::x] + route.offset) - route.func(pos[index::x]);
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

Vector::Vector getMagneticVector(const Vector::Vector& r, std::initializer_list<ElectricCurrent> I)
{
  Vector::Vector H{};
  for (auto i : I)
    for (auto x{0u}; x < i.route.xnum; i.setPosition(), i.setDirection(), ++x)
      H += biotSavart(r, i);
  return H;
}

int main (int argc, char** argv)
{
  const Route route1{[](DataType t){ return Vector::Vector{t,  std::sqrt(1 - t*t), 0}; }, {-1.0, 1.0}};
  const Route route2{[](DataType t){ return Vector::Vector{t, -std::sqrt(1 - t*t), 0}; }, {1.0, -1.0}};
  const ElectricCurrent I1{route1, 1.0}; const ElectricCurrent I2{route2, 1.0};
  std::fstream fstream{"mission1.dat", std::ios_base::out | std::ios_base::trunc};
  for (Vector::Vector r{-3.0, -3.0, 0.0}; r[index::x] < 3.0; r[index::x] += 0.1)
    for (r[index::y] = -3.0; r[index::y] < 3.0; r[index::y] += 0.1) {
      for (r[index::z] = -3.0; r[index::z] < 3.0; r[index::z] += 1) {
        Vector::Vector H{getMagneticVector(r, {I1, I2})};
        fstream << r[index::x] << '\t' << r[index::y] << '\t' << r[index::z] << '\t' 
                << H[index::x] << '\t' << H[index::y] << '\t' << H[index::z] << std::endl;
      }
    }
  fstream << std::endl;
  return 0;
}
