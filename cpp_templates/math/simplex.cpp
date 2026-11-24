// Contents
//   Simplex         two-phase simplex: maximize c^T x subject to A x <= b, x >= 0; A is m x n

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// two-phase simplex: maximize c^T x subject to A x <= b, x >= 0; A is m x n, O(pivots * n * m)
//   Simplex(A, b, c)   set up the tableau, O(nm)
//   pivot(r, s)        pivot on row r, column s, O(nm)
//   run(phase)         pivot until optimal; false if unbounded
//   solve(x)           optimal value (and x), +infinity if unbounded, -infinity if infeasible
struct Simplex {
    static constexpr ld EPS = 1e-9;
    int m, n;
    vector<int> B, N;
    vector<vector<ld>> D;

    Simplex(const vector<vector<ld>> &A, const vector<ld> &b, const vector<ld> &c)
        : m(b.size()), n(c.size()), B(m), N(n + 1), D(m + 2, vector<ld>(n + 2)) {
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) D[i][j] = A[i][j];
        for (int i = 0; i < m; i++) {
            B[i] = n + i;
            D[i][n] = -1;
            D[i][n + 1] = b[i];
        }
        for (int j = 0; j < n; j++) {
            N[j] = j;
            D[m][j] = -c[j];
        }
        N[n] = -1;
        D[m + 1][n] = 1;
    }

    void pivot(int r, int s) {
        ld inv = 1.0L / D[r][s];
        for (int i = 0; i < m + 2; i++) {
            if (i == r) continue;
            for (int j = 0; j < n + 2; j++) if (j != s) D[i][j] -= D[r][j] * D[i][s] * inv;
        }
        for (int j = 0; j < n + 2; j++) if (j != s) D[r][j] *= inv;
        for (int i = 0; i < m + 2; i++) if (i != r) D[i][s] *= -inv;
        D[r][s] = inv;
        swap(B[r], N[s]);
    }

    bool run(int phase) {
        int x = phase == 1 ? m + 1 : m;
        while (true) {
            int s = -1;
            for (int j = 0; j <= n; j++) {
                if (phase == 2 && N[j] == -1) continue;
                if (s == -1 || D[x][j] < D[x][s] || (D[x][j] == D[x][s] && N[j] < N[s])) s = j;
            }
            if (D[x][s] > -EPS) return true;
            int r = -1;
            for (int i = 0; i < m; i++) {
                if (D[i][s] < EPS) continue;
                if (r == -1) {
                    r = i;
                    continue;
                }
                ld cur = D[i][n + 1] / D[i][s], low = D[r][n + 1] / D[r][s];
                if (cur < low || (cur == low && B[i] < B[r])) r = i;
            }
            if (r == -1) return false;
            pivot(r, s);
        }
    }

    ld solve(vector<ld> &x) {
        int r = 0;
        for (int i = 1; i < m; i++) if (D[i][n + 1] < D[r][n + 1]) r = i;
        if (m > 0 && D[r][n + 1] < -EPS) {
            pivot(r, n);
            if (!run(1) || D[m + 1][n + 1] < -EPS) return -numeric_limits<ld>::infinity();
            for (int i = 0; i < m; i++) {
                if (B[i] != -1) continue;
                int s = -1;
                for (int j = 0; j <= n; j++)
                    if (s == -1 || D[i][j] < D[i][s] || (D[i][j] == D[i][s] && N[j] < N[s])) s = j;
                pivot(i, s);
            }
        }
        if (!run(2)) return numeric_limits<ld>::infinity();
        x = vector<ld>(n);
        for (int i = 0; i < m; i++) if (B[i] < n) x[B[i]] = D[i][n + 1];
        return D[m][n + 1];
    }
};
