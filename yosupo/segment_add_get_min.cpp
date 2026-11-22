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

// Li Chao tree on integer x in [lo, hi], nodes are created as needed so the range can be large
// MAX = false keeps minimums, true keeps maximums; all line values on [lo, hi] must fit in ll and stay below INF
//   LiChao(lo, hi)            empty tree on [lo, hi], O(1)
//   insert(v, line, a, b)     insert a line into node v covering [a, b], O(log(hi - lo))
//   add(m, b)                 add y = m * x + b for all x, O(log(hi - lo))
//   add_segment(l, r, m, b)   add y = m * x + b only for x in [l, r], O(log^2(hi - lo))
//   query(x)                  best value at x, INF (-INF if MAX) if no line covers x, O(log(hi - lo))
template <bool MAX = false>
struct LiChao {
    struct Line {
        ll m, b;
        ll eval(ll x) const { return m * x + b; }
    };
    struct Node { Line line; int l, r; };
    ll lo, hi;
    vector<Node> t;  // t[0] is the root; a child index of 0 means no child

    LiChao(ll lo, ll hi): lo(lo), hi(hi), t(1, Node{Line{0, INF}, 0, 0}) {}

    int new_node(Line line) {
        t.push_back({line, 0, 0});
        return t.size() - 1;
    }

    void insert(int v, Line nw, ll a, ll b) {
        while (true) {
            ll m = a + (b - a) / 2;
            bool left = nw.eval(a) < t[v].line.eval(a);
            bool mid = nw.eval(m) < t[v].line.eval(m);
            if (mid) swap(t[v].line, nw);
            if (a == b) return;
            if (left != mid) {
                if (!t[v].l) {
                    int id = new_node(nw);
                    t[v].l = id;
                    return;
                }
                v = t[v].l;
                b = m;
            }
            else {
                if (!t[v].r) {
                    int id = new_node(nw);
                    t[v].r = id;
                    return;
                }
                v = t[v].r;
                a = m + 1;
            }
        }
    }

    void add(ll m, ll b) { insert(0, MAX ? Line{-m, -b} : Line{m, b}, lo, hi); }

    void add_segment(ll l, ll r, ll m, ll b) { segment(0, MAX ? Line{-m, -b} : Line{m, b}, lo, hi, l, r); }

    void segment(int v, Line nw, ll a, ll b, ll l, ll r) {
        if (r < a || b < l) return;
        if (l <= a && b <= r) {
            insert(v, nw, a, b);
            return;
        }
        ll m = a + (b - a) / 2;
        if (!t[v].l) {
            int id = new_node(Line{0, INF});
            t[v].l = id;
        }
        if (!t[v].r) {
            int id = new_node(Line{0, INF});
            t[v].r = id;
        }
        segment(t[v].l, nw, a, m, l, r);
        segment(t[v].r, nw, m + 1, b, l, r);
    }

    ll query(ll x) const {
        ll res = INF, a = lo, b = hi;
        int v = 0;
        while (true) {
            res = min(res, t[v].line.eval(x));
            if (a == b) break;
            ll m = a + (b - a) / 2;
            int next = x <= m ? t[v].l : t[v].r;
            if (x <= m) b = m;
            else a = m + 1;
            if (!next) break;
            v = next;
        }
        return MAX ? -res : res;
    }
};

void solve() {
    ll n, q;
    cin >> n >> q;
    LiChao<false> lc(-1'000'000'000, 1'000'000'001);
    for (ll i = 0; i < n; i++) {
        ll li, ri, ai, bi;
        cin >> li >> ri >> ai >> bi;
        lc.add_segment(li, ri - 1, ai, bi);
    }
    for (ll i = 0; i < q; i++) {
        ll type;
        cin >> type;
        if (type == 0) {
            ll li, ri, ai, bi;
            cin >> li >> ri >> ai >> bi;
            lc.add_segment(li, ri - 1, ai, bi);
        }
        else if (type == 1) {
            ll p;
            cin >> p;
            ll ans = lc.query(p);
            if (ans == INF) cout << "INFINITY\n";
            else cout << ans << "\n";
        }
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
