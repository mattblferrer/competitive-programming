// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 1'000'000'007;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

// Mobius function mu[0..n], O(n log log n)
vector<int> mobius_sieve(int n) {
    vector<int> mu(n + 1, 1);
    vector<char> composite(n + 1, false);
    if (n >= 0) mu[0] = 0;
    for (ll i = 2; i <= n; i++) {
        if (composite[i]) continue;
        for (ll j = i; j <= n; j += i) {
            if (j > i) composite[j] = true;
            mu[j] = -mu[j];
        }
        for (ll j = i * i; j <= n; j += i * i) mu[j] = 0;
    }
    return mu;
}

// number of squarefree integers in [1, n], n up to 1e18, O(n^(2/5)) time and memory; uses mobius_sieve above
// answer = sum of mu(d) floor(n / d^2): d <= D = n^(2/5) directly; for d > D, floor(n / d^2) < n / D^2,
// so that part is sum over i >= 1 of M(sqrt(n / i)) - M(D) while sqrt(n / i) > D, with M the Mertens function
ll count_squarefree(ll n) {
    auto isqrt = [](ll x) {
        ll r = sqrtl((ld)x);
        while (r * r > x) r--;
        while ((r + 1) * (r + 1) <= x) r++;
        return r;
    };
    ll D = min(isqrt(n), max(1LL, (ll)powl((ld)n, 0.4L)));
    vector<int> M = mobius_sieve(D);  // mu, then its prefix sums M[x] for x <= D
    ll ans = 0;
    for (ll d = 1; d <= D; d++) if (M[d]) ans += M[d] * (n / (d * d));
    for (ll d = 1; d <= D; d++) M[d] += M[d - 1];
    auto mertens = [&](ll x) -> ll {  // M(x) = 1 - sum_{k = 2..x} M(x / k); only x / m with x / m > D need recursion
        if (x <= D) return M[x];
        ll K = x / D;
        vector<ll> big(K + 1);  // big[m] = M(x / m)
        for (ll m = K; m >= 1; m--) {
            ll v = x / m, s = 1, k = 2;
            if (v <= D) {
                big[m] = M[v];
                continue;
            }
            for (; v / k > D; k++) s -= big[m * k];
            for (ll hi; k <= v; k = hi + 1) {  // blocks of k with the same v / k
                ll q = v / k;
                hi = v / q;
                s -= (hi - k + 1) * M[q];
            }
            big[m] = s;
        }
        return big[1];
    };
    for (ll i = 1;; i++) {
        ll x = isqrt(n / i);
        if (x <= D) break;
        ans += mertens(x) - M[D];
    }
    return ans;
}

void solve() {
    ll n;
    cin >> n;
    cout << count_squarefree(n) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
