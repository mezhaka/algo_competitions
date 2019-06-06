def f(people, q):
    horiz = [0] * q
    vert = [0] * q

    for (x, y, d) in people:
        if d == 'S':
            for i in range(0, y):
                vert[i] += 1
        elif d == 'N':
            for i in range(y + 1, q):
                vert[i] += 1
        elif d == 'W':
            for i in range(0, x):
                horiz[i] += 1
        else: #  d == 'E'
            for i in range(x+1, q):
                horiz[i] += 1


    return horiz.index(max(horiz)), vert.index(max(vert))

if __name__ == '__main__':
    T = int(input())
    for case in range(T):
        pnum, q = [int(i) for i in input().split(' ')]
        people = []
        for __ in range(pnum):
            temp = input().split(' ')
            people.append(
                (int(temp[0]), int(temp[1]), temp[2],)
            )
        print('Case #{}: {} {}'.format(case + 1, *f(people, q)))

