#include <iostream>
#include <memory>
#include <vector>

struct A
{
  void f()
  {
    std::cout << "I'm class A" << std::endl;
  }
};

struct B
{
  void f()
  {
    std::cout << "I'm class B" << std::endl;
  }
};

struct holder {
  virtual void f() = 0;
};

template<typename T>
struct holder_sub : public holder {
  holder_sub(const T& obj) : m_obj(obj) {}

  virtual void f() { m_obj.f(); }

  T m_obj;
};

struct anyf
{
  template<typename T> anyf(const T& a) { m_p.reset(new holder_sub<T>(a)); }

  void f() { m_p->f(); }

  std::shared_ptr<holder> m_p;
};

int main() {
  std::vector<anyf> objs;
  objs.push_back(A());
  objs.push_back(B());

  for (size_t i = 0; i < objs.size(); ++i) {
    objs[i].f();
  }
}
