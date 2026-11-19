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

// disjoint set union with path compression and union by size
//   DSU(n)               n singleton sets {0}, ..., {n - 1}, O(n)
//   find_set(a)          representative of a's set, O(alpha(n)) amortized
//   union_sets(a, b)     merge the sets of a and b; false if already in the same set, O(alpha(n))
//   is_connected(a, b)   whether a and b are in the same set, O(alpha(n))
struct DSU {
    vector<int> parent, sz;

    DSU(int n): parent(n), sz(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find_set(int a) {
        if (parent[a] == a) return a;
        return parent[a] = find_set(parent[a]);
    }

    bool union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }

    bool is_connected(int a, int b) { return find_set(a) == find_set(b); }
};

// a^b mod mod, O(log b)
ll binexp(ll a, ll b, ll mod) {
    ll ans = 1;
    a %= mod;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

// number theoretic transform, each MOD and ROOT pair is its own type:
//   using ntt1 = NTT<998'244'353, 3>;
//   using ntt2 = NTT<469'762'049, 3>;
//   vector<ll> c = ntt1::multiply(a, b);
// MOD must be a prime below 2^31 and ROOT a primitive root of MOD
// the largest transform size is the largest power of 2 dividing MOD - 1
// choices of (MOD, ROOT), max size:
//   (998'244'353, 3), 2^23
//   (469'762'049, 3), 2^26
//   (167'772'161, 3), 2^25
//   (754'974'721, 11), 2^24
//   (1'004'535'809, 3), 2^21
//   (2'013'265'921, 31), 2^27
//   ntt(a, invert)   in-place NTT (inverse if invert); a.size() must be a power of 2 up to the max size, O(n log n)
//   multiply(a, b)   product of polynomials a and b mod MOD, O((n + m) log(n + m))
template <ll MOD, ll ROOT>
struct NTT {
    static void ntt(vector<ll> &a, bool invert = false) {
        int n = a.size();
        assert(n > 0 && (n & (n - 1)) == 0 && (MOD - 1) % n == 0);
        for (int i = 1, j = 0; i < n; i++) {  // bit-reversal permutation
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) swap(a[i], a[j]);
        }
        for (int len = 2; len <= n; len <<= 1) {
            ll w = binexp(ROOT, (MOD - 1) / len, MOD);
            if (invert) w = binexp(w, MOD - 2, MOD);
            for (int i = 0; i < n; i += len) {
                ll wn = 1;
                for (int j = 0; j < len / 2; j++) {
                    ll u = a[i + j], v = a[i + j + len / 2] * wn % MOD;
                    a[i + j] = u + v < MOD ? u + v : u + v - MOD;
                    a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + MOD;
                    wn = wn * w % MOD;
                }
            }
        }
        if (invert) {
            ll n_inv = binexp(n, MOD - 2, MOD);
            for (ll &x : a) x = x * n_inv % MOD;
        }
    }

    static vector<ll> multiply(vector<ll> a, vector<ll> b) {
        if (a.empty() || b.empty()) return {};
        int need = a.size() + b.size() - 1, n = 1;
        while (n < need) n <<= 1;
        for (ll &x : a) x = (x % MOD + MOD) % MOD;
        for (ll &x : b) x = (x % MOD + MOD) % MOD;
        a.resize(n);
        b.resize(n);
        ntt(a);
        ntt(b);
        for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % MOD;
        ntt(a, true);
        a.resize(need);
        return a;
    }
};

void solve() {
    string s, t;
    cin >> s >> t;
    ll n = s.size(), m = t.size();
    vector<vector<ll>> freq_s(6, vector<ll>(n)), freq_t(6, vector<ll>(m));

    for (ll i = 0; i < n; i++) {
        freq_s[s[i] - 'a'][i] = 1;
    }
    for (ll i = 0; i < m; i++) {
        freq_t[t[i] - 'a'][m - 1 - i] = 1;
    }

    using ntt = NTT<998'244'353, 3>;
    vector<vector<vector<bool>>> edges(n - m + 1, vector<vector<bool>>(6, vector<bool>(6)));
    for (ll i = 0; i < 6; i++) {
        for (ll j = 0; j < 6; j++) {
            if (i == j) continue;

            vector<ll> prod = ntt::multiply(freq_s[i], freq_t[j]);
            for (ll k = 0; k < n - m + 1; k++) {
                if (prod[k + m - 1]) edges[k][i][j] = true;
            }
        }
    }
    for (ll k = 0; k < n - m + 1; k++) {
        ll ops = 0;
        DSU dsu(6);
        for (ll i = 0; i < 6; i++) {
            for (ll j = 0; j < 6; j++) {
                if (edges[k][i][j]) ops += dsu.union_sets(i, j);
            }
        }
        cout << ops << " ";
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
