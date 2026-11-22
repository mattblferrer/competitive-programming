// Contents
//   Matrix  dense matrix with entries mod MOD

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// dense matrix with entries mod MOD
// compile-time modulus: using mat = Matrix<1'000'000'007>;
//   each modulus is its own type, so mixing two moduli is a compile error.
// runtime modulus: use a non-positive id, e.g. using dmat = Matrix<0>;
//   then call dmat::set_mod(p) before use (Matrix<-1>, Matrix<-2>, ... for more).
// moduli up to ~4e18 are fine (products above 2^31 go through __int128).
//   mod()                    current modulus, O(1)
//   set_mod(p)               set the runtime modulus (MOD <= 0 only), O(1)
//   Matrix(n, m, identity)   n x m zero matrix (identity if requested), O(nm)
//   Matrix(vals)             from a 2D vector, entries reduced into [0, mod()), O(nm)
//   a[i]                     row access, O(1)
//   a * b                    product this * other mod mod(); requires this.m == other.n, O(n * m * other.m)
//   pow(p)                   this^p for a square matrix, O(n^3 log p)
//   print()                  print the matrix, one row per line, O(nm)
template <ll MOD>
struct Matrix {
    static inline ll dyn = 1; // runtime modulus (only used when MOD <= 0)
    static constexpr bool is_static = MOD > 0;
    static ll mod() {
        if constexpr (is_static) return MOD;
        else return dyn;
    }
    static void set_mod(ll p) {
        static_assert(!is_static, "set_mod is only for runtime moduli (MOD <= 0)");
        dyn = p;
    }
    static ll mul(ll x, ll y) {
        if (mod() < (1LL << 31)) return x * y % mod();
        return (__int128)x * y % mod();
    }

    int n, m; // n rows, m cols
    vector<vector<ll>> a;

    Matrix(int n, int m, bool identity = false): n(n), m(m) {
        a.assign(n, vector<ll>(m, 0));
        if (identity) {
            for (int i = 0; i < min(n, m); i++) a[i][i] = 1 % mod();
        }
    }

    Matrix(const vector<vector<ll>> &vals): n(vals.size()), m(vals.empty() ? 0 : vals[0].size()), a(vals) {
        for (auto &row : a) {
            for (ll &x : row) {
                x %= mod();
                if (x < 0) x += mod();
            }
        }
    }

    vector<ll> &operator[](int i) { return a[i]; }
    const vector<ll> &operator[](int i) const { return a[i]; }

    Matrix operator*(const Matrix &other) const {
        assert(m == other.n);
        Matrix res(n, other.m);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < m; k++) {
                if (!a[i][k]) continue; // small optimization for sparse rows
                ll aik = a[i][k];
                for (int j = 0; j < other.m; j++) {
                    ll v = res.a[i][j] + mul(aik, other.a[k][j]);
                    res.a[i][j] = v >= mod() ? v - mod() : v;
                }
            }
        }
        return res;
    }

    Matrix pow(ll p) const {
        assert(n == m);
        Matrix result(n, n, true); // identity
        Matrix base = *this;
        while (p > 0) {
            if (p & 1) result = result * base;
            base = base * base;
            p >>= 1;
        }
        return result;
    }

    void print() const {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << a[i][j] << " \n"[j == m - 1];
            }
        }
    }
};
