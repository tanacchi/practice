#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

class Super
{
public:
  Super(int a = {}, int b = {}, int c = {})
    : a{a}, b{b}, c{c}
  {
  }

  int a;
  int b;
  int c;
  
  virtual std::string write() const
  {
    std::stringstream ss;
    ss <<   "a = " << a 
       << ", b = " << b 
       << ", c = " << c << "\n";
    return ss.str();
  }

  friend std::ostream& operator<<(std::ostream& os, const Super& super)
  {
    return os << super.write();
  }
};

class Sub : public Super 
{
  public:
    Sub(int a, int b, int c, int d, int e)
      : Super(a, b, c),
        d{d}, e{e}
    {
    }

    int d;
    int e;

    std::string write() const
    {
      std::stringstream ss;
      ss << Super::write() 
         <<   "d = " << d 
         << ", e = " << e;
      return ss.str();
    }
};

int main()
{
  Super super(1, 2, 3);
  Sub sub(1, 2, 3, 4, 5);

  std::cout << super << "=========\n" << sub << std::endl;
  return 0;
}
