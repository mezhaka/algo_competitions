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
class RouteIntersection {
public:
    string isValid(int N, vector <int> coords, string moves) {
        vector<map<int, char>> all;
        map<int, char> curr;
        all.push_back(curr);
        for (int i = 0; i < coords.size(); ++i) {
            auto dim = curr.find(coords[i]);
            char m = moves[i] == '+' ? 1 : -1;
            if (curr.end() != dim) {
                dim->second += m;
                if (dim->second == 0) {
                    curr.erase(dim);
                }
            }
            else {
                curr[coords[i]] = m;
            }
            all.push_back(curr);
        }
        for (int i = 0; i < all.size(); ++i) {
            for (int j = i + 1; j < all.size(); ++j) {
                if (all[i] == all[j]) { return "NOT VALID"; }
            }
        }
        return "VALID";
    }

};
// BEGIN CUT HERE
int main( int argc, char* argv[] ) {
    {
        int coordsARRAY[] = {1};
        vector <int> coords( coordsARRAY, coordsARRAY+ARRSIZE(coordsARRAY) );
        RouteIntersection theObject;
        eq(0, theObject.isValid(1, coords, "+"),"VALID");
    }
    {
        int coordsARRAY[] = {1,2,1,2};
        vector <int> coords( coordsARRAY, coordsARRAY+ARRSIZE(coordsARRAY) );
        RouteIntersection theObject;
        eq(1, theObject.isValid(2, coords, "++--"),"NOT VALID");
    }
    {
        int coordsARRAY[] = {1,2,3,1,2};
        vector <int> coords( coordsARRAY, coordsARRAY+ARRSIZE(coordsARRAY) );
        RouteIntersection theObject;
        eq(2, theObject.isValid(3, coords, "+++--"),"VALID");
    }
    {
        int coordsARRAY[] = {132,51717,628,344447,628,51717,344447,2};
        vector <int> coords( coordsARRAY, coordsARRAY+ARRSIZE(coordsARRAY) );
        RouteIntersection theObject;
        eq(3, theObject.isValid(344447, coords, "+-++-+--"),"NOT VALID");
    }
    {
        int coordsARRAY[] = {1,1};
        vector <int> coords( coordsARRAY, coordsARRAY+ARRSIZE(coordsARRAY) );
        RouteIntersection theObject;
        eq(4, theObject.isValid(1, coords, "+-"),"NOT VALID");
    }
    {
        int coordsARRAY[] = {833196,524568,361663,108056,28026,824639,269315,440977,440977,765458,
           988451,242440,948414,130873,773990,765458,130873,28026,853121,553636,
           581069,82254,735536,833196,898562,898562,940783,988451,540613,317306,
           623194,940783,571384,988451,108056,514374,97664};
        vector <int> coords( coordsARRAY, coordsARRAY+ARRSIZE(coordsARRAY) );
        RouteIntersection theObject;
        eq(5, theObject.isValid(990630, coords, "--+---+-+++-+-+---++-++-+---+-+--+-++"),"NOT VALID");
    }
return 0;
}
// END CUT HERE
