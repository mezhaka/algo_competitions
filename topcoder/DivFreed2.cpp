// BEGIN CUT HERE
// SRM 684, div2, 600

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

//f(int prev_digit, int numsofar, int togo, int k) {
    //int curr = prev + 1;
    //prev_num
    //// what happens if we add a new digit to some that ends on prev
    //fori (i, prev_digit, k) {
        //total += prev_num * (k - prev_digit); // A <= B
        //total += prev_num *

    //}
    //return f(curr, togo - 1, k);
//}

class DivFreed2 {
public:
    int count(int n, int K) {
        int const magic = 1000000007;
        // dp[i][j] is the amount of good arrays of length i that end on j
        vector<vector<int>> divisors(K+1);
        for (int i = 1; i <= K; ++i) {
            for (int j = 2*i; j <= K; j += i) {
                divisors[j].push_back(i);
            }
        }
        cerr << endl;
        if (divisors.size() > 2) print(divisors[10]);

        vector<vector<int>> dp(n+1, vector<int>(K+1));
        for (int i = 1; i <= K; ++i) {
            dp[1][i] = 1;
        }

        fori (i, 2, n+1) {
            int sum = 0;
            fori (j, 1, K+1) {
                sum = (sum + dp[i-1][j]) % magic;
            }

            fori (j, 1, K+1) {
                dp[i][j] = sum;
                for (int d : divisors[j]) {
                    dp[i][j] = (magic + dp[i][j] - dp[i-1][d]) % magic;
                }
                //for (int k = 1; k <= sqrt(j); ++k) {
                    //auto r = div(j, k);
                    //if (r.rem != 0) continue;
                    //if (r.quot != k) {
                        //dp[i][j] = (magic + dp[i][j] - dp[i-1][k]) % magic;
                    //}
                    //dp[i][j] = (magic + dp[i][j] - dp[i-1][r.quot]) % magic;
                //}
                //dp[i][j] = (dp[i][j] + dp[i-1][j]) % magic;
            }
        }

        int res = 0;
        fori(i, 0, dp[n].size()) {
            res = (res + dp[n][i]) % magic;
        }
        return res;
    }

};
// BEGIN CUT HERE
int main( int argc, char* argv[] ) {
    {
        DivFreed2 theObject;
        eq(0, theObject.count(2, 2),3);
    }
    {
        DivFreed2 theObject;
        eq(1, theObject.count(9, 1),1);
    }
    {
        DivFreed2 theObject;
        eq(2, theObject.count(3, 3),15);
    }
    //exit(1);
    {
        DivFreed2 theObject;
        eq(3, theObject.count(1, 107),107);
    }
    {
        DivFreed2 theObject;
        eq(4, theObject.count(2, 10),83);
    }
    {
        DivFreed2 theObject;
        eq(5, theObject.count(2, 1234),1515011);
    }
    {
        DivFreed2 theObject;
        eq(6, theObject.count(3, 8),326);
    }
    {
        DivFreed2 theObject;
        eq(7, theObject.count(10, 100000),526882214);
    }
return 0;
}
// END CUT HERE
