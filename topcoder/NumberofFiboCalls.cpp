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
class NumberofFiboCalls {
public:
    vector <int> fiboCallsMade(int n) {
        vector <int> res {0, 0};
        vector<int> a{1, 0}, b{0, 1};
        if (0 == n) {
            return a;
        }
        if (1 == n) {
            return b;
        }
        for (int i = 1; i < n; ++i) {
            res[0] = a[0] + b[0];
            res[1] = a[1] + b[1];
            a = b;
            b = res;
        }

        return res;
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] ) {
    {
        int retrunValueARRAY[] = {1, 0 };
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        NumberofFiboCalls theObject;
        eq(0, theObject.fiboCallsMade(0),retrunValue);
    }
    {
        int retrunValueARRAY[] = {1, 2 };
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        NumberofFiboCalls theObject;
        eq(1, theObject.fiboCallsMade(3),retrunValue);
    }
    {
        int retrunValueARRAY[] = {5, 8 };
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        NumberofFiboCalls theObject;
        eq(2, theObject.fiboCallsMade(6),retrunValue);
    }
    {
        int retrunValueARRAY[] = {10946, 17711 };
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        NumberofFiboCalls theObject;
        eq(3, theObject.fiboCallsMade(22),retrunValue);
    }
    {
        int retrunValueARRAY[] = {10946, 17711 };
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        NumberofFiboCalls theObject;
        eq(3, theObject.fiboCallsMade(40),retrunValue);
    }
return 0;
}
// END CUT HERE
