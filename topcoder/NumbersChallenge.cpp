// BEGIN CUT HERE
// SRM 621, div 2, 500

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
int high_bit_position(unsigned int i) {
    int res = 0;
    int c = 0;
    while (i) {
        if (1 == (i & 1)) res = c;
        i >>= 1;
        ++c;
    }
    return res;
}

int remove_highest_bit(unsigned int i) {
    return i & ~(1 << high_bit_position(i)) ;
}

class NumbersChallenge {
public:
    int MinNumberBruteForce(vector <int> S) {
        const int len = (1 << S.size()) + 1;
        vector<int> dp(len, 0);
        fori(i, 1, len) {
            dp[i] = S[high_bit_position(i)] + dp[remove_highest_bit(i)];
        }

        sort(all(dp));
        int end = distance(begin(dp), unique(all(dp)));

        fori(i, 1, end) {
            if (i != dp[i]) return i;
        }
        return end;
    }

// This problem has a very simple solutions, which is not explained in
// editorial:
//class NumbersChallenge:
    //def MinNumber(self, S):
        //S=sorted(S)
        //candidate=1
        //for i in range(len(S)):
          //if S[i]> candidate:
            //return candidate
          //else:
            //candidate=candidate+S[i]

        //return candidate

    int MinNumber(vector <int> S) {
        // This is a dynamic programming solution.  It's a standard solution of
        // a subset sum problem.
        // The key to understanding is to imagine a table -- let's call it dp --
        // with rows corresponding to values of S and columns to the number
        // that we test if it can be constructed, the values of the table are
        // boolean: dp[i][j] is true if it's possible to construct a sum with
        // value j from the elements S[0] up to S[i]. For example, for S = [5,
        // 2, 1] we can construct sums up to 8 and the first column of the
        // table is set to true, because we can construct 0 from any set:
        //      0   1   2   3   4   5   6   7   8
        //  5   1
        //  2   1
        //  1   1
        //  now we iterate over this row by row: we add elements from S
        //  one by one and check if we can construct a value with column index.
        //  If j is equal to the number S[i], then we set to
        //  true; or if the smaller set already can construct this number, i.e.
        //  if dp[i-1][j] is already set; or there is an already considered set
        //  -- one of i-1 that equals to (j - S[i]), i.e., we can add currently
        //  considered set element S[i] to one of the previous sets and get j.
        //
        //  What I found confusing in this algorithm is that I thought that
        //  sets constructed from S[0] up to S[i] should be minimal, but this
        //  is not what this algorithm is claiming.
        int rownum = S.size(), colnum = accumulate(all(S), 0) + 1;
        vector<vector<char>> dp(rownum, vector<char>(colnum));
        rep (i, rownum) dp[i][0] = 1;
        fori (i, 0, rownum) {
            fori(j, 1, colnum) {
                dp[i][j] = (j == S[i])
                           || (i >=1 ? dp[i-1][j] : 0)
                           || (j - S[i] >= 0 && i >=1 ? dp[i-1][j - S[i]] : 0);
            }
        }
        fori (i, 1, colnum) {
            if (!dp[rownum-1][i]) return i;
        }
        return colnum;
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] ) {
    {
        eq(-5, remove_highest_bit(10), 2);
        eq(-4, remove_highest_bit(9), 1);
        eq(-3, 0, remove_highest_bit(8));
        eq(-2, 3, high_bit_position(8));
        eq(-1, 0, high_bit_position(1));
    }
    {
        int SARRAY[] = {5, 1, 2};
        vector <int> S( SARRAY, SARRAY+ARRSIZE(SARRAY) );
        NumbersChallenge theObject;
        eq(0, theObject.MinNumber(S),4);
    }
    {
        int SARRAY[] = {2, 1, 4};
        vector <int> S( SARRAY, SARRAY+ARRSIZE(SARRAY) );
        NumbersChallenge theObject;
        eq(1, theObject.MinNumber(S),8);
    }
    {
        int SARRAY[] = {2, 1, 2, 7};
        vector <int> S( SARRAY, SARRAY+ARRSIZE(SARRAY) );
        NumbersChallenge theObject;
        eq(2, theObject.MinNumber(S),6);
    }
    {
        int SARRAY[] = {94512, 2, 87654, 81316, 6, 5, 6, 37151, 6, 139, 1, 36, 307, 1, 377, 101, 8, 37, 58, 1};
        vector <int> S( SARRAY, SARRAY+ARRSIZE(SARRAY) );
        NumbersChallenge theObject;
        eq(3, theObject.MinNumber(S),1092);
    }
    {
        int SARRAY[] = {883, 66392, 3531, 28257, 1, 14131, 57, 1, 25, 88474, 4, 1, 110, 6, 1769, 220, 442, 7064, 7, 13};
        vector <int> S( SARRAY, SARRAY+ARRSIZE(SARRAY) );
        NumbersChallenge theObject;
        eq(4, theObject.MinNumber(S),56523);
    }
return 0;
}
// END CUT HERE
