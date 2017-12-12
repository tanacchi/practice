#include <iostream>
#include <cmath>

using DataType = double;

namespace {

  class Vector {
  public:
    Vector(DataType x = 0.0, DataType y = 0.0, DataType z = 0.0)
      : elem_{x , y, z}
    {
    }
    const Vector& operator-=(const Vector& rhs) const
    {
    }
  private:
    enum { x = 0, y = 1, z = 2; };
    DataType elem_[3];
  };

  
}

Vector getCross(Vector a, Vector b)
{
  Vector ans = {
    a.y*b.z - a.z*b.y,
    a.z*b.x - a.x*b.z,
    a.x*b.y - a*y*b.x;
  };
  return ans;
}

int main ()
{

  return 0;
}
