// BEGIN CUT HERE
// SRM 555, div 2, 500

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
#include <bitset>

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
class CuttingBitString {
public:
    vector<uint64_t> pwrs;
    vector<uint64_t> mask;
    vector<char> pwrslen;

    int const impossible = 1000051;

    int f(uint64_t rest) {
        if (!rest) { return 0; }

        int m = impossible;
        for (int i = 0; i < pwrs.size(); ++i) {
            uint64_t cand = mask[i] & rest;
            if (pwrs[i] == cand) {
                uint64_t diff = rest >> pwrslen[i];
                int diffcost = f(diff);
                if (diffcost != impossible) {
                    m = min(m, 1 + diffcost);
                }
            }
        }

        return m;
    }

    int getmin(string S) {
        S = 'G' + S;
        int const N = S.size();

        vector<int> dp(N, -1);
        dp[0] = 0;
        for (int i = 1; i < N; ++i) {
            for (int j = 1; j <= i; ++j) {
                if (dp[j-1] != -1 && p5(j, i, S)) {
                    if (dp[i] == -1) { dp[i] = 1 + dp[j-1]; }
                    else { dp[i] = min(dp[i], 1 + dp[j-1]); }
                }
            }
        }

        return dp[dp.size() - 1];
    }

    bool p5(int b, int e, string const & s) {
        if (s[b] == '0') { return false; }

        uint64_t a = 0;
        for (int i = b; i <= e; ++i) {
            a = a*2 + (s[i] - '0');
        }

        while (0 == a % 5) {
            a /= 5;
        }
        return a == 1;
    }

    int getminBruteForceRecursive(string S) {
        if (S[0] == '0') { return -1; }

        uint64_t s = stoll(S, nullptr, 2);

        for (uint64_t i = 1; i <= s; i *= 5) {
            pwrs.push_back(i);

            uint64_t m = 0;
            char len = 0;
            uint64_t k = i;
            while (k) {
                k >>= 1;
                m = (m << 1) + 1;
                ++len;
            }
            mask.push_back(m);
            pwrslen.push_back(len);
        }

        if (f(s) == impossible) { return -1; }
        else { return f(s); }
    }

};
// BEGIN CUT HERE
int main( int argc, char* argv[] ) {
        //CuttingBitString theObject;
        //cerr << theObject.p5(0, 0, "1");
    //{
        //CuttingBitString theObject;
        //eq(-1, theObject.getmin("101"),1);
    //}
    {
        CuttingBitString theObject;
        eq(3, theObject.getmin("110011011"),3);
    }
    {
        CuttingBitString theObject;
        eq(0, theObject.getmin("101101101"),3);
        //cerr << theObject.p5(1, 4, "310110") << endl;
    }
    {
        CuttingBitString theObject;
        eq(1, theObject.getmin("1111101"),1);
    }
    {
        CuttingBitString theObject;
        eq(2, theObject.getmin("00000"),-1);
    }
    {
        CuttingBitString theObject;
        eq(4, theObject.getmin("1000101011"),-1);
    }
    {
        CuttingBitString theObject;
        eq(5, theObject.getmin("111011100110101100101110111"),5);
    }
    {
        CuttingBitString theObject;
        eq(6, theObject.getmin("1101100011010111001001101011011100010111011110101"),5);
    }
    {
        CuttingBitString theObject;
        eq(7, theObject.getmin("11111011100111001100111000110011100011011001110001"),5);
    }
return 0;
}
// END CUT HERE
