import sys

n = 50
count = 0
for line in sys.stdin:
    turn = int(line.replace('L', '-').replace('R', ''))
    n += turn
    if n % 100 == 0:
        count += 1
print(count)

