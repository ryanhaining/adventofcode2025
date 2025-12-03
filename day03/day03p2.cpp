#include <algorithm>
#include <iostream>
#include <string>

constexpr int NUM_DIGITS = 12;

int main() {
  std::string line{};
  long total{};
  while (std::getline(std::cin, line)) {
    long current_joltage{};
    auto remaining_begin = line.begin();
    for (int i = NUM_DIGITS - 1; i >= 0; --i) {
      current_joltage *= 10;
      auto cur_digit = std::max_element(remaining_begin, line.end() - i);
      current_joltage += *cur_digit - '0';
      remaining_begin = cur_digit + 1;
    }
    total += current_joltage;
  }
  std::cout << total << '\n';
}
