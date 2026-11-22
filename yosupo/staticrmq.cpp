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

// sparse table; S must be idempotent, e.g. min, max, gcd, and shaped like MinOp
struct MinOp {
    using T = ll;
    static T op(const T &a, const T &b) { return min(a, b); }
};

// SparseTable<S>: static range query
//   SparseTable(a)   build from a, O(n log n)
//   query(l, r)      op over [l, r); requires l < r, O(1)
template <class S>
struct SparseTable {
    using T = typename S::T;
    vector<vector<T>> t;

    SparseTable(const vector<T> &a = {}): t(1, a) {
        int n = a.size();
        for (int j = 1; (1 << j) <= n; j++) {
            t.emplace_back(n - (1 << j) + 1);
            for (int i = 0; i + (1 << j) <= n; i++)
                t[j][i] = S::op(t[j - 1][i], t[j - 1][i + (1 << (j - 1))]);
        }
    }

    T query(int l, int r) const {
        int k = __lg(r - l);
        return S::op(t[k][l], t[k][r - (1 << k)]);
    }
};

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    SparseTable<MinOp> st(a);
    for (ll i = 0; i < q; i++) {
        ll li, ri;
        cin >> li >> ri;
        cout << st.query(li, ri) << "\n";
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
