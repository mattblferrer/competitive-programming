#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MODULO = 998244353;
template<int MOD, int RT> struct mint {
    static const int mod = MOD;
    static constexpr mint rt() { return RT; }
    int v; explicit operator int() const { return v; }
    mint():v(0) {}
    mint(long long _v) {
        v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD);
        if (v < 0) v += MOD;
    }
    bool operator==(const mint &o) const { return v == o.v; }
    friend bool operator!=(const mint &a, const mint &b) { return !(a == b); }
    friend bool operator<(const mint &a, const mint &b) { return a.v < b.v; }
    mint &operator+=(const mint &o) { if ((v += o.v) >= MOD) v -= MOD; return *this; }
    mint &operator-=(const mint &o) { if ((v -= o.v) < 0) v += MOD; return *this; }
    mint &operator*=(const mint &o) { v = int((long long)v * o.v % MOD); return *this; }
    mint &operator/=(const mint &o) { return (*this) *= inv(o); }
    friend mint pow(mint a, long long p) { mint ans = 1; assert(p >= 0); for (; p; p /= 2, a *= a) if (p & 1) ans *= a; return ans; }
    friend mint inv(const mint &a) { assert(a.v != 0); return pow(a, MOD - 2); }
    mint operator-() const { return mint(-v); }
    mint &operator++() { return *this += 1; }
    mint &operator--() { return *this -= 1; }
    friend mint operator+(mint a, const mint &b) { return a += b; }
    friend mint operator-(mint a, const mint &b) { return a -= b; }
    friend mint operator*(mint a, const mint &b) { return a *= b; }
    friend mint operator/(mint a, const mint &b) { return a /= b; }
};
using mi = mint<998244353, 5>;

void solve() {
    // your solution here
    int n, k; cin >> n >> k;
    int max_idx = k * k;

    vector<mi> dp(max_idx + 1, 0);
    vector<vector<int>> multiples(k + 1);
    for (int i = 1; i <= k; i++)
    {
        dp[i] = 1;
        int max_sum = i * k;
        for (int j = i; j <= max_sum; j += i)
        {
            multiples[i].push_back(j);
        }
    }

    ll ops = 0;
    for (int i = 1; i < min(n, k); i++)
    {
        int max_sum = i * k;
        for (int j = max_sum; j >= i; j -= i)
        {
            mi upd_val = dp[j];
            dp[j] = 0;
            int lower_idx = lower_bound(multiples[i + 1].begin(), multiples[i + 1].end(), j + 1) - multiples[i + 1].begin();
            int upper_idx = upper_bound(multiples[i + 1].begin(), multiples[i + 1].end(), j + k) - multiples[i + 1].begin();
            for (int k = lower_idx; k < upper_idx; k++)
            {
                ops++;
                dp[multiples[i + 1][k]] += upd_val;
            }
        }
    }

    mi ans = 0;
    ll check = min(n, k);
    for (int i = 1; i <= max_idx; i++)
    {
        if (i % check == 0)
        {
            ans += dp[i];
        }
    }
    cout << ans.v << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}