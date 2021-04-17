
#0123 02 03 12 13



#01 02 03

#02

#03

#R
#R
#P

#PP


#======
#1
#R
#RR
#PS

#PR

#2
#R
#RR
#PS

#PRP


#3
#R
#RP
#PS

#PSS


#1) generate
#play with
#test if the current solution does not loose played against all, then add options to it and test it again
#if it


#1 2
#a b c

#1a
#2b
#1c
#2a
#1b
#2c

#1
#a b c
#1a
#1b
#1c

#1 2
#a b c d
#1a
#2b
#1c
#2d



import itertools
import logging
import os
logging.basicConfig(
    level=os.environ.get("LOGLEVEL", "INFO"),
    format=('[%(filename)s:%(lineno)d] %(message)s'),
    datefmt='%Y-%m-%d:%H:%M:%S',
)
logger = logging.getLogger(__name__)
dbg = logger.debug

w = {'R': 'P',
     'P': 'S',
     'S': 'R', }

def play(cand, p):
    candlen, plen = len(cand), len(p)
    i, j = 0, 0
    dbg((cand, p))
    while True:
        if cand[i] == w[p[j]]:
            return 1
        if w[cand[i]] == p[j]:
            return -1
        i = (i+1) % candlen
        j = (j+1) % plen
        if i == 0 and j == 0:
            return 0


def rec(prev, nextmovecand, prs):
    dbg((prev, nextmovecand))
    if not nextmovecand:
        return 'IMPOSSIBLE'

    nmc = nextmovecand.pop()
    cand = prev + nmc
    allgames = [play(cand, r[:len(cand)]) for r in prs] # when we are building we don't need to cycle through, but we should cycle at some point, so passing r[:blah] is not always needed
    #import pdb; pdb.set_trace()
    dbg((cand, allgames))
    if all(1 == a for a in allgames):
        return ''.join(cand)
    if any(-1 == a for a in allgames):
        return rec(prev, nextmovecand, prs)
    if len(cand) < 500:
        return rec(cand, ['R', 'S', 'P'], prs)
    return 'IMPOSSIBLE'


def play2(p, turn_num, cand):
    dbg((p, turn_num, cand))
    advers = p[turn_num % len(p)]
    if cand == w[advers]:
        return 1
    if w[cand] == advers:
        return -1
    return 0


def rec2(prev, allgames, prs):
    cand_for_score = {}
    dbg((prev))
    for nmc in ['R', 'S', 'P']:
        cand = prev + nmc
        candlen = len(prev) + 1
        newallgames = [play2(r[:candlen], candlen, nmc)
                       if res != 1 else res
                       for r, res in zip(prs, allgames)]
        dbg((newallgames))
        if not any(-1 == a for a in newallgames):
            cand_for_score[sum(allgames)] = (cand, newallgames)
    if cand_for_score:
        bestmove = max(cand_for_score.keys())
        if bestmove == len(prs):
            return cand_for_score[bestmove][0]
        return rec2(*cand_for_score[bestmove], prs)
    else:
        return 'IMPOSSIBLE'


# continue building?  how to distinguish when to use full length of the adversary program

# pass best option so far and whether it still makes sense to search

if __name__ == '__main__':
    T = int(input())
    for case in range(T):
        A = int(input())
        prs = []
        for __ in range(A):
            prs.append(input())

        #print('Case #{}: {}'.format(case + 1, rec('', ['R', 'S', 'P'], prs)))
        print('Case #{}: {}'.format(case + 1, rec2('', [0] * len(prs), prs)))

