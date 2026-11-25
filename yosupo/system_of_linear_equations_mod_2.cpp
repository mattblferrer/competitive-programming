// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 1'000'000'007;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

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

// solves A x = b over GF(2), using BitMatrix above: false if there is no solution, else x is one solution (free
// variables 0) and the rows of kernel are a basis of A x = 0 (all solutions are x + any sum of them), O(n * m * rank / 64)
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

void solve() {
    ll n, m;
    cin >> n >> m;
    BitMatrix a(n, m), kernel;
    for (ll i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (ll j = 0; j < m; j++) if (s[j] == '1') a.flip(i, j);
    }
    string bs;
    cin >> bs;
    vector<int> b(n), x;
    for (ll i = 0; i < n; i++) b[i] = bs[i] - '0';
    if (!solve_mod2(a, b, x, kernel)) {
        cout << -1 << "\n";
        return;
    }
    cout << kernel.n << "\n";
    for (ll j = 0; j < m; j++) cout << x[j];
    cout << "\n";
    for (ll i = 0; i < kernel.n; i++) {
        string s(m, '0');
        for (ll j = 0; j < m; j++) if (kernel.get(i, j)) s[j] = '1';
        cout << s << "\n";
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
