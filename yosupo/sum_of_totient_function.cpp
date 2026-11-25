// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 998244353;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

// sum of phi(i) for i in [1, n] mod mod, n up to about 1e11, O(n^(2/3)) time and memory
// S(x) = x(x + 1) / 2 - sum over d in [2, x] of S(x / d), since every pair i <= j <= x has gcd(i, j) = j / d for some d;
// S is sieved up to n^(2/3), and big[i] = S(n / i) above that is filled for decreasing i (n / (i d) = (n / i) / d)
ll totient_sum(ll n, ll mod) {
    if (n < 1) return 0;
    ll lim = max(1LL, (ll)powl(n, 2.0L / 3));
    vector<ll> small(lim + 1), big(n / lim + 1);
    iota(small.begin(), small.end(), 0);
    for (ll p = 2; p <= lim; p++) {
        if (small[p] == p) for (ll j = p; j <= lim; j += p) small[j] -= small[j] / p;  // p is prime
    }
    for (ll i = 1; i <= lim; i++) small[i] = (small[i - 1] + small[i]) % mod;
    for (ll i = n / lim; i >= 1; i--) {
        ll x = n / i;
        if (x <= lim) continue;
        ll res = (x % 2 ? x % mod * ((x + 1) / 2 % mod) : x / 2 % mod * ((x + 1) % mod)) % mod;
        for (ll d = 2, e; d <= x; d = e + 1) {  // x / d is the same for all d' in [d, e]
            ll q = x / d;
            e = x / q;
            res = (res - (e - d + 1) % mod * (q <= lim ? small[q] : big[i * d])) % mod;
        }
        big[i] = (res + mod) % mod;
    }
    return n <= lim ? small[n] : big[1];
}

void solve() {
    ll n;
    cin >> n;
    cout << totient_sum(n, MOD) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
