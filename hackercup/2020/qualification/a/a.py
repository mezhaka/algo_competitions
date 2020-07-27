import fileinput
import functools
import math


def solve(in_allowed, out_allowed):
    N = len(in_allowed)

    @functools.lru_cache(maxsize=None)
    def f(out, in_):
        if out == in_:
            return True
        direction = 1 if out < in_ else -1
        intermediate = out + direction
        canfly = (
                out_allowed[out] == 'Y'
            and in_allowed[in_] == 'Y'
            and (   intermediate == in_
                 or (f(out, intermediate) and f(intermediate, in_))
            )
        )
        return canfly

    t = lambda x: 'Y' if x else 'N'
    return '\n'.join(
                ''.join(t(f(in_, out)) for out in range(N))
                for in_ in range(N))


def getinputs():
    lines = fileinput.input()
    total_casenum = int(next(lines))
    for casenum in range(1, total_casenum + 1):
        _, in_, out = next(lines), next(lines).strip(), next(lines).strip()
        yield casenum, in_, out


if __name__ == '__main__':
    for casenum, in_, out in getinputs():
        print('Case #{}:\n{}'.format(casenum, solve(in_, out)))

