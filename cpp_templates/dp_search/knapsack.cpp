// Contents
//   subset_sums        bitset of the sums [0, N) reachable by subsets of w (bitset knapsack), O(N sqrt(N) / 64)
//   bounded_knapsack   best value with weight at most j for every j <= W, item i used up to c[i] times, O(n W)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// bitset of the sums in [0, N) reachable by subsets of the weights w (each used at most once); weights >= N are
// dropped, since no sum below N uses them; three or more copies of a weight x become one or two copies of x and
// pairs moved to 2x (the reachable sums don't change), which leaves O(sqrt(N)) shifts when sum(w) <= N, otherwise
// O(n) shifts; O(min(n, sqrt(sum w)) * N / 64) after O(n + N)
//   subset_sums<N>(w)    N is a compile-time constant, above the largest sum needed
template <int N>
bitset<N> subset_sums(const vector<int> &w) {
    vector<int> cnt(N);
    for (int x : w) if (x < N) cnt[x]++;
    bitset<N> b;
    b[0] = 1;
    for (int x = 1; x < N; x++) {
        if (cnt[x] > 2) {
            int pairs = (cnt[x] - 1) / 2;
            cnt[x] -= 2 * pairs;
            if (2 * x < N) cnt[2 * x] += pairs;
        }
        for (int k = 0; k < cnt[x]; k++) b |= b << x;
    }
    return b;
}

// bounded knapsack: dp[j] = the best value of items with total weight at most j, for every j in [0, W], where item i
// has weight w[i] >= 1, value v[i], and can be used up to c[i] times (c[i] up to W / w[i] for unbounded)
// for each item, the weights j = r, r + w, r + 2w, ... with the same remainder r form a line; writing j = r + k w,
// new[j] = max over k - c <= k' <= k of old[r + k' w] - k' v, plus k v: a sliding window max (monotone deque)
// for weight exactly j, start dp at -INF except dp[0] = 0 and skip -INF entries; O(n W)
vector<ll> bounded_knapsack(const vector<int> &w, const vector<ll> &v, const vector<ll> &c, int W) {
    vector<ll> dp(W + 1, 0), nd(W + 1);
    vector<pair<ll, ll>> dq(W + 1);  // {k', old[r + k' w] - k' v}, decreasing in value
    for (size_t i = 0; i < w.size(); i++) {
        for (int r = 0; r < w[i] && r <= W; r++) {
            int head = 0, tail = 0;
            for (ll k = 0, j = r; j <= W; k++, j += w[i]) {
                ll val = dp[j] - k * v[i];
                while (tail > head && dq[tail - 1].second <= val) tail--;
                dq[tail++] = {k, val};
                while (dq[head].first < k - c[i]) head++;
                nd[j] = dq[head].second + k * v[i];
            }
        }
        swap(dp, nd);
    }
    return dp;
}
