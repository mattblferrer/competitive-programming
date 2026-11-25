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

// characteristic polynomial det(xI - A) mod a prime p, coefficients of x^0..x^n (monic), O(n^3)
// A is first reduced to upper Hessenberg form H by similarity, then det(xI - H) is expanded along the last column:
// P[i + 1] = (x - H[i][i]) P[i] - sum over k < i of H[k][i] H[k + 1][k] ... H[i][i - 1] P[k]
vector<ll> charpoly_mod(vector<vector<ll>> a, ll p) {
    int n = a.size();
    for (auto &row : a) for (ll &x : row) x = (x % p + p) % p;
    for (int j = 0; j + 2 < n; j++) {
        int piv = j + 1;
        while (piv < n && !a[piv][j]) piv++;
        if (piv == n) continue;
        if (piv != j + 1) {  // swap rows and columns j + 1 and piv
            swap(a[piv], a[j + 1]);
            for (auto &row : a) swap(row[piv], row[j + 1]);
        }
        ll inv = binexp(a[j + 1][j], p - 2, p);
        for (int i = j + 2; i < n; i++) {
            ll u = a[i][j] * inv % p;
            if (!u) continue;
            for (int k = 0; k < n; k++) a[i][k] = (a[i][k] - u * a[j + 1][k] % p + p) % p;  // row i -= u row j + 1
            for (int k = 0; k < n; k++) a[k][j + 1] = (a[k][j + 1] + u * a[k][i]) % p;     // col j + 1 += u col i
        }
    }
    vector<vector<ll>> P(n + 1);
    P[0] = {1};
    for (int i = 0; i < n; i++) {
        P[i + 1].assign(i + 2, 0);
        for (int k = 0; k <= i; k++) {
            P[i + 1][k + 1] = (P[i + 1][k + 1] + P[i][k]) % p;
            P[i + 1][k] = (P[i + 1][k] + (p - a[i][i]) * P[i][k]) % p;
        }
        ll prod = 1;
        for (int k = i - 1; k >= 0; k--) {
            prod = prod * a[k + 1][k] % p;
            ll c = prod * a[k][i] % p;
            for (int t = 0; t <= k; t++) P[i + 1][t] = (P[i + 1][t] + (p - c) * P[k][t]) % p;
        }
    }
    return P[n];
}

void solve() {
    ll n;
    cin >> n;
    vector<vector<ll>> a(n, vector<ll>(n));
    for (ll i = 0; i < n; i++) for (ll j = 0; j < n; j++) cin >> a[i][j];
    vector<ll> p = charpoly_mod(a, MOD);
    for (ll i = 0; i <= n; i++) cout << p[i] << " ";
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
