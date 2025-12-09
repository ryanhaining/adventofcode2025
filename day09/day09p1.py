import sys

points = [tuple(int(n) for n in line.rstrip().split(',')) for line in sys.stdin]


def area(p1, p2):
    return (abs(p1[0] - p2[0]) + 1) * (abs(p1[1] - p2[1]) + 1)


print(max(area(p1, p2) for p1 in points for p2 in points))
