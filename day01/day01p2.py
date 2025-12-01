import sys

MAX = 100

n = 50
count = 0
for line in sys.stdin:
    amount = int(line[1:])
    sign = -1 if line[0] == 'L' else 1
    count += amount // MAX
    turn = (amount % MAX) * sign

    prev = n
    n += turn
    if n % MAX == 0 or (prev % MAX != 0 and prev // MAX != n // MAX):
        count += 1
print(count)

