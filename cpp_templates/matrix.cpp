#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

class Matrix {
    public:
    vector<vector<ll>> mat;

    Matrix(int n) {
        mat.resize(n, vector<ll>(n));
        for (int i = 0; i < n; i++) mat[i][i] = 1;
    }
    Matrix(int n, int m) {
        mat.resize(n, vector<ll>(m));
    }
    Matrix(vector<vector<ll>> in) {
        mat = in;
    }
    friend ostream& operator<<(ostream& out, const Matrix& a) {
        int n = a.mat.size(), m = a.mat[0].size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) cout << a.mat[i][j] << " ";
            cout << "\n";
        }
        return cout;
    }
};

Matrix matrix_input(int n, int m) {
    Matrix a(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cin >> a.mat[i][j];
    }   
    return a;
}

Matrix multiply(const Matrix a, const Matrix b, ll mod) {
    int n1 = a.mat.size(), m1 = a.mat[0].size();
    int n2 = b.mat.size(), m2 = b.mat[0].size();
    Matrix c(n1, m2);
    for (int i = 0; i < n1; i++) {
        for (int k = 0; k < m1; k++) {
            for (int j = 0; j < m2; j++) {
                c.mat[i][j] = (c.mat[i][j] + a.mat[i][k] * b.mat[k][j]) % mod;
            }
        }
    }
    return c;
}

Matrix power(Matrix a, ll b, ll mod) {
    Matrix ans = Matrix(a.mat.size());
    while (b) {
        if (b % 2) {
            ans = multiply(ans, a, mod);
        }
        a = multiply(a, a, mod);
        b >>= 1;
    }
    return ans;
}