import sys


def surrounding_count(grid: list[list[bool]], row: int, col: int) -> int:
    return sum(
        grid[r][c] and (r != row or c != col)
        for r in range(max(row - 1, 0), min(row + 2, len(grid)))
        for c in range(max(col - 1, 0), min(col + 2, len(grid[row])))
    )


def main():
    grid = [[c == '@' for c in line.rstrip()] for line in sys.stdin]
    total = sum(
        pos and surrounding_count(grid, row_index, col_index) < 4
        for row_index, row in enumerate(grid)
        for col_index, pos in enumerate(row)
    )

    print(total)


if __name__ == '__main__':
    main()
