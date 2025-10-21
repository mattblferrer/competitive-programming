#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 998244353;

class Matrix {
    public:
    std::vector<std::vector<long long>> mat;

    Matrix(int n) {
        mat.resize(n, std::vector<long long>(n));
        for (int i = 0; i < n; i++) mat[i][i] = 1;
    }
    Matrix(int n, int m) {
        mat.resize(n, std::vector<long long>(m));
    }
    Matrix(std::vector<std::vector<long long>> in) {
        mat = in;
    }
    friend std::ostream& operator<<(std::ostream& out, const Matrix& a) {
        int n = a.mat.size(), m = a.mat[0].size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) std::cout << a.mat[i][j] << " ";
            std::cout << "\n";
        }
        return std::cout;
    }
};

Matrix matrix_input(int n, int m) {
    Matrix a(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) std::cin >> a.mat[i][j];
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

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    Matrix a = matrix_input(n, m), b = matrix_input(m, k);
    cout << multiply(a, b, MOD);
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}