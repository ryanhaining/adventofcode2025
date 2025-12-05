#include <stdio.h>

int main(void) {
  int current = 50;
  char direction = 0;
  int amount = 0;
  int zero_count = 0;
  while (scanf("%c%d\n", &direction, &amount) > 0) {
    if (direction == 'L') {
      amount *= -1;
    }
    current += amount;
    if (current % 100 == 0) {
      ++zero_count;
    }
  }
  printf("%d\n", zero_count);
}
