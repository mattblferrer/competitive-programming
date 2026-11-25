// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 998244353;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

// offline: add w to every cell of each rectangle [l, r) x [d, u) in adds = {l, d, r, u, w}, then the sum over each
// rectangle in queries = {l, d, r, u}, mod mod; each add becomes 4 corner weights, and the sum over cells x < X, y < Y
// is the sum over corners (x, y, w) with x < X, y < Y of w (X - x)(Y - y) = w XY - w y X - w x Y + w x y,
// so a sweep over x with Fenwick trees over y for w, w y, w x and w x y answers it, O((n + q) log n)
vector<ll> rect_add_rect_sum(const vector<array<ll, 5>> &adds, const vector<array<ll, 4>> &queries, ll mod) {
    vector<array<ll, 3>> cs;  // {x, y, w}
    for (auto [l, d, r, u, w] : adds) {
        w %= mod;
        ll nw = (mod - w) % mod;
        cs.insert(cs.end(), {{l, d, w}, {l, u, nw}, {r, d, nw}, {r, u, w}});
    }
    sort(cs.begin(), cs.end());
    vector<ll> ys;
    for (auto &c : cs) ys.push_back(c[1]);
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    int m = ys.size();
    vector<array<ll, 4>> bit(m + 1);
    vector<array<ll, 4>> qs;  // {x, y, query id, sign}
    for (int i = 0; i < (int)queries.size(); i++) {
        auto [l, d, r, u] = queries[i];
        qs.insert(qs.end(), {{r, u, i, 1}, {l, u, i, -1}, {r, d, i, -1}, {l, d, i, 1}});
    }
    sort(qs.begin(), qs.end());
    vector<ll> ans(queries.size());
    size_t ci = 0;
    for (auto [X, Y, id, sign] : qs) {
        for (; ci < cs.size() && cs[ci][0] < X; ci++) {
            ll x = cs[ci][0] % mod, y = cs[ci][1] % mod, w = cs[ci][2];
            array<ll, 4> v{w, w * y % mod, w * x % mod, w * x % mod * y % mod};
            for (int i = lower_bound(ys.begin(), ys.end(), cs[ci][1]) - ys.begin() + 1; i <= m; i += i & -i) {
                for (int k = 0; k < 4; k++) bit[i][k] = (bit[i][k] + v[k]) % mod;
            }
        }
        array<ll, 4> s{};
        for (int i = lower_bound(ys.begin(), ys.end(), Y) - ys.begin(); i > 0; i -= i & -i) {  // corners with y < Y
            for (int k = 0; k < 4; k++) s[k] = (s[k] + bit[i][k]) % mod;
        }
        ll xm = X % mod, ym = Y % mod;
        ll f = (xm * ym % mod * s[0] - xm * s[1] % mod - ym * s[2] % mod + s[3]) % mod;
        ans[id] = ((ans[id] + sign * f) % mod + mod) % mod;
    }
    return ans;
}

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<array<ll, 5>> adds(n);
    for (ll i = 0; i < n; i++) for (ll &x : adds[i]) cin >> x;
    vector<array<ll, 4>> queries(q);
    for (ll i = 0; i < q; i++) for (ll &x : queries[i]) cin >> x;
    vector<ll> ans = rect_add_rect_sum(adds, queries, MOD);
    for (ll i = 0; i < q; i++) cout << ans[i] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
