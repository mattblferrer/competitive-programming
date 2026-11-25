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

// binary trie over a multiset of values in [0, 2^BITS), BITS <= 62
//   insert(x)    add one copy of x, O(BITS)
//   erase(x)     remove one copy of x; x must be present, O(BITS)
//   count(x)     number of copies of x, O(BITS)
//   min_xor(x)   smallest x ^ a over the values a; requires a nonempty multiset, O(BITS)
//   max_xor(x)   largest x ^ a over the values a; requires a nonempty multiset, O(BITS)
template <int BITS = 30>
struct XorTrie {
    vector<array<int, 3>> t{{0, 0, 0}};  // {child 0, child 1, count}; node 0 is the root

    void add(ll x, int d) {
        int v = 0;
        t[0][2] += d;
        for (int i = BITS - 1; i >= 0; i--) {
            int b = x >> i & 1;
            if (!t[v][b]) {
                t[v][b] = t.size();
                t.push_back({0, 0, 0});
            }
            v = t[v][b];
            t[v][2] += d;
        }
    }

    void insert(ll x) { add(x, 1); }

    void erase(ll x) { add(x, -1); }

    int count(ll x) const {
        int v = 0;
        for (int i = BITS - 1; i >= 0 && v != -1; i--) v = t[v][x >> i & 1] ? t[v][x >> i & 1] : -1;
        return v == -1 ? 0 : t[v][2];
    }

    ll walk(ll x, int flip) const {  // greedy from the top bit: flip = 0 keeps x's bits (min), 1 flips them (max)
        int v = 0;
        ll res = 0;
        for (int i = BITS - 1; i >= 0; i--) {
            int b = (x >> i & 1) ^ flip;
            if (!t[v][b] || !t[t[v][b]][2]) b ^= 1;
            res |= (ll)(b ^ (x >> i & 1)) << i;
            v = t[v][b];
        }
        return res;
    }

    ll min_xor(ll x) const { return walk(x, 0); }

    ll max_xor(ll x) const { return walk(x, 1); }
};

void solve() {
    ll q;
    cin >> q;
    XorTrie<30> trie;
    for (ll i = 0; i < q; i++) {
        ll t, x;
        cin >> t >> x;
        if (t == 0) {
            if (!trie.count(x)) trie.insert(x);
        }
        else if (t == 1) {
            if (trie.count(x)) trie.erase(x);
        }
        else if (t == 2) {
            cout << trie.min_xor(x) << "\n";
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
