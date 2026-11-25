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

void solve() {
    ll n, m;
    cin >> n >> m;
    BitMatrix a(n, m);
    for (ll i = 0; i < n && m > 0; i++) {
        string s;
        cin >> s;
        for (ll j = 0; j < m; j++) if (s[j] == '1') a.flip(i, j);
    }
    cout << a.gauss(m).size() << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
