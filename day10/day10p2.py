"""
I had to rely on another z3 solution to understand this.

This kind of linear problem always screws me up.

Unfortunately I lost the reddit comment that linked to this one, sorry for
not including the actual referenc, OP.

https://topaz.github.io/paste/#XQAAAQApCAAAAAAAAAARiEJHiiMzw3cPM/1Vl+2nx/DqKkM2yi+AsNSFTsn4BnEsfFjAFZsDftkxgA7sz32NiJ6DtB/mqz1IyhVTR9MIKAOiJ9THw3WzRCg/mioWWw8pJRPNsFdo5skZXbUZPJebMjkZQQv8OAxUQQPCc+j+HLraJPUoidaR1hPSfa+M3w0PMaGrdLBvbZVi0v6o4qxSO08uUc3lyPUKQl5angETKTs0iw4HjNuCoeuoPHmL3J2plfXt+Ozrr5nRkRiqg7bLoLKCTyE+k4DNwiYNbhHP/z1EQH0DYv8VwZAvzYhY1wQDsP53vl16OW6Pux3ixgiqiS4m2I/yoMArphb1/J7jreHldYHHu1APEXDg0dOBeqGE7yOW7FN2U8tcpTDep1GdHEo6Dh/Do1XWDAYPwthYf0Ffwlb2iVLNsyw6k2zJ1YbrpMZFus+n8SgrpLP2yrCqB3T0NvEptLmYTSF/N8JJqvRnBeCjoV8Z+YDrWn7smh/VJXt4NByJI/ZrGT7RxsqOgI3ecuJuBh2zM/laJRKVOP8GpvN1jIQ56HVBWyIbLPUPdKeL7qIvr+PeetJ6L414JoEpp85Ra8lbqs/+d/TDRLIgY2OIfC/5P0vMNPFIwj7kH5tudTEt1ZH1jUunBHTbq3O7YKP70I+VV8J35JZnm+XFdW99s49oV2jj6m+/f5iDyZjxlIlNRz3zEKDVezDYFDdXzlFiNtHalwdO15Y5If4DMJr4MSfX9oEzzTSydrt2BaD9ZYnOmIWctdDneUcU/9JBqHAmhjqYgS+VWRfBuIVGkSb4+M/bZB87uYNMhhqD+kTupNK5cjMvyr0EL4v3QarMbU63elaxwNF2mnMgv7uL/3SiP7ubWO6ya8wBAV4AfDKycQXJ1IUzfE3Wzq3+PxFGretCKK8eEQgy7k7G0eJ4Qle0/e+l4rqPswkOVkzR/vDXS4G8HkWatNWM7wVjdXtyXcDvnkm184IYksV6MvutpSIvfQ+EYPojJ60e1P28D9h3izd7Kks8/WhQN4g1EBWdmgPjvMHvfuLIpYT1L9UyqCow81NAejpaIUJWD6FHAERh/cVZq/E41MPCC6nGrmD4YVVM2nYGNAf/4YgBTw==
"""

import dataclasses
import sys
from z3 import z3


@dataclasses.dataclass
class Machine:
    switches: tuple[tuple[int, ...], ...]
    goal: tuple[int, ...]


def create_machine(line: str) -> Machine:
    _, *switches_strs, joltages_str = line.split()
    joltages = tuple(int(n) for n in joltages_str[1:-1].split(','))
    switches = tuple(
        tuple(int(n) for n in switch_str[1:-1].split(','))
        for switch_str in switches_strs
    )

    return Machine(switches, joltages)


def solve_machine(m: Machine) -> int:
    counters = [[] for _ in m.goal]
    for i, switch in enumerate(m.switches):
        for n in switch:
            counters[n].append(i)

    presses = z3.Int('presses')
    switch_vars = z3.IntVector('switch', len(m.switches))
    solver = z3.Optimize()

    for i, (counter, joltage) in enumerate(zip(counters, m.goal)):
        solver.add(sum(switch_vars[switch_pos] for switch_pos in counter) == joltage)

    for i, _ in enumerate(m.switches):
        solver.add(switch_vars[i] >= 0)

    solver.add(sum(switch_vars) == presses)
    solver.minimize(presses)

    solver.check()
    return solver.model().eval(presses).as_long()


def main():
    print(sum(solve_machine(create_machine(line)) for line in sys.stdin))


if __name__ == '__main__':
    main()
