#include "day1_1.hpp"

#include <vector>

std::string day1_1(std::istream &input) {
  std::vector<int> list1, list2;
  int num1, num2;
  
  while(true) {
    input >> num1 >> num2;

    if (!input) break;
    
    list1.push_back(num1);
    list2.push_back(num2);
  }
  
  std::sort(list1.begin(), list1.end());
  std::sort(list2.begin(), list2.end());
  
  int diff = 0;

  for (size_t i = 0; i < list1.size(); ++i) {
    diff += std::abs(list1[i] - list2[i]);
  }

  return std::to_string(diff);
}
