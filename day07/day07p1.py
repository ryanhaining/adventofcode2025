import sys

beams: set[int] = {input().index('S')}

count = 0
for line in sys.stdin:
    next_beams: set[int] = set()
    for p in beams:
        if line[p] == '^':
            count += 1
            next_beams.add(p - 1)
            next_beams.add(p + 1)
        else:
            next_beams.add(p)
    beams = next_beams

print(count)
