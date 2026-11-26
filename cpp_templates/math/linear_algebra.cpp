// Contents
//   binexp                         a^b mod mod, O(log b)
//   gauss_jordan                   reduces a to reduced row echelon form using its first cols columns, returns the rank
//   solve_linear                   solves A x = b; free variables are set to 0; returns false if there is no solution
//   gauss_jordan_mod               reduces a to reduced row echelon form mod a prime p < 2^31
//                                  using its first cols columns
//   solve_linear_mod               solves A x = b mod a prime p < 2^31; free variables are set to 0;
//                                  also a basis of A x = 0
//   inverse_mod                    inverse of a square matrix mod a prime p < 2^31;
//                                  returns false if it is singular, O(n^3)
//   solve_xor                      solves A x = b over GF(2) (XOR equations) with m <= N variables
//   det_mod                        determinant of a square matrix mod a prime, O(n^3)
//   count_spanning_trees           number of spanning trees of a multigraph mod a prime (Kirchhoff), O(n^3)
//   count_spanning_trees_directed  number of spanning arborescences rooted at r of a directed multigraph mod a prime,
//                                  O(n^3)
//   charpoly_mod                   characteristic polynomial det(xI - A) mod a prime (Hessenberg form), O(n^3)
//   BitMatrix                      n x m matrix over GF(2) with rows packed into 64-bit words; gauss gives the RREF
//   det_mod2                       determinant of a square matrix over GF(2), O(n^3 / 64)
//   inverse_mod2                   inverse of a square matrix over GF(2); false if it is singular, O(n^3 / 64)
//   solve_mod2                     solves A x = b over GF(2): one solution and a basis of A x = 0, O(n * m * rank / 64)
//   mul_mod2                       product of an n x m and an m x l matrix over GF(2), O(n * m * l / 64)
//   XorBasis                       XOR linear basis over values in [0, 2^BITS), BITS <= 62

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
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
// returns -1 if there is no solution, else the number of free variables (there are p^that solutions),
// O(n * m * min(n, m))
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

// inverse of a square matrix mod a prime p < 2^31; returns false if it is singular, O(n^3)
bool inverse_mod(vector<vector<ll>> a, ll p, vector<vector<ll>> &inv) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        a[i].resize(2 * n, 0);
        a[i][n + i] = 1;
    }
    ll det;
    if (gauss_jordan_mod(a, n, p, det) < n) return false;
    inv.assign(n, {});
    for (int i = 0; i < n; i++) inv[i].assign(a[i].begin() + n, a[i].end());
    return true;
}

// solves A x = b over GF(2) (XOR equations) with m <= N variables; row i of A is the bitset a[i];
// free variables are set to 0
// returns -1 if there is no solution, else the number of free variables (there are 2^that solutions),
// O(n * m * min(n, m) / 64)
template <size_t N>
int solve_xor(vector<bitset<N>> a, vector<int> b, int m, bitset<N> &x) {
    int n = a.size(), rank = 0;
    vector<int> where(m, -1);  // where[c] = row whose pivot is column c
    for (int c = 0; c < m && rank < n; c++) {
        int r = rank;
        while (r < n && !a[r][c]) r++;
        if (r == n) continue;
        swap(a[r], a[rank]);
        swap(b[r], b[rank]);
        for (int i = 0; i < n; i++) {
            if (i != rank && a[i][c]) {
                a[i] ^= a[rank];
                b[i] ^= b[rank];
            }
        }
        where[c] = rank++;
    }
    for (int i = rank; i < n; i++) if (b[i]) return -1;
    x.reset();
    for (int c = 0; c < m; c++) if (where[c] != -1) x[c] = b[where[c]];
    return m - rank;
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

// number of spanning arborescences rooted at r (every vertex reachable from r) of a directed multigraph mod a prime,
// edges are {u, v} for u -> v and self-loops are ignored; matrix-tree theorem on the in-degree Laplacian, O(n^3)
ll count_spanning_trees_directed(int n, const vector<pair<int, int>> &edges, int r, ll p) {
    vector<vector<ll>> lap(n, vector<ll>(n, 0));
    for (auto [u, v] : edges) {
        if (u == v) continue;
        lap[v][v]++;
        lap[u][v]--;
    }
    lap.erase(lap.begin() + r);
    for (auto &row : lap) row.erase(row.begin() + r);
    return n == 1 ? 1 % p : det_mod(lap, p);
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

// n x m matrix over GF(2), rows packed into 64-bit words in one array (no size limit, unlike solve_xor's bitset)
//   BitMatrix(n, m)   all zeros, O(nm / 64)
//   get(i, j)         entry (i, j), O(1)
//   flip(i, j)        toggle entry (i, j), O(1)
//   row(i)            pointer to the w = ceil(m / 64) words of row i
//   gauss(cols)       reduced row echelon form using the first cols columns, in place; returns the pivot columns,
//                     pivot k in row k (rank = their count), O(n * m * rank / 64)
struct BitMatrix {
    int n, m, w;
    vector<ull> d;

    BitMatrix(int n = 0, int m = 0): n(n), m(m), w((m + 63) / 64), d((size_t)n * w) {}

    ull *row(int i) { return d.data() + (size_t)i * w; }
    bool get(int i, int j) const { return d[(size_t)i * w + j / 64] >> (j % 64) & 1; }
    void flip(int i, int j) { d[(size_t)i * w + j / 64] ^= 1ULL << (j % 64); }

    vector<int> gauss(int cols) {
        vector<int> piv;
        for (int c = 0, r = 0; c < cols && r < n; c++) {
            int i = r;
            while (i < n && !get(i, c)) i++;
            if (i == n) continue;
            swap_ranges(row(i), row(i) + w, row(r));
            for (i = 0; i < n; i++) {
                if (i == r || !get(i, c)) continue;
                ull *x = row(i), *y = row(r);
                for (int k = c / 64; k < w; k++) x[k] ^= y[k];  // words before c / 64 are 0 in row r
            }
            piv.push_back(c);
            r++;
        }
        return piv;
    }
};

// determinant of a square matrix over GF(2), using BitMatrix above, O(n^3 / 64)
bool det_mod2(BitMatrix a) { return (int)a.gauss(a.n).size() == a.n; }

// inverse of a square matrix over GF(2), using BitMatrix above; false if it is singular, O(n^3 / 64)
bool inverse_mod2(const BitMatrix &a, BitMatrix &inv) {
    int n = a.n;
    BitMatrix aug(n, 2 * n);  // [A | I]
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) if (a.get(i, j)) aug.flip(i, j);
        aug.flip(i, n + i);
    }
    if ((int)aug.gauss(n).size() < n) return false;
    inv = BitMatrix(n, n);
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (aug.get(i, n + j)) inv.flip(i, j);
    return true;
}

// solves A x = b over GF(2), using BitMatrix above: false if there is no solution, else x is one solution (free
// variables 0) and the rows of kernel are a basis of A x = 0 (all solutions are x + any sum of them),
// O(n * m * rank / 64)
bool solve_mod2(const BitMatrix &a, const vector<int> &b, vector<int> &x, BitMatrix &kernel) {
    int n = a.n, m = a.m;
    BitMatrix aug(n, m + 1);  // [A | b]
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) if (a.get(i, j)) aug.flip(i, j);
        if (b[i]) aug.flip(i, m);
    }
    vector<int> piv = aug.gauss(m);
    int r = piv.size();
    for (int i = r; i < n; i++) if (aug.get(i, m)) return false;
    x.assign(m, 0);
    vector<char> is_piv(m);
    for (int i = 0; i < r; i++) x[piv[i]] = aug.get(i, m), is_piv[piv[i]] = 1;
    kernel = BitMatrix(m - r, m);
    for (int f = 0, k = 0; f < m; f++) {  // free variable f = 1, the other free variables 0
        if (is_piv[f]) continue;
        kernel.flip(k, f);
        for (int i = 0; i < r; i++) if (aug.get(i, f)) kernel.flip(k, piv[i]);
        k++;
    }
    return true;
}

// product of an n x m and an m x l matrix over GF(2), using BitMatrix above: row i of a b is the XOR of the rows k of b
// with a(i, k) = 1, O(n * m * l / 64)
BitMatrix mul_mod2(const BitMatrix &a, const BitMatrix &b) {
    BitMatrix c(a.n, b.m);
    for (int i = 0; i < a.n; i++) {
        ull *x = c.row(i);
        for (int k = 0; k < a.m; k++) {
            if (!a.get(i, k)) continue;
            const ull *y = b.d.data() + (size_t)k * b.w;
            for (int j = 0; j < c.w; j++) x[j] ^= y[j];
        }
    }
    return c;
}

// XOR linear basis over values in [0, 2^BITS), BITS <= 62
//   insert(x)     add x; true if x was independent of the basis, O(BITS)
//   contains(x)   true if x is the XOR of some subset of the inserted values, O(BITS)
//   max_xor(x)    largest value of x ^ (XOR of a subset), O(BITS)
//   size()        rank of the basis; there are 2^size() distinct subset XORs, O(1)
//   kth(k)        k-th smallest distinct subset XOR (0-indexed, the empty subset gives 0), -1 if k is too large,
//                 O(BITS^2)
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
