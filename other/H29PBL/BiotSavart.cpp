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

int main ()
{
  {
    Vector::Vector v1{3.3, 2.1, 5.9};
    v1 -= Vector::Vector{1.1, 1.1, 1.1};
    v1.show();
  }
  {
    Vector::Vector v2{1.0, 0.0, 0.0};
    Vector::Vector v3{0.0, 1.0, 0.0};
    (v2*v3).show();
  }
  return 0;
}
