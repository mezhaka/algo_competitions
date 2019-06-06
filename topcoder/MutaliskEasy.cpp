// BEGIN CUT HERE
// SRM 658, div2, 500

// END CUT HERE
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
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

vector<int> add(vector<int> a, vector<int> b) {
    vector<int> r(3);
    for (int i = 0; i < a.size(); ++i) {
        r[i] = a[i] + b[i];
    }
    return r;
}

class MutaliskEasy {
public:
    vector<vector<int>> dmg;
    int dp[61][61][61];
    int const big = 10000000;

    int f(vector<int> hp) {
        int & r = dp[hp[0]][hp[1]][hp[2]];
        if (r != big) return r;
        for (auto d: dmg) {
            auto next = hp;
            transform(all(next),
                      begin(d),
                      begin(next),
                      [](int a, int b) { return max(0, a - b); });
            r = min(r, 1 + f(next));
        }
        return r;
    }

    void init() {
        vector<int> tmp {1, 3, 9};
        dmg.push_back(tmp);
        while (next_permutation(all(tmp))) {
            dmg.push_back(tmp);
        }
        fill(&dp[0][0][0], &dp[0][0][0] + 61*61*61, big);
        dp[0][0][0] = 0;
    }

    int minimalAttacks(vector <int> x) { // memoized approach
        init();
        while (x.size() < 3) {
            x.push_back(0);
        }
        return f(x);
    }

    int minimalAttacksDp(vector <int> x) { // bottom-up DP
        init();
        for (int i = 0; i < 61 ; ++i) {
            for (int j = 0; j < 61; ++j) {
                for (int k = 0; k < 61; ++k) {
                    for (auto const & d : dmg) {
                        int ii = max(0, i - d[0]);
                        int jj = max(0, j - d[1]);
                        int kk = max(0, k - d[2]);
                        dp[i][j][k] = min(dp[i][j][k], 1 + dp[ii][jj][kk]);
                    }
                }
            }
        }

        while (x.size() < 3) {
            x.push_back(0);
        }
        return dp[x[0]][x[1]][x[2]];
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] ) {
    //{
        //map<vector<int>, int> dp;
        //cerr << dp[{0}] << endl;
    //}
    {
        int xARRAY[] = {1, 1, 60};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        MutaliskEasy theObject;
        eq(-1, theObject.minimalAttacks(x),2);
    }
    {
        int xARRAY[] = {12,10,4};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        MutaliskEasy theObject;
        eq(0, theObject.minimalAttacks(x),2);
    }
    {
        int xARRAY[] = {54,18,6};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        MutaliskEasy theObject;
        eq(1, theObject.minimalAttacks(x),6);
    }
    {
        int xARRAY[] = {55,60,53};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        MutaliskEasy theObject;
        eq(2, theObject.minimalAttacks(x),13);
    }
    {
        int xARRAY[] = {1,1,1};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        MutaliskEasy theObject;
        eq(3, theObject.minimalAttacks(x),1);
    }
    {
        int xARRAY[] = {60, 40};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        MutaliskEasy theObject;
        eq(4, theObject.minimalAttacks(x),9);
    }
    {
        int xARRAY[] = {60};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        MutaliskEasy theObject;
        eq(5, theObject.minimalAttacks(x),7);
    }
return 0;
}
// END CUT HERE
