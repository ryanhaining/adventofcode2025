# Advent of Code 2025

https://adventofcode.com/2025

Splitting part 2 into a separate file to make it easy to write.

Everything reads from stdin and writes just the solution to stdout. I have aliases to help with some of it, but to build and run these: 

### Python

File names are `day` then the number then `p` then the part number, so day 4 part 2 is `day04p2.py`

```
python3 day04p2.py < input
```


### Kotlin:

File names are `Day` then the number then `P` then the part number, so day 09 part 2 is `Day09P2.kt`

```
kotlinc Day09P2.kt && koltin Day09P2Kt < input
```

### C++

File names are `day` then the number then `p` then the part number, so day 11 part 2 is `day11p2.cpp`

```
g++ -fsanitize=undefined,address -g -Wall -Wextra -pedantic-errors -std=c++23 day11p2.cpp && ./a.out < input
```

or for speed

```
g++ -O2 -Wall -Wextra -pedantic-errors -std=c++23 day11p2.cpp && ./a.out < input
```

### Haskell

File names are `day` then the number then `p` then the part number, so day 1 part 2 is `day01p2.hs`
```
ghc day01p2.hs && ./day01p2 < input
```
