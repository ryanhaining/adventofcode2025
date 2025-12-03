#include <algorithm>
#include <iostream>
#include <string>

int main() {
  std::string line{};
  int total{};
  while (std::getline(std::cin, line)) {
    auto first_digit = std::max_element(line.begin(), line.end() - 1);
    auto second_digit = std::max_element(first_digit + 1, line.end());
    total += (*first_digit - '0') * 10 + (*second_digit - '0');
  }
  std::cout << total << '\n';
}
