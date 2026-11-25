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

// number of primes <= n (Lucy_Hedgehog), n up to about 1e11, O(n^(3/4)) time and O(sqrt n) memory
// lo[i] and hi[i] count the numbers in [2, i] and [2, n / i] that survive sieving by the primes so far
ll count_primes(ll n) {
    if (n < 2) return 0;
    ll r = sqrtl(n);
    while (r * r > n) r--;
    while ((r + 1) * (r + 1) <= n) r++;
    vector<ll> lo(r + 1), hi(r + 1);
    for (ll i = 1; i <= r; i++) {
        lo[i] = i - 1;
        hi[i] = n / i - 1;
    }
    for (ll p = 2; p <= r; p++) {
        if (lo[p] == lo[p - 1]) continue;  // p is not prime
        ll before = lo[p - 1], sq = p * p, top = min(r, n / sq);
        for (ll i = 1; i <= top; i++) hi[i] -= (i * p <= r ? hi[i * p] : lo[n / (i * p)]) - before;
        for (ll i = r; i >= sq; i--) lo[i] -= lo[i / p] - before;
    }
    return hi[1];
}

void solve() {
    ll n;
    cin >> n;
    cout << count_primes(n) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
