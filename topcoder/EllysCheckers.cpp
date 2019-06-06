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

#define TRACE(x) cout << #x << " = " << x << endl

// END CUT HERE
bool is_set(int n, int i) { return (n >> i) & 1; }
int unset(int n, int i) { return n & ~(1 << i); }
void fill_possible_moves(vector<int> & next, int current) {
    for (int i = 1; i <= 21; ++i) { // start with i, cause 0th bit is never set
        if (is_set(current, i)) {
            if (!is_set(current, (i-1))) {
                next.push_back(unset(current, i) | 1 << (i-1));
            }
            if (i >= 3 && is_set(current, i-1) && is_set(current, i-2)
                && !is_set(current, i-3)) {
                next.push_back(unset(current, i) | 1 << (i-3));
            }
        }
    }
}


class EllysCheckers {
public:
    string getWinner(string board) {
        int b = 0;
        for (int i = 0; i < board.size(); ++i) {
            b = (b << 1) | (board[i] == 'o' ? 1 : 0);
        }

        // store optimal number of moves in the game for player given current
        // board in dp[player][board]
        vector<vector<int>> dp(2, vector<int>(pow(2, board.size())));
        vector<int> possible_moves;

        for (int i = 2; i <= b; ++i) { // i is a board
            if (i && 1) {
                for (int player = 0; player < 2; ++player) {
                    dp[player][i] = dp[player][i && ~unsigned(1)];
                    continue;
                }
            }

            // generate all possible moves
            possible_moves.clear();
            fill_possible_moves(possible_moves, i);
    //pick the one which is either odd or even depending on whose move it is

            for (int player = 0; player < 2; ++player) {
                int other = player == 0 ? 1 : 0;
                int optimal_num = 1 + dp[other][possible_moves[0]];
                for (int k = 1; k < possible_moves.size(); ++k) {
                    auto next = 1 + dp[other][possible_moves[k]];
                    if (next % 2) {
                        optimal_num = next;
                    }
                }
                dp[player][i] = optimal_num;
            }
        }

        return (dp[0][b] % 2) ? "YES" : "NO";
    }

};
// BEGIN CUT HERE
int main( int argc, char* argv[] ) {
    {
        int m = 22;
        vector<int> moves;
        fill_possible_moves(moves, m);
        print(moves);
    }
    {
        int m = (1 << 1 | 1 << 2 | 1 << 3);
        vector<int> moves;
        fill_possible_moves(moves, m);
        print(moves);
    }
    {
        EllysCheckers theObject;
        eq(-1, theObject.getWinner("o."),"YES");
    }
    {
        EllysCheckers theObject;
        eq(0, theObject.getWinner(".o..."),"YES");
    }
    //exit(1);
    {
        EllysCheckers theObject;
        eq(1, theObject.getWinner("..o..o"),"YES");
    }
    {
        EllysCheckers theObject;
        eq(2, theObject.getWinner(".o...ooo..oo.."),"NO");
    }
    {
        EllysCheckers theObject;
        eq(3, theObject.getWinner("......o.ooo.o......"),"YES");
    }
    {
        EllysCheckers theObject;
        eq(4, theObject.getWinner(".o..o...o....o.....o"),"NO");
    }
return 0;
}
// END CUT HERE
