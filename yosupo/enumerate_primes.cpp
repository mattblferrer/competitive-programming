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

// floor(sqrt(n)) for n >= 0, O(1)
ll isqrt(ll n) {
    ll r = sqrtl((ld)n);
    while (r * r > n) r--;
    while ((r + 1) * (r + 1) <= n) r++;
    return r;
}

// calls f(p) for every prime p in [L, R] in increasing order, R up to ~1e12 or more (R - L is what costs);
// sieves blocks of S numbers with the primes up to sqrt(R); collect with [&](ll p) { v.push_back(p); }
// O((R - L) log log R + sqrt(R)) time, O(sqrt(R) + S) memory
template <class F>
void segmented_sieve(ll L, ll R, F f) {
    L = max(L, 2LL);
    if (L > R) return;
    ll r = isqrt(R);
    vector<char> comp(r + 1);
    vector<ll> primes;
    for (ll i = 2; i <= r; i++) {
        if (comp[i]) continue;
        primes.push_back(i);
        for (ll j = i * i; j <= r; j += i) comp[j] = 1;
    }
    const ll S = 1 << 18;
    vector<char> block(S);
    for (ll lo = L; lo <= R; lo += S) {
        ll hi = min(R, lo + S - 1);
        fill(block.begin(), block.begin() + (hi - lo + 1), 1);
        for (ll p : primes) {
            if (p * p > hi) break;
            for (ll j = max(p * p, (lo + p - 1) / p * p); j <= hi; j += p) block[j - lo] = 0;
        }
        for (ll i = lo; i <= hi; i++) if (block[i - lo]) f(i);
    }
}

void solve() {
    ll n, a, b;
    cin >> n >> a >> b;
    ll cnt = 0;
    vector<ll> ans;
    segmented_sieve(0, n, [&](ll p) {
        if (cnt % a == b) ans.push_back(p);
        cnt++;
    });
    cout << cnt << " " << ans.size() << "\n";
    for (ll p : ans) cout << p << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
