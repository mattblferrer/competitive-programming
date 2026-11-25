// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
using cd = complex<double>;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 1'000'000'007;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

// in-place FFT (inverse FFT if invert, including the 1/n scaling); a.size() must be a power of 2, O(n log n)
void fft(vector<cd> &a, bool invert = false) {
    int n = a.size();
    assert(n > 0 && (n & (n - 1)) == 0);
    static vector<cd> rt(2, 1);  // rt[k + j] = e^(i * pi * j / k) for each power of 2 k, 0 <= j < k
    for (static int k = 2; k < n; k *= 2) {
        rt.resize(n);
        for (int j = 0; j < k; j++) rt[k + j] = cd(polar(1.0L, acosl(-1) * j / k));  // long double for accuracy
    }
    for (int i = 1, j = 0; i < n; i++) {  // bit-reversal permutation
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                cd z = rt[k + j] * a[i + j + k];
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
        }
    }
    if (invert) {
        reverse(a.begin() + 1, a.end());
        for (cd &x : a) x /= n;
    }
}

// product of integer polynomials a and b, O((n + m) log(n + m))
// exact while (sum a[i]^2 + sum b[i]^2) * log2(n + m) < ~9e14; use NTT below for results mod a prime
vector<ll> multiply(const vector<ll> &a, const vector<ll> &b) {
    if (a.empty() || b.empty()) return {};
    int need = a.size() + b.size() - 1, n = 1;
    while (n < need) n <<= 1;
    vector<cd> in(n), out(n);
    for (int i = 0; i < (int)a.size(); i++) in[i].real(a[i]);
    for (int i = 0; i < (int)b.size(); i++) in[i].imag(b[i]);
    fft(in);
    for (cd &x : in) x *= x;  // (A + iB)^2 = A^2 - B^2 + 2iAB, so AB is recoverable from one transform
    for (int i = 0; i < n; i++) out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out);
    vector<ll> res(need);
    for (int i = 0; i < need; i++) res[i] = llround(imag(out[i]) / (4 * n));
    return res;
}

// cnt[d] = number of unordered pairs u != v at distance d in a tree, d = 0..n-1 (cnt[0] = 0); uses multiply (FFT)
// centroid decomposition: square the depth counts around each centroid, minus the square inside each child subtree
// (pairs whose path does not pass through the centroid), O(n log^2 n)
vector<ll> tree_distance_counts(const vector<vector<int>> &adj) {
    int n = adj.size();
    vector<ll> cnt(n);
    vector<char> removed(n);
    vector<int> par(n), dep(n), sz(n), todo{0};
    auto bfs = [&](int s, int p, int d) {  // unremoved component of s in BFS order, filling par[] and dep[]
        vector<int> order{s};
        par[s] = p, dep[s] = d;
        for (int i = 0; i < (int)order.size(); i++) {
            int u = order[i];
            for (int v : adj[u]) {
                if (v == par[u] || removed[v]) continue;
                par[v] = u, dep[v] = dep[u] + 1;
                order.push_back(v);
            }
        }
        return order;
    };
    auto count = [&](const vector<int> &order, int sign) {  // add sign * (ordered pairs by depth sum)
        vector<ll> a(dep[order.back()] + 1);
        for (int u : order) a[dep[u]]++;
        vector<ll> sq = multiply(a, a);
        if (sq.size() > cnt.size()) cnt.resize(sq.size());
        for (int d = 0; d < (int)sq.size(); d++) cnt[d] += sign * sq[d];
    };
    while (n && !todo.empty()) {
        int s = todo.back();
        todo.pop_back();
        vector<int> order = bfs(s, -1, 0);
        for (int i = (int)order.size() - 1; i >= 0; i--) {  // subtree sizes, children before parents
            int u = order[i];
            sz[u] = 1;
            for (int v : adj[u]) if (v != par[u] && !removed[v]) sz[u] += sz[v];
        }
        int total = order.size(), c = s;
        for (bool moved = true; moved;) {  // walk toward the heavy child until none has more than half
            moved = false;
            for (int v : adj[c]) {
                if (v != par[c] && !removed[v] && sz[v] * 2 > total) {
                    c = v;
                    moved = true;
                    break;
                }
            }
        }
        count(bfs(c, -1, 0), 1);
        removed[c] = true;
        for (int v : adj[c]) {
            if (removed[v]) continue;
            count(bfs(v, c, 1), -1);
            todo.push_back(v);
        }
    }
    cnt.resize(n);
    for (ll &x : cnt) x /= 2;
    if (n) cnt[0] = 0;
    return cnt;
}

void solve() {
    ll n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (ll i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<ll> cnt = tree_distance_counts(adj);
    for (ll i = 1; i < n; i++) cout << cnt[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
