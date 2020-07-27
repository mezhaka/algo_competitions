import fileinput
import functools
import math
from collections import Counter


def solve2(shards):
    N = len(shards)

    @functools.lru_cache(maxsize=None)
    def f(shards):
        if len(shards) == 1:
            return shards
        elif len(shards) == 3:
            stats = Counter(shards)
            if 'X' in stats: return 'X'
            color, num = stats.most_common(1)[0]
            if num == 3: return 'X'
            return color
        else:
            for pivot in range(1, len(shards)-1, 2):
                l = shards[:pivot]
                r = shards[pivot + 1:]
                cand = f('{}{}{}'.format(f(l), shards[pivot], f(r)))
                if cand != 'X': # is it possible to contract the same string to different options? if it is, then I need to continue search here
                    return cand
        return 'X'

    return 'Y' if f(shards) != 'X' else 'N'


def solve(shards):
    def fuse(shards):
        stats = Counter(shards)
        color, num = stats.most_common(1)[0]
        #print('color: ', color, 'num: ', num)
        if num == 3: return 'X'
        return color
    shards = list(shards)
    newshards = shards.copy()
    while True:
        shards, newshards = newshards, shards
        newshards.clear()
        i = 0
        while i <= len(shards) - 3:
            fused = fuse(shards[i : i+3])
            if fused == 'X':
                i += 1
                newshards.append(shards[i])
            else:
                i += 3
                newshards.append(fused)
        newshards.extend(shards[i:])
        if len(newshards) == 1: return 'Y'
        if len(newshards) == len(shards): return 'N'
    return 'Y' if len(newshards) == 1 else 'N'


if __name__ == '__main__':
    lines = fileinput.input()
    total_casenum = int(next(lines))
    for casenum in range(1, total_casenum + 1):
        _, shards = next(lines), next(lines).strip()
        print('Case #{}: {}'.format(casenum, solve(shards)))


