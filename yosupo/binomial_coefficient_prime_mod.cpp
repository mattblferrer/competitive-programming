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

vector<ll> fac, inv_fac;

// a^b mod mod, O(log b)
ll binexp(ll a, ll b, ll mod) {
    ll ans = 1;
    a %= mod;
    while (b) {
        if (b % 2) {
            ans = (ans * a) % mod;
        }
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans;
}

// inverse of a mod prime p (Fermat), O(log p)
ll modinv_p(ll a, ll p) {
    return binexp(a, p - 2, p);
}

// O(n) precompute factorials up to n; mod must be a prime > n
void init_fac(int n, ll mod) {
    fac.assign(n + 1, 1);
    inv_fac.assign(n + 1, 1);
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
    inv_fac[n] = modinv_p(fac[n], mod);
    for (int i = n; i > 0; i--) inv_fac[i - 1] = inv_fac[i] * i % mod;
}

// O(1) nCk mod p, requires init_fac(N, mod) with N >= n
ll comb_f(ll n, ll k, ll mod) {
    if (k < 0 || k > n) return 0;
    return fac[n] * inv_fac[k] % mod * inv_fac[n - k] % mod;
}

void solve() {
    ll t, m;
    cin >> t >> m;
    init_fac(min(m, 10'000'000LL) - 1, m);
    while (t--) {
        ll n, k;
        cin >> n >> k;
        cout << comb_f(n, k, m) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
