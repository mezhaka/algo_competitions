// BEGIN CUT HERE
// SRM 685, div 2, 500

// END CUT HERE
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

// BEGIN CUT HERE
#define ARRSIZE(x) (sizeof(x)/sizeof(x[0]))

template<typename T> void print( T a ) {
    cerr << a;
}
static void print( long long a ) {
    cerr << a << "L";
}
static void print( string a ) {
    cerr << '"' << a << '"';
}
template<typename T> void print( vector<T> a ) {
    cerr << "{";
    for ( typename vector<T>::size_type i = 0 ; i != a.size() ; i++ ) {
        if ( i != 0 ) cerr << ", ";
        print( a[i] );
    }
    cerr << "}" << endl;
}
template<typename T, typename U> void eq( int n, T have, U need ) {
    if ( have == need ) {
        cerr << "Case " << n << " passed." << endl;
    } else {
        cerr << "Case " << n << " failed: expected ";
        print( need );
        cerr << " received ";
        print( have );
        cerr << "." << endl;
    }
}
template<typename T, typename U> void eq( int n, vector<T> have, vector<U> need ) {
    if( have.size() != need.size() ) {
        cerr << "Case " << n << " failed: returned " << have.size() << " elements; expected " << need.size() << " elements.";
        print( have );
        print( need );
        return;
    }
    for( int i= 0; i < have.size(); i++ ) {
        if( have[i] != need[i] ) {
            cerr << "Case " << n << " failed. Expected and returned array differ in position " << i << ".";
            print( have );
            print( need );
            return;
        }
    }
    cerr << "Case " << n << " passed." << endl;
}
static void eq( int n, string have, string need ) {
    if ( have == need ) {
        cerr << "Case " << n << " passed." << endl;
    } else {
        cerr << "Case " << n << " failed: expected ";
        print( need );
        cerr << " received ";
        print( have );
        cerr << "." << endl;
    }
}
// END CUT HERE
struct s {
    int id, w1sum, w2sum;
    s(int id_, int w1sum_, int w2sum_) {
        id = id_;
        w1sum = w1sum_;
        w2sum = w2sum_;
    }

    s(s const & other, int id_, char w1, char w2) {
        id = id_;
        w1sum = other.w1sum + (w1 - '0');
        w2sum = other.w2sum + (w2 - '0');
    }

    int dist() const {
        return w1sum*w2sum;
    }
};

class DoubleWeights {
public:
    int N;

    int getw(vector<string> w, int i, int j) {
        return w[i][j] - '0';
    }

    void backtrack_iterative(vector<string> weight1, vector<string> weight2) {
        int N = weight1.size();
        vector<bool> visited(N, false);
        stack<tuple<int, int, int>> q;
        q.push({0, -1, -1});
        q.push({0, 0, 0});
        while (!q.empty()) {
            int id,  w1, w2;
            tie(id, w1, w2) = q.top();
            q.pop();

            if (w1 == -1 && w2 == -1) {
                visited[id] = false;
                continue;
            }

            if (visited[id]) { continue; }
            visited[id] = true;
            q.push({id, -1, -1});

            if (id == 1) {
                cost = min(cost, w1*w2);
            }

            for (int i = 0; i < N; ++i) {
                if (weight1[id][i] == '.' || visited[i]) { continue; }
                q.push({i, w1 + getw(weight1, id, i), w2 + getw(weight2, id, i)});
            }
        }
    }

    int minimalCost_backtrack_iterative(vector <string> weight1, vector <string> weight2) { // DFS
        backtrack_iterative(weight1, weight2);
        return numeric_limits<int>::max() != cost ? cost : -1;
    }

    int minimalCost(vector<string> weight1, vector<string> weight2) // editorial solution
    {
        const int MAX_WEIGHT = 180;
        int n = weight1.size();
        // [20*9][20]
        const int INF = 1000000000;

        // In c++ 's case, we can use a set of tuples for the Dijkstra "priority queue".
        // std::set orders its elements and tuples means that the first value of
        // the tuple is given priority when ordering. So to add (x, w2) to the
        // queue with a distance d we add (d, x,w2) to the std::set.
        //
        // The good thing about std::set is that it allows us to remove elements
        // unlike std::priority_queue.
        //
        set< tuple<int,int,int> > Q;
        // dist[x][w2] : The known smallest distance between (0,0) and (x,w2)
        vector<vector<int>> dist(MAX_WEIGHT + 1, vector<int>(n, INF) );
        // The distance between (0,0) and (0,0) is 0 (it is the starting point)
        Q.insert( make_tuple(0, 0,0) );
        dist[0][0] = 0;

        while (! Q.empty() ) {
            auto it = Q.begin(); // get the first element of the set, the first one in the order
                                 // the one with smallest d:
            int d, w2, x;
            tie(d, w2, x) = *it; //un pack the values
            Q.erase(it);

            // try an edge with x as starting point:
            for (int y = 0; y < n; y++) {
                if (weight1[x][y] != '.') {
                    int nd =  d + (weight1[x][y] - '0');  // new distance
                    int nw2 = w2 + (weight2[x][y] - '0');  // new d2

                    if ( (nw2 <= MAX_WEIGHT) && (nd < dist[nw2][y]) )  {
                        // don't add elements with too large a w2

                        // remove the old element from the set:
                        //auto q = Q.find( make_tuple( dist[nw2][y], nw2,y) );
                        //if (q != Q.end()) {
                            //Q.erase(q);
                        //}
                        // update the distance, add to set
                        dist[nw2][y] = nd;
                        Q.insert( make_tuple( dist[nw2][y], nw2,y) );
                    }
                }
            }
        }
        // try all (1, w2), the result is distance * w2:
        int res = INF;
        for (int W2 = 0; W2 <= MAX_WEIGHT; W2++) {
            if (dist[W2][1] < INF) {
                res = std::min(res, dist[W2][1] * W2);
            }
        }

        return (res >= INF) ? -1: res;
    }

    vector<bool> visited;
    int cost = numeric_limits<int>::max();
    vector<string> weight1, weight2;

    void backtrack(int id, int w1sofar, int w2sofar) {
        if (id == 1) {
            cost = min(cost, w1sofar*w2sofar);
        }

        for (int i = 0; i < visited.size(); ++i) {
            if (weight2[id][i] == '.' || visited[i]) { continue; }
            visited[i] = true;
            backtrack(i, w1sofar + (weight1[id][i] - '0'), w2sofar + (weight2[id][i] - '0'));
            visited[i] = false;
        }
    }

    int minimalCostRecursive(vector <string> weight1, vector <string> weight2) { // backtrack
        visited = vector<bool>(weight2.size(), false);
        this->weight1 = weight1;
        this->weight2 = weight2;
        backtrack(0, 0, 0);
        return numeric_limits<int>::max() != cost ? cost : -1;
    }

    int minimalCostDijkstra(vector <string> weight1, vector <string> weight2) { // Dijkstra
        int const N = weight2.size();
        vector<char> visited(N, 0);
        vector<int> dist(N, numeric_limits<int>::max());
        dist[0] = 0;
        auto cmp = [] (s const & l, s const & r) { return l.dist() > r.dist(); };
        priority_queue<s, vector<s>, decltype(cmp)> q(cmp);
        q.push({0, 0, 0});
        while (!q.empty()) {
            auto curr = q.top();
            q.pop();
            if (visited[curr.id]) { continue; }
            visited[curr.id] = 1;

            for (int id = 0; id < N; ++id) {
                if (visited[id] || weight2[curr.id][id] == '.') { continue; }

                auto cand = s(curr, id, weight1[curr.id][id], weight2[curr.id][id]);
                if (cand.dist() < dist[id]) {
                    dist[id] = cand.dist();
                    q.push(cand);
                }
            }
        }
        return numeric_limits<int>::max() != dist[1] ? dist[1] : -1;
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] ) {
    {
        string weight1ARRAY[] = {"..14",
            "..94",
            "19..",
            "44.."};
        vector <string> weight1( weight1ARRAY, weight1ARRAY+ARRSIZE(weight1ARRAY) );
        string weight2ARRAY[] = {"..94",
            "..14",
            "91..",
            "44.."};
        vector <string> weight2( weight2ARRAY, weight2ARRAY+ARRSIZE(weight2ARRAY) );
        DoubleWeights theObject;
        eq(0, theObject.minimalCost(weight1, weight2),64);
    }
    {
        string weight1ARRAY[] = {"..14",
            "..14",
            "11..",
            "44.."};
        vector <string> weight1( weight1ARRAY, weight1ARRAY+ARRSIZE(weight1ARRAY) );
        string weight2ARRAY[] = {"..94",
            "..94",
            "99..",
            "44.."};
        vector <string> weight2( weight2ARRAY, weight2ARRAY+ARRSIZE(weight2ARRAY) );
        DoubleWeights theObject;
        eq(1, theObject.minimalCost(weight1, weight2),36);
    }
    {
        string weight1ARRAY[] = {"..",
            ".."};
        vector <string> weight1( weight1ARRAY, weight1ARRAY+ARRSIZE(weight1ARRAY) );
        string weight2ARRAY[] = {"..",
            ".."};
        vector <string> weight2( weight2ARRAY, weight2ARRAY+ARRSIZE(weight2ARRAY) );
        DoubleWeights theObject;
        eq(2, theObject.minimalCost(weight1, weight2),-1);
    }
    {
        string weight1ARRAY[] = {".....9",
            "..9...",
            ".9.9..",
            "..9.9.",
            "...9.9",
            "9...9."};
        vector <string> weight1( weight1ARRAY, weight1ARRAY+ARRSIZE(weight1ARRAY) );
        string weight2ARRAY[] = {".....9",
            "..9...",
            ".9.9..",
            "..9.9.",
            "...9.9",
            "9...9."};
        vector <string> weight2( weight2ARRAY, weight2ARRAY+ARRSIZE(weight2ARRAY) );
        DoubleWeights theObject;
        eq(3, theObject.minimalCost(weight1, weight2),2025);
    }
    {
        string weight1ARRAY[] = {".4...1",
            "4.1...",
            ".1.1..",
            "..1.1.",
            "...1.1",
            "1...1."};
        vector <string> weight1( weight1ARRAY, weight1ARRAY+ARRSIZE(weight1ARRAY) );
        string weight2ARRAY[] = {".4...1",
            "4.1...",
            ".1.1..",
            "..1.1.",
            "...1.1",
            "1...1."};
        vector <string> weight2( weight2ARRAY, weight2ARRAY+ARRSIZE(weight2ARRAY) );
        DoubleWeights theObject;
        eq(4, theObject.minimalCost(weight1, weight2),16);
    }
return 0;
}
// END CUT HERE
