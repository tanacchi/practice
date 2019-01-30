#include <iostream>

class Outer
{
  public:
    void yell()
    {
      std::cout << "Hello" << std::endl;
    }

    class Inner
    {
      public:
        static int value;

        void hello()
        {
          // this->yell();  // Can't call this.
          std::cout << value << std::endl;
          std::cout << Outer::value << std::endl;
        }
    };

    Inner inner;
    static int value;
};

int Outer::value = 8;
int Outer::Inner::value = 10;

int main()
{

  Outer obj;
  obj.inner.hello();

  return 0;
}
