// SRM 596, div 2, 500
d = {'G': 'R', 'B': 'G', 'R': 'B'}
#dbg = print
dbg = lambda x: None

/home/ant/algo_competitions/topcoder/plugins/CodeProcessor.jar:/home/ant/algo_competitions/topcoder/plugins/FileEdit.jar:/home/ant/algo_competitions/topcoder/plugins/ExampleBuilder.jar

class ColorfulRoadBf:
    def getMin(self, road):

        def bf():
            tovisit = [(0, 0)]
            while tovisit:
                current, costsofar = tovisit.pop()
                tovisit.extend((i, costsofar + (i - current)**2)
                               for i in range(current + 1, len(road))
                               if d[road[i]] == road[current])
                dbg(tovisit)
                if current == len(road) - 1:
                    yield costsofar

        return min(bf(), default=-1)


class ColorfulRoad:
    def getMin(self, road):
        # add a letter to the solution one step at a time; go backwards to check if there's a solution
        cost = [-1] * len(road)
        cost[0] = 0

        for i in range(1, len(cost)):
            expected_color = d[road[i]]
            for j in range(0, i):
                if road[j] == expected_color and cost[j] != -1:
                    movecost = cost[j] + (i - j)**2
                    if cost[i] != -1:
                        cost[i] = min(cost[i], movecost)
                    else:
                        cost[i] = movecost
        return cost[-1]


if __name__ == '__main__':
    #c = ColorfulRoad()
    c = ColorfulRoadBf()

    print(1 == c.getMin("RG"))
    print(8 == c.getMin("RGGGB"))
    print(8 == c.getMin("RGBRGBRGB"))
    print(-1 == c.getMin("RBBGGGRR"))
    print(50 == c.getMin("RBRRBGGGBBBBR"))
    print(52 == c.getMin("RBRGBGBGGBGRGGG"))

