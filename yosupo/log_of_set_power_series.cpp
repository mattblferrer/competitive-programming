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

// ranked zeta transform for the subset convolution family: h[s * R + r] holds rank r of mask s (R = n + 1, h.size()
// = 2^n R); each rank becomes the sum over submasks of s (undone if invert), mod m, O(n^2 2^n)
void ranked_zeta(vector<unsigned> &h, int R, unsigned m, bool invert = false) {
    int N = h.size() / R;
    for (int bit = 1; bit < N; bit <<= 1) {
        for (int s = 0; s < N; s++) {
            if (!(s & bit)) continue;
            unsigned *x = &h[(size_t)s * R], *y = &h[(size_t)(s ^ bit) * R];
            if (invert) for (int r = 0; r < R; r++) x[r] = x[r] >= y[r] ? x[r] - y[r] : x[r] + m - y[r];
            else for (int r = 0; r < R; r++) x[r] = x[r] + y[r] >= m ? x[r] + y[r] - m : x[r] + y[r];
        }
    }
}

// log of a set power series, the inverse of subset_exp above: a has size 2^n with a[0] == 1, and the result has
// result[0] = 0, mod a prime mod (below 2^31, above n); per mask the ranked transform is a polynomial f(z) with
// f(0) = 1, and g = log(f) solves z f g' = z f', using ranked_zeta above, O(n^2 2^n)
vector<ll> subset_log(const vector<ll> &a, ll mod) {
    int N = a.size(), n = __lg(N), R = n + 1;
    assert(N == (1 << n) && a[0] % mod == 1);
    unsigned m = mod;
    vector<unsigned> f((size_t)N * R), inv(R, 1), F(R);
    for (int i = 2; i < R; i++) inv[i] = (unsigned long long)(m - m / i) * inv[m % i] % m;
    for (int s = 0; s < N; s++) f[(size_t)s * R + __builtin_popcount(s)] = a[s] % mod;
    ranked_zeta(f, R, m);
    for (int s = 0; s < N; s++) {
        unsigned *x = &f[(size_t)s * R];
        copy(x, x + R, F.begin());
        x[0] = 0;
        for (int k = 1; k < R; k++) {  // x[i] holds i g_i: k g_k = k f_k - sum of i g_i f_(k - i), 0 < i < k
            unsigned long long acc = 0;
            for (int i = 1; i < k; i++) acc = (acc + (unsigned long long)x[i] * F[k - i]) % m;
            x[k] = ((unsigned long long)F[k] * k + m - acc) % m;
        }
        for (int k = 1; k < R; k++) x[k] = (unsigned long long)x[k] * inv[k] % m;
    }
    ranked_zeta(f, R, m, true);
    vector<ll> b(N);
    for (int s = 0; s < N; s++) b[s] = f[(size_t)s * R + __builtin_popcount(s)];
    return b;
}

void solve() {
    ll n;
    cin >> n;
    vector<ll> b(1 << n);
    for (ll i = 0; i < (1 << n); i++) cin >> b[i];
    vector<ll> c = subset_log(b, MOD);
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
