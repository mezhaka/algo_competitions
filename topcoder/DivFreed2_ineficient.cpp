// BEGIN CUT HERE

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
        int const magic = 1'000'000'007;
        // dp[i][j] is the amount of good arrays of length i that end on j
        vector<vector<int>> dp(n+1, vector<int>(K+1));
        for (int i = 1; i <= K; ++i) {
            dp[1][i] = 1;
        }

        vector<vector<int>> running_sums(n+1, vector<int>(K+1));
        running_sums[1][K] = dp[1][K];
        for (int i = K-1; i > 0; --i) {
            running_sums[1][i] = dp[1][i] + running_sums[1][i+1];
        }

        //print(running_sums);
        //vector<int> tmp1, tmp2;
        //bool allequal = true;

        fori (i, 2, n+1) {
            int sum = 0;
            fori (j, 1, K+1) {
                sum = (sum + dp[i-1][j]) % magic;
            }
            //if (running_sums[i-1][1] != sum) cerr << "yodl" << endl;

            fori (j, 1, K+1) {
                //tmp1.clear(), tmp2.clear();
                //fori (k, 1, j) {
                    //if (j % k) {
                        //dp[i][j] += dp[i-1][k];
                        //dp[i][j] %= magic;
                    //}
                    ////else {
                        ////tmp1.push_back(k);
                    ////}
                //}
                //dp[i][j] += running_sums[i-1][j];

                //for (int k = 2; k <= sqrt(j); ++k) {
                    //auto r = div(j, k);
                    //if (r.rem != 0) continue;
                    //if (r.quot != k) {
                        //tmp2.push_back(k);
                    //}
                    //tmp2.push_back(r.quot);
                //}
                //if (j!=1) tmp2.push_back(1);
                //sort(all(tmp2));
                //bool eq = equal(all(tmp1), all(tmp2));
                //allequal &= eq;
                //if (!eq) {
                    //print(tmp1); cerr << endl;
                    //print(tmp2); cerr << endl;
                //}

                //dp[i][j] = running_sums[i-1][1] - dp[i-1][1];
                dp[i][j] = running_sums[i-1][1];
                for (int k = 1; k <= sqrt(j); ++k) {
                    auto r = div(j, k);
                    //if (r.rem != 0) continue;
                    if (r.rem != 0) continue;
                    if (r.quot != k) {
                        dp[i][j] -= dp[i-1][k];
                    }
                    dp[i][j] -= dp[i-1][r.quot];
                }
                dp[i][j] += dp[i-1][j];

                //fori (k, j, K+1) {
                        //dp[i][j] += dp[i-1][k];
                        //dp[i][j] %= 1'000'000'007;
                //}
            }
            running_sums[i][K] = dp[i][K];
            for (int j = K-1; j > 0; --j) {
                running_sums[i][j] = dp[i][j] + running_sums[i][j+1];
            }
        }

        //cerr << "allequal: " << allequal << endl;
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
