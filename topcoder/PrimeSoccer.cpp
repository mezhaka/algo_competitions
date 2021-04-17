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
double fact(int ff) {
    double res = 1.0;
    for (int i = 2; i <= ff; ++i) { res *= i; }
    return res;
}

double binomCoeff(int success_num, int trial_num) {
    return fact(trial_num) / fact(success_num) / fact(trial_num - success_num);
}

double prob(int success_num, int trial_num, double p) {
    return binomCoeff(success_num, trial_num) * pow(p, success_num) * pow(1 - p, trial_num - success_num);
}

class PrimeSoccer {
public:
    double _getProbabilityBinom(int p) {
        vector<int> primes {2, 3, 5, 7, 11, 13, 17};
        vector<double> exact_prob;
        transform(begin(primes), end(primes), back_inserter(exact_prob),
           [p] (int outcome) { return prob(outcome, 18, p / 100.0); });
        return accumulate(begin(exact_prob), end(exact_prob), 0.0);
    }

    // this solution works as well and it's not DP
    double getProbabilityBinom(int skillOfTeamA, int skillOfTeamB) {
        double a = _getProbabilityBinom(skillOfTeamA);
        double b = _getProbabilityBinom(skillOfTeamB);

        return a*(1 - b) + b*(1 - a) + a*b;
    }

    bool isPrime(int i) {
        fori(j, 2, i) {
            if (0 == i % j) {
                return false;
            }
        }
        return true;
    }

    double _getProbability(int pp) {
        double p = pp / 100.0;
        double q = 1.0 - p;

        vector<vector<double>> dp(19, vector<double>(19, 0.));
        dp[0][0] = 1.0;
        fori(game, 1, 19) {
            dp[0][game] = dp[0][game-1] * q;
        }
        // I was not able to come up with this DP -- I've looked it up in the
        // forum and it took me some time to understand how it works.  In plane
        // words: I call each five minute span a game; there are two ways to to
        // get score X in game Y: 1) we have either got score X-1 in game Y-1
        // for which we know the probablity P(X-1, Y-1), so the probability to
        // get score X in the new game is p*P(X-1, Y-1); 2) we already got
        // score X in the previous game Y-1, which means if we want to stay
        // with the same score in the coming game Y, we need not to win in game
        // Y, so the probability is (1-p)*P(X, Y-1).  The bit that I find
        // counterintuitive is that we sum those probabilities, i.e., it means
        // those are mutually exclusive, which is not that easy for me to see.
        fori(score, 1, 19) {
            fori(game, score, 19) {
                dp[score][game] = p*dp[score-1][game-1] + q*dp[score][game-1];
            }
        }

        double ret = 0;
        fori(score, 2, 18) {
            if (isPrime(score)) {
                ret += dp[score][18];
            }
        }

        return ret;
    }

    double getProbability(int skillOfTeamA, int skillOfTeamB) {
        double a = _getProbability(skillOfTeamA);
        double b = _getProbability(skillOfTeamB);

        return a*(1 - b) + b*(1 - a) + a*b;
    }

};


// BEGIN CUT HERE
int main( int argc, char* argv[] ) {
    {
        PrimeSoccer theObject;
        eq(0, theObject.getProbability(50, 50),0.5265618908306351);
    }
    {
        PrimeSoccer theObject;
        eq(1, theObject.getProbability(100, 100),0.0);
    }
    {
        PrimeSoccer theObject;
        eq(2, theObject.getProbability(12, 89),0.6772047168840167);
    }
return 0;
}
// END CUT HERE
