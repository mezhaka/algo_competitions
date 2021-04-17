// BEGIN CUT HERE
// SRM SRM 619, div 2, 500
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
class ChooseTheBestOne {
public:
    int countNumber(int N) {
        vector<int> players(N);
        iota(all(players), 1);

        uint64_t prev = 0;
        for (size_t i = 1; i < N; ++i) {
            prev = (prev + i*i*i - 1) % players.size();
            players.erase(players.begin() + prev);
        }
        return players[0];
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] ) {
    {
        ChooseTheBestOne theObject;
        eq(0, theObject.countNumber(3),2);
    }
    {
        ChooseTheBestOne theObject;
        eq(1, theObject.countNumber(6),6);
    }
    {
        ChooseTheBestOne theObject;
        eq(2, theObject.countNumber(10),8);
    }
    {
        ChooseTheBestOne theObject;
        eq(3, theObject.countNumber(1234),341);
    }
    {
        ChooseTheBestOne theObject;
        eq(3, theObject.countNumber(5000),341);
    }
return 0;
}
// END CUT HERE
