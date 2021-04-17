#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <numeric>
#include <iterator>
#include <stack>

#define fori(i,start,end) for(int(i)=int(start);(i)<int(end);(i)++)
#define all(a) (a).begin(), (a).end()
#define rep(i, end) fori((i), 0, (end))

using namespace std;

class TheBoredomDivTwo {
public:
    int find(int n, int m, int j, int b) {
        int res = n;
        if (j > n) res++;
        if (b > n) res++;
        if (b > n && j > n && j == b) res--;
        return res;
    }

};


// Powered by FileEdit
// Powered by CodeProcessor
