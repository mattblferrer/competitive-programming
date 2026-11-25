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

// Stern-Brocot tree of the positive fractions: path from 1/1 to the coprime a/b as runs {'L' or 'R', length}, O(log)
// (the continued fraction of a/b, with its last term decreased by 1)
vector<pair<char, ll>> sb_path(ll a, ll b) {
    vector<pair<char, ll>> path;
    for (char c = 'R'; b; c ^= 'L' ^ 'R') {
        ll q = a / b, r = a % b;
        if (!r) q--;
        if (q) path.push_back({c, q});
        a = b;
        b = r;
    }
    return path;
}

// follows path from 1/1 in the Stern-Brocot tree: returns {p, q, r, s}, where the node reached is (p + r) / (q + s)
// and its descendants are exactly the fractions strictly between p/q and r/s (0/1 and 1/0 stand for 0 and infinity)
array<ll, 4> sb_bounds(const vector<pair<char, ll>> &path) {
    array<ll, 4> t{0, 1, 1, 0};
    for (auto [c, k] : path) {
        if (c == 'R') t[0] += k * t[2], t[1] += k * t[3];
        else t[2] += k * t[0], t[3] += k * t[1];
    }
    return t;
}

// lowest common ancestor of a/b and c/d in the Stern-Brocot tree (longest common prefix of the paths), O(log)
pll sb_lca(ll a, ll b, ll c, ll d) {
    vector<pair<char, ll>> p = sb_path(a, b), q = sb_path(c, d), r;
    for (size_t i = 0; i < min(p.size(), q.size()) && p[i].first == q[i].first; i++) {
        r.push_back({p[i].first, min(p[i].second, q[i].second)});
        if (p[i].second != q[i].second) break;
    }
    array<ll, 4> t = sb_bounds(r);
    return {t[0] + t[2], t[1] + t[3]};
}

// ancestor of a/b at depth k in the Stern-Brocot tree (1/1 has depth 0), {-1, -1} if a/b is shallower, O(log)
pll sb_ancestor(ll k, ll a, ll b) {
    vector<pair<char, ll>> r;
    for (auto [c, len] : sb_path(a, b)) {
        if (!k) break;
        r.push_back({c, min(k, len)});
        k -= r.back().second;
    }
    if (k) return {-1, -1};
    array<ll, 4> t = sb_bounds(r);
    return {t[0] + t[2], t[1] + t[3]};
}

void solve() {
    string type;
    cin >> type;
    if (type == "ENCODE_PATH") {
        ll a, b;
        cin >> a >> b;
        vector<pair<char, ll>> path = sb_path(a, b);
        cout << path.size();
        for (auto [c, k] : path) cout << " " << c << " " << k;
        cout << "\n";
    }
    else if (type == "DECODE_PATH") {
        ll k;
        cin >> k;
        vector<pair<char, ll>> path(k);
        for (ll i = 0; i < k; i++) cin >> path[i].first >> path[i].second;
        array<ll, 4> b = sb_bounds(path);
        cout << b[0] + b[2] << " " << b[1] + b[3] << "\n";
    }
    else if (type == "LCA") {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        auto [f, g] = sb_lca(a, b, c, d);
        cout << f << " " << g << "\n";
    }
    else if (type == "ANCESTOR") {
        ll k, a, b;
        cin >> k >> a >> b;
        auto [f, g] = sb_ancestor(k, a, b);
        if (f == -1) cout << -1 << "\n";
        else cout << f << " " << g << "\n";
    }
    else {
        ll a, b;
        cin >> a >> b;
        array<ll, 4> r = sb_bounds(sb_path(a, b));
        cout << r[0] << " " << r[1] << " " << r[2] << " " << r[3] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    cin >> t;  // comment out for single test
    while (t--) solve();
}
