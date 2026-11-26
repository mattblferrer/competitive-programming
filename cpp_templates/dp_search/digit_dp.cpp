// Contents
//   digit_dp_simple  copy-and-edit digit DP: how many x in [0, n] have digit sum divisible by K, O(len * K * 10)
//   digits_of        base-b digits of n >= 0, most significant first (empty for 0), O(log n)
//   digit_dp         sum of acc(state) over every x in [0, n], where state comes from feeding x's digits to step

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// copy-and-edit digit DP: how many x in [0, n] have digit sum divisible by K (the example property)
// go(pos, sum, tight, started) counts the ways to fill digits pos.. of n's length, where tight means the prefix so
// far equals n's (so the next digit is at most s[pos]) and started means a nonzero digit has been placed (leading
// zeros are not digits: unused here, but needed when they would count, e.g. counting zero digits or comparing
// adjacent digits); only !tight && started calls are memoized, the others happen once per position
// to adapt: change the state (sum) and its size K in memo, the base case, and the transition marked below;
// a range [l, r] is digit_dp_simple(r) - digit_dp_simple(l - 1); O(len * K * 10), len = number of digits of n
ll digit_dp_simple(ll n, int K) {
    if (n < 0) return 0;
    string s = to_string(n);
    int len = s.size();
    vector<vector<ll>> memo(len, vector<ll>(K, -1));
    auto go = [&](auto &self, int pos, int sum, bool tight, bool started) -> ll {
        if (pos == len) return sum == 0;  // base case: is the finished number counted?
        bool memoize = !tight && started;
        if (memoize && memo[pos][sum] != -1) return memo[pos][sum];
        ll res = 0;
        int hi = tight ? s[pos] - '0' : 9;
        for (int d = 0; d <= hi; d++) {
            int nsum = (sum + d) % K;  // transition: the state after placing digit d
            res += self(self, pos + 1, nsum, tight && d == hi, started || d > 0);
        }
        if (memoize) memo[pos][sum] = res;
        return res;
    };
    return go(go, 0, 0, true, false);
}

// base-b digits of n >= 0, most significant first, empty for n = 0, O(log n)
vector<int> digits_of(ll n, int base = 10) {
    vector<int> d;
    for (; n > 0; n /= base) d.push_back(n % base);
    return vector<int>(d.rbegin(), d.rend());
}

// digit DP: sum of acc(s) over every x in [0, n], where s is the state after feeding the base-b digits of x to step,
// most significant first, starting from init; leading zeros are not fed (x = 0 feeds nothing, so it gets acc(init))
// n is given by its digits (digits_of above, or parsed from a string when n is huge), so n can have any length
// step(s, d) returns optional<S>: the next state, or nullopt to drop every x with this prefix; acc(s) is the weight of
// x (1 to count, or a value read off s); S must be usable as a map key
// memo[r][s] = the sum over all r-digit suffixes (any digits) from state s, so each (length, state) is solved once;
// a range [l, r] is digit_dp(r) - digit_dp(l - 1)
// O(len * base * (states per length) * log), len = number of digits of n
//   digit_dp<T>(digits, base, init, step, acc)
template <class T, class S, class Step, class Acc>
T digit_dp(const vector<int> &dig, int base, S init, Step step, Acc acc) {
    int len = dig.size();
    vector<map<S, T>> memo(len + 1);
    auto suffixes = [&](auto &self, int r, const S &s) -> T {
        if (r == 0) return acc(s);
        auto it = memo[r].find(s);
        if (it != memo[r].end()) return it->second;
        T res = 0;
        for (int d = 0; d < base; d++) if (auto t = step(s, d)) res += self(self, r - 1, *t);
        return memo[r][s] = res;
    };
    T ans = acc(init);  // x = 0
    for (int l = 1; l < len; l++) {  // fewer digits than n: a nonzero first digit, then anything
        for (int d = 1; d < base; d++) if (auto t = step(init, d)) ans += suffixes(suffixes, l - 1, *t);
    }
    optional<S> cur = init;  // len digits: follow n's prefix, branching below it at every position
    for (int i = 0; i < len && cur; i++) {
        for (int d = i == 0; d < dig[i]; d++) if (auto t = step(*cur, d)) ans += suffixes(suffixes, len - 1 - i, *t);
        cur = step(*cur, dig[i]);
    }
    if (len && cur) ans += acc(*cur);  // x = n
    return ans;
}
