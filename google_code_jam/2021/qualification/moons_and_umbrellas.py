import fileinput
from functools import lru_cache

import sys
sys.setrecursionlimit(3000)


def getinputs():
    lines = fileinput.input()
    total_casenum = int(next(lines))
    for casenum in range(1, total_casenum + 1):
        CJ_cost, JC_cost, draft = [s for s in next(lines).strip().split(' ')]
        yield casenum, int(CJ_cost), int(JC_cost), draft


if __name__ == '__main__':
    for casenum, CJ_cost, JC_cost, draft in getinputs():

        @lru_cache(maxsize=None)
        def f(s: str):
            if s in ("J", "C", "JJ", "CC"):
                return 0
            if s == "CJ":
                return CJ_cost
            if s == "JC":
                return JC_cost

            q = s.find("?")
            if q == -1:
                return sum(f(a+b) for a, b in zip(s, s[1:]))

            left, right = s[:q], s[q+1:]

            tryj = f(left + "J") + f("J" + right)
            tryc = f(left + "C") + f("C" + right)
            return min(tryj, tryc)

        print("Case #{}: {}".format(casenum, f(draft)), flush=True)