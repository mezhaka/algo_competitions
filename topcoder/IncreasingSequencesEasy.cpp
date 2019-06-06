// BEGIN CUT HERE
// SRM 728, div 2, 500
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
class IncreasingSequencesEasy {
public:

    int count(vector <int> L, vector <int> R) {
        int const m = 998244353;
        int const maxval = 10000;
        // dp[seqlength][num_of_ending_on_k]
        vector<vector<int>> dp(L.size() + 1, vector<int>(maxval+1, 0));
        fill(begin(dp[1]) + L[0], begin(dp[1]) + R[0] + 1, 1);

        auto acc = [] (int a, int b) { return (a + b) % m; };
        for (int l = 1; l < L.size(); ++l) {
            auto start = begin(dp[l]);
            dp[l+1][L[l]] = accumulate(start, start + L[l], 0, acc);

            for (int k = L[l]+1; k <= R[l]; ++k) {
                dp[l+1][k] = (dp[l+1][k-1] + dp[l][k-1]) % m;
            }
        }

        return accumulate(all(dp[L.size()]), 0, acc);
    }

};
// BEGIN CUT HERE
int main( int argc, char* argv[] ) {
    {
        int LARRAY[] = {1, 3, 1, 4};
        vector <int> L( LARRAY, LARRAY+ARRSIZE(LARRAY) );
        int RARRAY[] = {6, 5, 4, 6};
        vector <int> R( RARRAY, RARRAY+ARRSIZE(RARRAY) );
        IncreasingSequencesEasy theObject;
        eq(0, theObject.count(L, R),4);
    }
    {
        int LARRAY[] = {10, 20};
        vector <int> L( LARRAY, LARRAY+ARRSIZE(LARRAY) );
        int RARRAY[] = {20, 30};
        vector <int> R( RARRAY, RARRAY+ARRSIZE(RARRAY) );
        IncreasingSequencesEasy theObject;
        eq(1, theObject.count(L, R),120);
    }
    {
        int LARRAY[] = {20, 10};
        vector <int> L( LARRAY, LARRAY+ARRSIZE(LARRAY) );
        int RARRAY[] = {30, 20};
        vector <int> R( RARRAY, RARRAY+ARRSIZE(RARRAY) );
        IncreasingSequencesEasy theObject;
        eq(2, theObject.count(L, R),0);
    }
    {
        int LARRAY[] = {4, 46, 46, 35, 20, 77, 20};
        vector <int> L( LARRAY, LARRAY+ARRSIZE(LARRAY) );
        int RARRAY[] = {41, 65, 84, 90, 49, 86, 88};
        vector <int> R( RARRAY, RARRAY+ARRSIZE(RARRAY) );
        IncreasingSequencesEasy theObject;
        eq(3, theObject.count(L, R),2470);
    }
    {
        int LARRAY[] = {1, 1, 1};
        vector <int> L( LARRAY, LARRAY+ARRSIZE(LARRAY) );
        int RARRAY[] = {10000, 10000, 10000};
        vector <int> R( RARRAY, RARRAY+ARRSIZE(RARRAY) );
        IncreasingSequencesEasy theObject;
        eq(4, theObject.count(L, R),908107402);
    }
return 0;
}
// END CUT HERE
