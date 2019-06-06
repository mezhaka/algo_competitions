// BEGIN CUT HERE
// SRM 585, div 2, 500

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
class TrafficCongestionDivTwo {
public:
    long long theMinCars(int treeHeight) {
        if (treeHeight < 2) return 1;
        long long a = 1, b = 1, tmp;
        fori(i, 1, treeHeight) {
            tmp = 2*a + b;
            a = b;
            b = tmp;
        }
        return b;
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] ) {
    {
        TrafficCongestionDivTwo theObject;
        eq(0, theObject.theMinCars(1),1L);
    }
    {
        TrafficCongestionDivTwo theObject;
        eq(1, theObject.theMinCars(2),3L);
    }
    {
        TrafficCongestionDivTwo theObject;
        eq(2, theObject.theMinCars(3),5L);
    }
    {
        TrafficCongestionDivTwo theObject;
        eq(3, theObject.theMinCars(10),683L);
    }
    {
        TrafficCongestionDivTwo theObject;
        eq(4, theObject.theMinCars(60),768614336404564651L);
    }
return 0;
}
// END CUT HERE
