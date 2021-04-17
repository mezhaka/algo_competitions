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
// from the editorial:
//The constraints are small enough that we can just implement the recurrence in this raw state, without memoization or dynamic programming. Like the following c++ and python solutions:

//?
//int printSmiles(int s)
//{
    //int res = s; //if x = 1, then f(1) + s/1, f(1) = 0
    //for (int x = 1; x < s; x++) {
        //if (s % x == 0) { // x is a divisor of s
            //res = std::min(res, printSmiles(x) + s / x);
        //}
    //}
    //return res;
//}
//?
//# the recurrence, if s==1, return 0 else the minimum f(x) + s/x where x
//# is a proper divisor of s
//def f(s):
    //return 0 if s == 1 else min( f(x) + s / x for x in divisors(s) )

//def divisors(s):
    //return (x for x in xrange(1,s) if s % x == 0) #proper divisors of s

//class EmoticonsDiv2:
    //printSmiles = staticmethod(f)
//We need an analysis for why doesn't this time out. The number of divisors of the numbers from 1 to 1000 ought to be rather small. The valid number with the most divisors is 840 (It tends to be useful to keep the list of highly composite numbers in hand). Even for 840, the function will be called 2684 times (can just test it). Of course, we can use memoization or dynamic programming so each of the (up to 1000) values of `s` is evaluated at most once and ensure an `O("smiles"^2)` complexity.

//Greedy
//Or we can just prove that the best value for `x` is always the largest one. So we first find the maximum divisor `x` of `s` and return `f(x) + s/x`.

//Math
//If we assume that the best `x` is the maximum divisor of `s`, we can find a very interesting property. If `x` is the maximum proper divisor of `s`, what does it make of `s/x` ? Unless `s` has no proper divisors other than 1, then `s/x` is the smallest prime factor of `s`. We add the smallest prime factor to the result, and modify `s = x` , which is the same as `s = s/(s/x)`. From this we can conclude that the result is equal to the sum of all prime factors of `s`. We can find all prime factors of `s` in `O(sqrt(s))` time:

//?
//int printSmiles(int s)
//{
    //// add all prime factors of s:
    //int res = 0;
    //for (int x = 2; x*x <= s; x++) {
        //while (s % x == 0) {
            //s /= x;
            //res += x;
        //}
    //}
    //if (s != 1) {
        //res += s;
    //}
    //return res;
//}

// END CUT HERE
class EmoticonsDiv2 {
public:
    int printSmiles(int smiles) {
        int len = smiles + 1;
        vector<int> dp(len);
        for (int i = 1; i < dp.size(); ++i)
        {
            dp[i] = i;
        }
        for (int i = 1; i < dp.size(); ++i)
        {
            for (int j = i; j < dp.size(); ++j)
            {
                if (j % i) continue;
                dp[j] = min(dp[j], j/i + dp[i]);
            }
        }

        return dp[smiles];
    }

};
// BEGIN CUT HERE
int main( int argc, char* argv[] ) {
    {
        EmoticonsDiv2 theObject;
        eq(0, theObject.printSmiles(2),2);
    }
    {
        EmoticonsDiv2 theObject;
        eq(1, theObject.printSmiles(6),5);
    }
    {
        EmoticonsDiv2 theObject;
        eq(2, theObject.printSmiles(11),11);
    }
    {
        EmoticonsDiv2 theObject;
        eq(3, theObject.printSmiles(16),8);
    }
    {
        EmoticonsDiv2 theObject;
        eq(4, theObject.printSmiles(1000),21);
    }
return 0;
}
// END CUT HERE
