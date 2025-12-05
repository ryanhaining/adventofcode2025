import sys


def get_range(line: str) -> range:
    start, end = [int(n) for n in line.split('-')]
    assert end >= start
    return range(start, end + 1)


def main():
    ranges = [get_range(line) for line in iter(sys.stdin.readline, '\n')]
    print(sum(any(int(n) in r for r in ranges) for n in sys.stdin))


if __name__ == '__main__':
    main()
