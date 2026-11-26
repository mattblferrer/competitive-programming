// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 998'244'353;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

// a^b mod mod, O(log b)
ll binexp(ll a, ll b, ll mod) {
    ll ans = 1;
    a %= mod;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

// position of (x, y) along a Hilbert curve of order pow; requires x, y < 2^pow, O(pow)
ll hilbert_order(int x, int y, int pow, int rotate = 0) {
    if (pow == 0) return 0;
    int h = 1 << (pow - 1);
    int seg = x < h ? (y < h ? 0 : 3) : (y < h ? 1 : 2);
    seg = (seg + rotate) & 3;
    static const int delta[4] = {3, 0, 0, 1};
    ll sub = 1LL << (2 * pow - 2);
    ll add = hilbert_order(x & (x ^ h), y & (y ^ h), pow - 1, (rotate + delta[seg]) & 3);
    return seg * sub + (seg == 1 || seg == 2 ? add : sub - add - 1);
}

// sum of C(n, i) over 0 <= i <= k for each query {n, k} (n, k >= 0), mod a prime mod > max n; Mo's algorithm over the
// points (n, k) in Hilbert order, using binexp and hilbert_order above: S(n, k) - S(n, k - 1) = C(n, k) and
// S(n + 1, k) = 2 S(n, k) - C(n, k), O(max(n, k) sqrt q) steps
vector<ll> binomial_prefix_sums(const vector<pair<int, int>> &queries, ll mod) {
    int q = queries.size(), N = 1, pow = 0;
    for (auto [n, k] : queries) N = max({N, n + 1, k + 1});
    while ((1 << pow) < N) pow++;
    vector<ll> fac(N + 1, 1), ifac(N + 1, 1), key(q), ans(q);
    for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[N] = binexp(fac[N], mod - 2, mod);
    for (int i = N; i > 0; i--) ifac[i - 1] = ifac[i] * i % mod;
    auto C = [&](int n, int k) { return k > n ? 0 : fac[n] * ifac[k] % mod * ifac[n - k] % mod; };
    vector<int> order(q);
    for (int i = 0; i < q; i++) key[i] = hilbert_order(queries[i].first, queries[i].second, pow), order[i] = i;
    sort(order.begin(), order.end(), [&](int a, int b) { return key[a] < key[b]; });
    ll S = 1, half = (mod + 1) / 2;  // S = S(n, k)
    int n = 0, k = 0;
    for (int i : order) {
        auto [qn, qk] = queries[i];
        while (n < qn) S = (2 * S - C(n, k) + mod) % mod, n++;
        while (k > qk) S = (S - C(n, k) + mod) % mod, k--;
        while (n > qn) n--, S = (S + C(n, k)) * half % mod;
        while (k < qk) k++, S = (S + C(n, k)) % mod;
        ans[i] = S;
    }
    return ans;
}

void solve() {
    ll t;
    cin >> t;
    vector<pair<int, int>> qs(t);
    for (ll i = 0; i < t; i++) cin >> qs[i].first >> qs[i].second;
    vector<ll> ans = binomial_prefix_sums(qs, MOD);
    for (ll i = 0; i < t; i++) cout << ans[i] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
