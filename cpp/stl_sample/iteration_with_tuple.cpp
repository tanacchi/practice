#include <tuple>
#include <iostream>

template<typename Head, typename... Tails>
class List
{
  public:
    List(Head head, Tails... tails)
      : head_{head},
        tails_{std::make_tuple<Tails...>(std::forward<Tails>(tails)...)}
    {
    }

    template<std::size_t I = 0>
    auto print_tails() -> typename std::enable_if<I == sizeof...(Tails), void>::type
    { }

    template<std::size_t I = 0>
    auto print_tails() -> typename std::enable_if<I < sizeof...(Tails), void>::type
    {
      std::cout << std::get<I>(tails_) << std::endl;
      print_tails<I+1>();
    }

    template<std::size_t I = 0>
    auto print_head() -> typename std::enable_if<I == 0, void>::type
    {
      std::cout << head_ << std::endl;
    }

  private:
    Head head_;
    std::tuple<Tails...> tails_;
};

int main()
{
  List<int, int, int, char, int, int, int> list(1, 2, 3, 'c', 5, 6, 7);
  list.print_tails();

  return 0;
}
