import itertools
import fileinput


compass = {
    'W': (-1, 0),
    'E': (1, 0),
    'S': (0, -1),
    'N': (0, 1),
}


def plus(p1, p2):
    return (p1[0] + p2[0], p1[1] + p2[1])


def d(pnone, p2):
    x = abs(pnone[0] - p2[0]) if pnone[0] else 0
    y = abs(pnone[1] - p2[1]) if pnone[1] else 0
    return x+y


def movestowards(c, pers):
    curr, direction = pers[:2], pers[2]
    if d(c, curr) > d(c, plus(curr, compass[direction])): return 1
    return 0


def f(people, q):
    cand = []
    for (x, y, d) in people:
        if d == 'S':
            c = (None, y - 1)
        elif d == 'N':
            c = (None, y + 1)
        elif d == 'W':
            c = (x - 1, None)
        else: #  d == 'E'
            c = (x + 1, None)
        cand.append([c, 0])


    for c in cand:
        for p in people:
            c[1] += movestowards(c[0], p)

    cand.sort(
    print('cands:')
    print('\n'.join(str(c) for c in cand))

if __name__ == '__main__':
    T = int(input())
    for __ in range(T):
        pnum, q = [int(i) for i in input().split(' ')]
        people = []
        for __ in range(pnum):
            temp = input().split(' ')
            people.append(
                (int(temp[0]), int(temp[1]), temp[2],)
            )
        f(people, q)


