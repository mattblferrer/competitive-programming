// Contents
//   profile_dp_simple  copy-and-edit broken-profile DP: domino tilings of the free cells of a grid mod MOD,
//                      O(n m 2^m)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
const ll MOD = 1'000'000'007;

// copy-and-edit broken-profile DP: the number of ways to tile the free cells ('.') of the grid g with dominoes,
// blocked cells being '#', mod MOD (the example problem)
// cells are filled in row-major order, one at a time; before cell (i, j), bit k of the mask says whether the cell
// in column k of the profile is already covered, where the profile is row i + 1 for columns k < j and row i for
// columns k >= j (so bit j is the cell about to be filled, and the broken edge of the profile is at column j)
// at cell (i, j): if it is covered or blocked, nothing is placed and bit j becomes the cell below (uncovered);
// else a vertical domino covers it and the cell below (bit j set), or a horizontal one covers it and (i, j + 1)
// (bit j + 1 set); the answer is the empty mask after the last cell
// to adapt: change the transitions marked below (other tile shapes, colors, counting something other than tilings)
// and what is read from dp at the end; put the shorter side as the columns (transpose g); O(n m 2^m)
ll profile_dp_simple(const vector<string> &g) {
    int n = g.size(), m = n ? g[0].size() : 0;
    vector<ll> dp(1 << m), nd(1 << m);
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fill(nd.begin(), nd.end(), 0);
            for (int mask = 0; mask < 1 << m; mask++) {
                if (!dp[mask]) continue;
                ll ways = dp[mask];
                auto add = [&](int to) { nd[to] = (nd[to] + ways) % MOD; };
                int here = mask >> j & 1, rest = mask & ~(1 << j);
                if (g[i][j] == '#') {  // transition: a blocked cell can't already be covered
                    if (!here) add(rest);
                } else if (here) {  // transition: covered from above, nothing to place
                    add(rest);
                } else {
                    if (i + 1 < n && g[i + 1][j] == '.') add(rest | 1 << j);  // transition: vertical domino
                    if (j + 1 < m && g[i][j + 1] == '.' && !(mask >> (j + 1) & 1))
                        add(rest | 1 << (j + 1));  // transition: horizontal domino
                }
            }
            swap(dp, nd);
        }
    }
    return dp[0];
}
