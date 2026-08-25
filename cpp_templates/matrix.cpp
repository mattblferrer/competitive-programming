#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
const ll MOD = 1'000'000'007;

struct Matrix {
    int n, m; // n rows, m cols
    vector<vector<ll>> a;

    Matrix(int n, int m, bool identity = false): n(n), m(m) {
        a.assign(n, vector<ll>(m, 0));
        if (identity) {
            for (int i = 0; i < min(n, m); i++) a[i][i] = 1;
        }
    }

    Matrix(vector<vector<ll>> vals) {
        a = vals;
        n = a.size();
        m = n ? a[0].size() : 0;
    }

    vector<ll> &operator[](int i) { return a[i]; }
    const vector<ll> &operator[](int i) const { return a[i]; }

    // Matrix multiplication (this * other), dims must match: this.m == other.n
    Matrix operator*(const Matrix &other) const {
        assert(m == other.n);
        Matrix res(n, other.m);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < m; k++) {
                if (!a[i][k]) continue; // small optimization for sparse rows
                ll aik = a[i][k];
                for (int j = 0; j < other.m; j++) {
                    res.a[i][j] = (res.a[i][j] + aik * other.a[k][j]) % MOD;
                }
            }
        }
        return res;
    }

    // Matrix exponentiation (only valid for square matrices)
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