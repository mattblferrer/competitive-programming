#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
const ld EPS = 1e-12;

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

// reduces a to reduced row echelon form using its first cols columns, returns the rank, O(n * m * min(n, cols))
// det is set to the determinant when a's first cols columns form a square matrix
int gauss_jordan(vector<vector<ld>> &a, int cols, ld &det) {
    int n = a.size(), rank = 0;
    det = 1;
    for (int c = 0; c < cols && rank < n; c++) {
        int p = rank;
        for (int i = rank; i < n; i++) if (fabsl(a[i][c]) > fabsl(a[p][c])) p = i;  // largest pivot, for accuracy
        if (fabsl(a[p][c]) < EPS) {
            det = 0;
            continue;
        }
        if (p != rank) {
            swap(a[p], a[rank]);
            det = -det;
        }
        det *= a[rank][c];
        ld d = a[rank][c];
        for (ld &x : a[rank]) x /= d;
        for (int i = 0; i < n; i++) {
            if (i == rank || a[i][c] == 0) continue;
            ld f = a[i][c];
            for (int j = c; j < (int)a[i].size(); j++) a[i][j] -= f * a[rank][j];
        }
        rank++;
    }
    if (rank < cols) det = 0;
    return rank;
}

// solves A x = b; free variables are set to 0; returns false if there is no solution, O(n * m * min(n, m))
bool solve_linear(vector<vector<ld>> a, const vector<ld> &b, vector<ld> &x) {
    int n = a.size(), m = n ? a[0].size() : 0;
    for (int i = 0; i < n; i++) a[i].push_back(b[i]);
    ld det;
    int rank = gauss_jordan(a, m, det);
    for (int i = rank; i < n; i++) if (fabsl(a[i][m]) > 1e-9) return false;
    x.assign(m, 0);
    for (int i = 0; i < rank; i++) {
        int c = 0;
        while (fabsl(a[i][c]) < EPS) c++;
        x[c] = a[i][m];
    }
    return true;
}

// determinant of a square matrix mod a prime, O(n^3)
ll det_mod(vector<vector<ll>> a, ll p) {
    int n = a.size();
    ll det = 1;
    for (int c = 0; c < n; c++) {
        int r = c;
        while (r < n && a[r][c] % p == 0) r++;
        if (r == n) return 0;
        if (r != c) {
            swap(a[r], a[c]);
            det = (p - det) % p;
        }
        det = det * ((a[c][c] % p + p) % p) % p;
        ll inv = binexp((a[c][c] % p + p) % p, p - 2, p);
        for (int i = c + 1; i < n; i++) {
            ll f = (a[i][c] % p + p) % p * inv % p;
            if (f == 0) continue;
            for (int j = c; j < n; j++) a[i][j] = ((a[i][j] - f * ((a[c][j] % p + p) % p)) % p + p) % p;
        }
    }
    return det;
}

// number of spanning trees of a multigraph mod a prime (Kirchhoff), O(n^3); edges are {u, v}, self-loops are ignored
ll count_spanning_trees(int n, const vector<pair<int, int>> &edges, ll p) {
    if (n == 1) return 1 % p;
    vector<vector<ll>> lap(n, vector<ll>(n, 0));
    for (auto [u, v] : edges) {
        if (u == v) continue;
        lap[u][u]++;
        lap[v][v]++;
        lap[u][v]--;
        lap[v][u]--;
    }
    lap.pop_back();
    for (auto &row : lap) row.pop_back();
    return det_mod(lap, p);
}

// XOR linear basis over values in [0, 2^BITS), BITS <= 62
//   insert(x)     add x; true if x was independent of the basis, O(BITS)
//   contains(x)   true if x is the XOR of some subset of the inserted values, O(BITS)
//   max_xor(x)    largest value of x ^ (XOR of a subset), O(BITS)
//   size()        rank of the basis; there are 2^size() distinct subset XORs, O(1)
//   kth(k)        k-th smallest distinct subset XOR (0-indexed, the empty subset gives 0), -1 if k is too large, O(BITS^2)
template <int BITS = 60>
struct XorBasis {
    array<ll, BITS> b{};  // b[i] has highest set bit i, or is 0
    int rank = 0;

    bool insert(ll x) {
        for (int i = BITS - 1; i >= 0 && x; i--) {
            if (!(x >> i & 1)) continue;
            if (!b[i]) {
                b[i] = x;
                rank++;
                return true;
            }
            x ^= b[i];
        }
        return false;
    }

    bool contains(ll x) const {
        for (int i = BITS - 1; i >= 0 && x; i--) {
            if (x >> i & 1) x ^= b[i];
        }
        return x == 0;
    }

    ll max_xor(ll x = 0) const {
        for (int i = BITS - 1; i >= 0; i--) x = max(x, x ^ b[i]);
        return x;
    }

    int size() const { return rank; }

    ll kth(ll k) const {
        if (k >= (1LL << rank)) return -1;
        array<ll, BITS> r = b;
        for (int i = 0; i < BITS; i++) {  // reduce so each pivot bit appears in only one basis vector
            for (int j = 0; j < i; j++) {
                if (r[j] && (r[i] >> j & 1)) r[i] ^= r[j];
            }
        }
        ll res = 0;
        for (int i = 0, used = 0; i < BITS; i++) {
            if (!r[i]) continue;
            if (k >> used & 1) res ^= r[i];
            used++;
        }
        return res;
    }
};
