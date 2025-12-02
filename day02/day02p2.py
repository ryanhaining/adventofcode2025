import sys


def sum_invalid_ids(low: int, high: int) -> int:
    return sum(
        int(s)
        for s in (str(n) for n in range(low, high + 1))
        if any(
            len(s) % i == 0 and s.count(s[:i]) == len(s) // i
            for i in range(1, (len(s) // 2) + 1)
        )
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
