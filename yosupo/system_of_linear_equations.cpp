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

// solves A x = b mod a prime p < 2^31; free variables are set to 0
// returns -1 if there is no solution, else the number of free variables (there are p^that solutions), O(n * m * min(n, m))
// basis gets one solution of A x = 0 per free variable: every solution is x plus a combination of them
int solve_linear_mod(vector<vector<ll>> a, const vector<ll> &b, ll p, vector<ll> &x, vector<vector<ll>> &basis) {
    int n = a.size(), m = n ? a[0].size() : 0;
    for (int i = 0; i < n; i++) a[i].push_back(b[i]);
    ll det;
    int rank = gauss_jordan_mod(a, m, p, det);
    for (int i = rank; i < n; i++) if (a[i][m]) return -1;
    x.assign(m, 0);
    vector<int> row(m, -1);  // row[c] = the row whose pivot is in column c
    for (int i = 0, c = 0; i < rank; i++, c++) {
        while (a[i][c] == 0) c++;
        x[c] = a[i][m];
        row[c] = i;
    }
    basis.clear();
    for (int f = 0; f < m; f++) {  // free variable f = 1, the other free ones 0, then solve for the pivots
        if (row[f] != -1) continue;
        vector<ll> d(m, 0);
        d[f] = 1;
        for (int c = 0; c < m; c++) if (row[c] != -1) d[c] = (p - a[row[c]][f]) % p;
        basis.push_back(d);
    }
    return m - rank;
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> a(n, vector<ll>(m));
    vector<ll> b(n);
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) cin >> a[i][j];
    }
    for (ll i = 0; i < n; i++) cin >> b[i];
    vector<ll> x;
    vector<vector<ll>> basis;
    ll r = solve_linear_mod(a, b, MOD, x, basis);
    if (r == -1) {
        cout << -1 << "\n";
        return;
    }
    cout << r << "\n";
    for (ll j = 0; j < m; j++) cout << x[j] << " ";
    cout << "\n";
    for (ll i = 0; i < r; i++) {
        for (ll j = 0; j < m; j++) cout << basis[i][j] << " ";
        cout << "\n";
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
