// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 1'000'000'007;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

// returns g = gcd(a, b) and sets x, y so that ax + by = g, O(log min(a, b))
ll extended_euclidean(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll gcd = extended_euclidean(b, a % b, y, x);
    y -= (a / b) * x;
    return gcd;
}

// solves a * x = b (mod m), m > 0: returns {x, M} meaning all solutions are x mod M, nullopt if none, O(log m)
optional<pll> mod_solver(ll a, ll b, ll m) {
    a = (a % m + m) % m;
    b = (b % m + m) % m;
    ll x, y, g = extended_euclidean(a, m, x, y);
    if (b % g != 0) return nullopt;
    ll M = m / g;
    x = (x % M + M) % M;
    return pll((__int128)x * (b / g) % M, M);
}

// functional graph v -> f[v]: each component is one cycle with in-trees hanging off it
//   cycles[c]     vertices of cycle c in order, cycles[c][i + 1] = f[cycles[c][i]]
//   cyc[v]        id of the cycle that v reaches; pos[v] = index of v in it, -1 if v is not on a cycle
//   root[v]       first cycle vertex reached from v; depth[v] = steps to get there (0 on a cycle)
//   FunctionalGraph(f)   O(n log n)
//   jump(v, k)           f^k(v) for any k >= 0, O(log n)
//   dist(u, v)           smallest k >= 0 with f^k(u) = v, -1 if there is none, O(log n)
struct FunctionalGraph {
    int n, LOG = 1;
    vector<int> cyc, pos, root, depth;
    vector<vector<int>> cycles, up;  // up[j][v] = f^(2^j)(v)

    FunctionalGraph(const vector<int> &f): n(f.size()), cyc(n), pos(n, -1), root(n), depth(n) {
        vector<char> state(n);  // 0 unseen, 1 on the current walk, 2 done
        for (int s = 0; s < n; s++) {
            vector<int> walk;
            int v = s;
            while (!state[v]) state[v] = 1, walk.push_back(v), v = f[v];
            if (state[v] == 1) {  // the walk ran into itself: v starts a new cycle
                cycles.emplace_back();
                int u = v;
                do {
                    cyc[u] = cycles.size() - 1, pos[u] = cycles.back().size(), root[u] = u;
                    cycles.back().push_back(u);
                    u = f[u];
                } while (u != v);
            }
            for (int i = walk.size() - 1; i >= 0; i--) {
                int u = walk[i];
                state[u] = 2;
                if (pos[u] < 0) cyc[u] = cyc[f[u]], root[u] = root[f[u]], depth[u] = depth[f[u]] + 1;
            }
        }
        while ((1 << LOG) < n) LOG++;
        up.assign(LOG, f);
        for (int j = 1; j < LOG; j++) for (int v = 0; v < n; v++) up[j][v] = up[j - 1][up[j - 1][v]];
    }

    int jump(int v, ll k) const {
        if (k >= depth[v]) {
            auto &c = cycles[cyc[v]];
            return c[(pos[root[v]] + (k - depth[v])) % c.size()];
        }
        for (int j = 0; k; j++, k >>= 1) if (k & 1) v = up[j][v];
        return v;
    }

    ll dist(int u, int v) const {
        if (pos[v] >= 0) {
            if (cyc[u] != cyc[v]) return -1;
            int L = cycles[cyc[v]].size();
            return depth[u] + (pos[v] - pos[root[u]] + L) % L;
        }
        if (root[u] != root[v] || depth[u] < depth[v]) return -1;
        return jump(u, depth[u] - depth[v]) == v ? depth[u] - depth[v] : -1;
    }
};

// decimal string of an __int128, including -2^127; the unsigned overload covers all of [0, 2^128), O(digits)
string to_string128(u128 x) {
    string s;
    do s += char('0' + x % 10); while (x /= 10);
    return string(s.rbegin(), s.rend());
}

string to_string128(i128 x) { return x < 0 ? "-" + to_string128(-(u128)x) : to_string128((u128)x); }

ostream &operator<<(ostream &os, i128 x) { return os << to_string128(x); }
ostream &operator<<(ostream &os, u128 x) { return os << to_string128(x); }

bool step(const vector<ll> &f, i128 &energy, i128 &t) {
    i128 k = f[energy % f.size()];
    if (k > energy) {
        t += energy * (energy + 1) / 2;
        return false;
    }
    t += k * energy - k * (k - 1) / 2;
    energy += 2 - k;
    return true;
}

void solve() {
    ll n, e;
    cin >> n >> e;

    vector<ll> f(n, 0);
    ll left = n;
    for (ll k = 1; k <= 2 * n && left > 0; k++) {
        auto sol = mod_solver(k, k * (k - 1) / 2, n);
        if (!sol) continue;
        auto [r0, d] = *sol;
        for (ll r = r0; r < n; r += d) {
            if (f[r] == 0) {
                f[r] = k;
                left--;
            }
        }
    }

    i128 energy = e, t = 0;
    vector<int> nxt(n);
    for (ll r = 0; r < n; r++) nxt[r] = ((r - f[r] + 2) % n + n) % n;
    FunctionalGraph fg(nxt);
    for (ll i = fg.depth[energy % n]; i > 0; i--) {
        if (!step(f, energy, t)) { cout << t << '\n'; return; }
    }

    auto &c = fg.cycles[fg.cyc[energy % n]];
    ll lap_len = c.size(), p = fg.pos[energy % n];
    i128 lap_t = 0, k_sum = 0, loss = 0, slack = LLONG_MAX, x = energy;
    for (ll i = 0; i < lap_len; i++) {
        i128 k = f[c[(p + i) % lap_len]];
        slack = min(slack, x - k);
        lap_t += k * x - k * (k - 1) / 2;
        k_sum += k;
        loss += k - 2;
        x += 2 - k;
    }

    if (slack >= 0) {
        if (loss <= 0) { cout << "infinity\n"; return; }
        i128 q = slack / loss + 1;
        t += q * lap_t - k_sum * loss * (q * (q - 1) / 2);
        energy -= q * loss;
    }

    while (step(f, energy, t));
    cout << t << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
