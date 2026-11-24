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

// reduces a to reduced row echelon form mod a prime p < 2^31 using its first cols columns, returns the rank,
// O(n * m * min(n, cols)); det is set to the determinant when a's first cols columns form a square matrix
int gauss_jordan_mod(vector<vector<ll>> &a, int cols, ll p, ll &det) {
    int n = a.size(), rank = 0;
    det = 1;
    for (auto &row : a) for (ll &x : row) x = (x % p + p) % p;
    for (int c = 0; c < cols && rank < n; c++) {
        int r = rank;
        while (r < n && a[r][c] == 0) r++;
        if (r == n) continue;
        if (r != rank) {
            swap(a[r], a[rank]);
            det = (p - det) % p;
        }
        det = det * a[rank][c] % p;
        ll inv = binexp(a[rank][c], p - 2, p);
        for (ll &x : a[rank]) x = x * inv % p;
        for (int i = 0; i < n; i++) {
            if (i == rank || a[i][c] == 0) continue;
            ll f = a[i][c];
            for (int j = c; j < (int)a[i].size(); j++) a[i][j] = (a[i][j] + (p - f) * a[rank][j]) % p;
        }
        rank++;
    }
    if (rank < cols) det = 0;
    return rank;
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> a(n, vector<ll>(m));
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) cin >> a[i][j];
    }
    ll det;
    cout << gauss_jordan_mod(a, m, MOD, det) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
