import sys


def sum_invalid_ids(low: int, high: int) -> int:
    return sum(
        int(s)
        for s in (str(n) for n in range(low, high + 1))
        if s[: len(s) // 2] == s[len(s) // 2 :]
    )


def read_ranges() -> list[tuple[int, int]]:
    return [
        tuple(int(n) for n in rng.split('-'))
        for rng in sys.stdin.read().replace('\n', '').split(',')
    ]


def main():
    print(sum(sum_invalid_ids(*rng) for rng in read_ranges()))


if __name__ == '__main__':
    main()
