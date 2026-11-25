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

// subset convolution: c[k] = sum of a[i] * b[j] over all i | j == k with i & j == 0, mod mod (below 2^31)
// a and b have size 2^n; zeta transforms split by popcount (rank), multiplied rank by rank, O(n^2 2^n)
vector<ll> subset_convolution(const vector<ll> &a, const vector<ll> &b, ll mod) {
    int N = a.size(), n = __lg(N), R = n + 1;
    assert(N == (1 << n) && b.size() == a.size());
    unsigned m = mod;
    vector<unsigned> f((size_t)N * R), g((size_t)N * R);  // f[mask * R + rank]
    for (int s = 0; s < N; s++) {
        f[(size_t)s * R + __builtin_popcount(s)] = a[s] % mod;
        g[(size_t)s * R + __builtin_popcount(s)] = b[s] % mod;
    }
    auto zeta = [&](vector<unsigned> &h, bool invert) {
        for (int bit = 1; bit < N; bit <<= 1) {
            for (int s = 0; s < N; s++) {
                if (!(s & bit)) continue;
                unsigned *x = &h[(size_t)s * R], *y = &h[(size_t)(s ^ bit) * R];
                if (invert) for (int r = 0; r < R; r++) x[r] = x[r] >= y[r] ? x[r] - y[r] : x[r] + m - y[r];
                else for (int r = 0; r < R; r++) x[r] = x[r] + y[r] >= m ? x[r] + y[r] - m : x[r] + y[r];
            }
        }
    };
    zeta(f, false);
    zeta(g, false);
    vector<unsigned> prod(R);
    for (int s = 0; s < N; s++) {
        unsigned *x = &f[(size_t)s * R], *y = &g[(size_t)s * R];
        for (int k = 0; k < R; k++) {
            unsigned long long acc = 0;
            for (int i = 0; i <= k; i++) acc = (acc + (unsigned long long)x[i] * y[k - i]) % m;
            prod[k] = acc;
        }
        copy(prod.begin(), prod.end(), x);
    }
    zeta(f, true);
    vector<ll> c(N);
    for (int s = 0; s < N; s++) c[s] = f[(size_t)s * R + __builtin_popcount(s)];
    return c;
}

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(1 << n), b(1 << n);
    for (ll i = 0; i < (1 << n); i++) cin >> a[i];
    for (ll i = 0; i < (1 << n); i++) cin >> b[i];
    vector<ll> c = subset_convolution(a, b, MOD);
    for (ll i = 0; i < c.size(); i++) cout << c[i] << " ";
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
