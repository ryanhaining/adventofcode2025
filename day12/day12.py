"""
There's three cases:

1.  The tree doesn't have enough area to fit all the individual pieces of the
    gifts, that is, the area is less than the total number of #
2.  The tree has enough area to fit all the gifts without any squeezing, just all
    aligned in a 3x3 grid
3.  The tree tree can fit all the gifts with some compression.

It turns out that case 3 occurs 0 times.
"""

import sys

GIFT_DIM = 3


def read_gift_area() -> int:
    sys.stdin.readline()  # skip id number
    area = sum(sys.stdin.readline().count('#') for _ in range(GIFT_DIM))
    sys.stdin.readline()  # skip blank
    return area


def parse_dims(line: str) -> tuple[int, int]:
    n1, n2 = line.split(':')[0].split('x')
    return int(n1), int(n2)


def parse_gift_reqs(line: str) -> list[int]:
    return [int(n) for n in line.split(':')[1].strip().split()]


def rounded(dim: int) -> int:
    return dim - (dim % GIFT_DIM)


def main():
    gifts = [read_gift_area() for _ in range(6)]
    big_enough = 0
    for line in sys.stdin:
        n1, n2 = parse_dims(line)
        total_area = n1 * n2
        gift_reqs = parse_gift_reqs(line)
        rounded_area = rounded(n1) * rounded(n2)
        uncompressed_area = sum(gift_reqs) * GIFT_DIM**2
        if uncompressed_area <= rounded_area:
            big_enough += 1
        else:
            # Making sure there's no case 3 tree
            area_req = sum(r * a for r, a in zip(gift_reqs, gifts))
            if area_req <= total_area:
                raise ValueError(f'Tree might be able to fit gifts if arranged: {line}')
    print(big_enough)


if __name__ == '__main__':
    main()
