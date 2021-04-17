// BEGIN CUT HERE
// SRM 325, div 2, 500

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
template<typename T> void print( deque<T> a ) {
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
int cost(vector<vector<int>> & prices, deque<char> & street) {
    //cerr << "street: \n";
    //print(street);
    //cerr << "\n";

    int res = 0;
    fori (i, 0, prices.size()) {
        res += prices[i][street[i]];
    }
    return res;
}

char r = 0, g = 1, b = 2;

class RGBStreet {
public:
    vector<vector<int>> prices;
    size_t N;
    int res;

    void btiterative() { // backtracking
        deque<char> street;

        stack<char> moves;
        moves.push(-1);
        moves.push(0);
        moves.push(-1);
        moves.push(1);
        moves.push(-1);
        moves.push(2);

        while (!moves.empty()) {
            auto next = moves.top();
            moves.pop();
            if (-1 == next) {
                street.pop_back();
                continue;
            }
            street.push_back(next);
            if (street.size() == N) {
                res = min(res, cost(prices, street));
                continue;
            }
            fori(i, 0, 3) {
                if (i != next) {
                    moves.push(-1);
                    moves.push(i);
                }
            }
        }
    }

    void bt(deque<char> & street) {
        if (N == street.size()) {
            res = min(res, cost(prices, street));
            return;
        }
        auto n = street.back();
        if (r == n) {
            street.push_back(b);
            bt(street);
            street.pop_back();

            street.push_back(g);
            bt(street);
            street.pop_back();
        }
        else if (g == n) {
            street.push_back(r);
            bt(street);
            street.pop_back();

            street.push_back(b);
            bt(street);
            street.pop_back();
        }
        else {
            street.push_back(r);
            bt(street);
            street.pop_back();

            street.push_back(g);
            bt(street);
            street.pop_back();
        }
    }

    void parse(vector<string> houses) {
        stringstream ss;
        for (auto pr : houses) {
            ss.clear();
            ss << pr;
            int p1, p2, p3;
            ss >> p1 >> p2 >> p3;
            prices.emplace_back(vector<int>{p1, p2, p3});
        }
    }

    int estimateCostBruteForceRecursive(vector<string> houses) {
        N = houses.size();
        res = 20*1000 + 1;
        parse(houses);

        deque<char> s{0};

        bt(s);

        s.pop_back(); s.push_back(1);
        bt(s);

        s.pop_back(); s.push_back(2);
        bt(s);
        return res;
    }

    int rec(int prev, int sofar) {
        if (sofar == N) { return 0; }
        int res = 20*1000 + 1;
        fori(color, 0, 3) {
            if (prev != color) {
                res = min(res, rec(color, sofar+1) + prices[sofar][color]);
            }
        }
        return res;
    }

    int estimateCost(vector<string> houses) {
        N = houses.size();
        parse(houses);
        return rec(-1, 0);
    }


    int estimateCostBase3(vector<string> houses) {
        // brute force a la base 3 number
        N = houses.size();
        res = 20*1000 + 1;
        parse(houses);
        deque<char> street(houses.size());
        fori(j, 0, pow(3, houses.size())) {
            fori(i, 0, street.size()) {
                if ((street[i] + 1) < 3) {
                    ++street[i];
                    break;
                }
                street[i] = 0;
            }

            bool valid = true;
            fori(i, 1, street.size()) {
                if (street[i] == street[i-1]) {
                    valid = false;
                    break;
                }
            }
            if (valid) { res = min(res, cost(prices, street)); }
        }
        return res;
    }

    int estimateCostBacktrackingIterative(vector<string> houses) {
        N = houses.size();
        res = 20*1000 + 1;
        parse(houses);
        btiterative();
        return res;
    }

    vector<vector<int>> dp;
    int senti = 1000000;

    int estimateCostDynamicProgramming(vector<string> houses) {
        N = houses.size();
        parse(houses);
        dp = vector<vector<int>>(3, vector<int>(houses.size(), senti));
        dp[0][0] = prices[0][0];
        dp[1][0] = prices[0][1];
        dp[2][0] = prices[0][2];
        fori(housenum, 1, houses.size()) {
            fori(color, 0, 3) {
                fori(k, 0, 3) {
                    if (color == k) continue;
                    dp[color][housenum] = min(
                        dp[color][housenum],
                        prices[housenum][color] + dp[k][housenum-1]
                    );
                }
            }
        }
        return min(dp[0][N-1], min(dp[1][N-1], dp[2][N-1]));
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] ) {
    {
        string housesARRAY[] = {"1 100 100", "100 1 100", "100 100 1"};
        vector <string> houses( housesARRAY, housesARRAY+ARRSIZE(housesARRAY) );
        RGBStreet theObject;
        eq(0, theObject.estimateCost(houses),3);
    }
    {
        string housesARRAY[] = {"1 100 100", "100 100 100", "1 100 100"};
        vector <string> houses( housesARRAY, housesARRAY+ARRSIZE(housesARRAY) );
        RGBStreet theObject;
        eq(1, theObject.estimateCost(houses),102);
    }
    {
        string housesARRAY[] = {"26 40 83", "49 60 57", "13 89 99"};
        vector <string> houses( housesARRAY, housesARRAY+ARRSIZE(housesARRAY) );
        RGBStreet theObject;
        eq(2, theObject.estimateCost(houses),96);
    }
    {
        string housesARRAY[] = {"30 19 5", "64 77 64", "15 19 97", "4 71 57", "90 86 84", "93 32 91"};
        vector <string> houses( housesARRAY, housesARRAY+ARRSIZE(housesARRAY) );
        RGBStreet theObject;
        eq(3, theObject.estimateCost(houses),208);
    }
    {
        string housesARRAY[] = {"71 39 44", "32 83 55", "51 37 63", "89 29 100",
            "83 58 11", "65 13 15", "47 25 29", "60 66 19"};
        vector <string> houses( housesARRAY, housesARRAY+ARRSIZE(housesARRAY) );
        RGBStreet theObject;
        eq(4, theObject.estimateCost(houses),253);
    }
return 0;
}
// END CUT HERE
