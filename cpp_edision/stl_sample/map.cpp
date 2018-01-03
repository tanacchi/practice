#include <iostream>
#include <map>

int main()
{
  const std::map<const unsigned short, const std::string> month_map = {
    {1, "January"},  {2, "February"},  {3, "March"},
    {4, "April"},    {5, "May"},       {6, "June"},
    {7, "July"},     {8, "August"},    {9, "September"},
    {10, "October"}, {11, "November"}, {12, "December"}
  };
  int input_month{};
  std::cin >> input_month;
  std::cout << month_map.at(input_month) << std::endl;
  return 0;
}
