import dataclasses
import sys


@dataclasses.dataclass(frozen=True)
class BeamState:
    row: int
    col: int


start = BeamState(row=0, col=input().index('S'))
grid = [line.rstrip() for line in sys.stdin]

state_to_count: dict[BeamState, int] = {}


def count_paths(beam: BeamState) -> int:
    if beam in state_to_count:
        return state_to_count[beam]

    if beam.row == len(grid):
        state_to_count[beam] = 1
        return 1

    if grid[beam.row][beam.col] == '^':
        count = count_paths(BeamState(beam.row + 1, beam.col - 1)) + count_paths(
            BeamState(beam.row + 1, beam.col + 1)
        )
        state_to_count[beam] = count
        return count
    else:
        assert grid[beam.row][beam.col] == '.'
        count = count_paths(BeamState(beam.row + 1, beam.col))
        return count


print(count_paths(start))
