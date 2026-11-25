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

// compile-time modulus: using mint = ModInt<1'000'000'007>;
//   each modulus is its own type, so mixing two moduli is a compile error.
// runtime modulus: use a non-positive id, e.g. using dmint = ModInt<0>;
//   then call dmint::set_mod(p) before use (ModInt<-1>, ModInt<-2>, ... for more).
// inv() works for any modulus coprime to val (prime not required).
//   mod()                      current modulus, O(1)
//   set_mod(m)                 set the runtime modulus (MOD <= 0 only), O(1)
//   mul(a, b)                  a * b % mod(), O(1)
//   ModInt(v)                  v % mod(), normalized to [0, mod()), O(1)
//   pow(e)                     this^e, O(log e)
//   inv()                      modular inverse via extended Euclid, O(log mod()); requires gcd(val, mod()) = 1
//   +, -, *, / (and +=, ...)   arithmetic, O(1) (division is O(log mod()))
// friends so that e.g. 2 + x and 1 - x also work
template <ll MOD>
struct ModInt {
    ll val;
    static inline ll dyn = 1;  // runtime modulus (only used when MOD <= 0)
    static inline ull im = 0;  // Barrett constant for the runtime modulus

    static constexpr bool is_static = MOD > 0;
    static ll mod() {
        if constexpr (is_static) return MOD;
        else return dyn;
    }
    static void set_mod(ll m) {
        dyn = m;
        im = ~0ULL / m + 1;
    }
    static ll mul(ll a, ll b) {
        if constexpr (is_static) {
            if constexpr (MOD < (1LL << 31)) return a * b % MOD;
            else return (__int128)a * b % MOD;
        }
        else if (dyn < (1LL << 31)) {  // Barrett reduction, avoids slow % by a variable
            ull z = (ull)a * b;
            ull x = (ull)(((unsigned __int128)z * im) >> 64), y = x * dyn;
            return z - y + (z < y ? dyn : 0);
        }
        else return (__int128)a * b % dyn;
    }

    ModInt(ll v = 0): val(v % mod()) { if (val < 0) val += mod(); }

    ModInt pow(ll e) const {
        ModInt r = 1, b = *this;
        for (; e > 0; e >>= 1, b *= b) if (e & 1) r *= b;
        return r;
    }
    ModInt inv() const {
        ll a = val, b = mod(), x = 1, y = 0;
        while (b) {
            ll q = a / b;
            swap(a -= q * b, b);
            swap(x -= q * y, y);
        }
        assert(a == 1);  // inverse doesn't exist if gcd(val, mod()) != 1
        return ModInt(x);
    }

    ModInt &operator+=(const ModInt &o) { if ((val += o.val) >= mod()) val -= mod(); return *this; }
    ModInt &operator-=(const ModInt &o) { if ((val -= o.val) < 0) val += mod(); return *this; }
    ModInt &operator*=(const ModInt &o) { val = mul(val, o.val); return *this; }
    ModInt &operator/=(const ModInt &o) { return *this *= o.inv(); }
    ModInt operator-() const { return ModInt() - *this; }
    ModInt &operator++() { return *this += 1; }
    ModInt &operator--() { return *this -= 1; }
    ModInt operator++(int) { ModInt t = *this; ++*this; return t; }
    ModInt operator--(int) { ModInt t = *this; --*this; return t; }

    friend ModInt operator+(ModInt a, const ModInt &b) { return a += b; }
    friend ModInt operator-(ModInt a, const ModInt &b) { return a -= b; }
    friend ModInt operator*(ModInt a, const ModInt &b) { return a *= b; }
    friend ModInt operator/(ModInt a, const ModInt &b) { return a /= b; }
    friend bool operator==(const ModInt &a, const ModInt &b) { return a.val == b.val; }
    friend bool operator!=(const ModInt &a, const ModInt &b) { return a.val != b.val; }
    friend ostream &operator<<(ostream &os, const ModInt &m) { return os << m.val; }
    friend istream &operator>>(istream &is, ModInt &m) { ll x; is >> x; m = ModInt(x); return is; }
};

// map x -> first * x + second; query(l, r) is "apply f_l, then f_{l+1}, ..., then f_{r-1}"
template <class V>
struct AffineComp {
    using T = pair<V, V>;
    static T id() { return {1, 0}; }
    static T op(const T &f, const T &g) { return {f.first * g.first, g.first * f.second + g.second}; }
    static V eval(const T &f, const V &x) { return f.first * x + f.second; }
};

// link-cut tree for path folds of any monoid M (like the ones in monoids.cpp; op need not commute), 0-indexed
// each splay node keeps the fold of its subtree in path order and reversed, so re-rooting just swaps the two
//   LinkCutPath(a)   isolated vertices with values a, O(n)
//   link(u, v)       add the edge u - v; u and v must not be connected, O(log n) amortized
//   cut(u, v)        remove the edge u - v, which must exist, O(log n) amortized
//   set(v, x)        set the value of v, O(log n) amortized
//   fold(u, v)       op of the values on the path from u to v, in that order; u and v connected, O(log n) amortized
template <class M>
struct LinkCutPath {
    using T = typename M::T;
    struct Node {
        int ch[2] = {0, 0}, p = 0;
        bool rev = false;
        T val, sum, rsum;
    };
    vector<Node> t;  // internal vertices are 1..n and 0 is null

    LinkCutPath(const vector<T> &a): t(a.size() + 1) {
        t[0].val = t[0].sum = t[0].rsum = M::id();
        for (size_t i = 0; i < a.size(); i++) t[i + 1].val = t[i + 1].sum = t[i + 1].rsum = a[i];
    }

    bool is_root(int x) const {
        int p = t[x].p;
        return !p || (t[p].ch[0] != x && t[p].ch[1] != x);
    }

    void pull(int x) {
        int l = t[x].ch[0], r = t[x].ch[1];
        t[x].sum = M::op(M::op(t[l].sum, t[x].val), t[r].sum);
        t[x].rsum = M::op(M::op(t[r].rsum, t[x].val), t[l].rsum);
    }

    void flip(int x) {
        if (!x) return;
        swap(t[x].ch[0], t[x].ch[1]);
        swap(t[x].sum, t[x].rsum);
        t[x].rev = !t[x].rev;
    }

    void push(int x) {
        if (!t[x].rev) return;
        flip(t[x].ch[0]);
        flip(t[x].ch[1]);
        t[x].rev = false;
    }

    void rotate(int x) {
        int p = t[x].p, g = t[p].p, d = t[p].ch[1] == x, c = t[x].ch[!d];
        if (!is_root(p)) t[g].ch[t[g].ch[1] == p] = x;
        t[x].p = g;
        t[p].ch[d] = c;
        if (c) t[c].p = p;
        t[x].ch[!d] = p;
        t[p].p = x;
        pull(p);
        pull(x);
    }

    void splay(int x) {
        vector<int> path{x};
        for (int y = x; !is_root(y); y = t[y].p) path.push_back(t[y].p);
        for (int i = (int)path.size() - 1; i >= 0; i--) push(path[i]);
        while (!is_root(x)) {
            int p = t[x].p, g = t[p].p;
            if (!is_root(p)) rotate((t[p].ch[1] == x) == (t[g].ch[1] == p) ? p : x);
            rotate(x);
        }
    }

    void access(int x) {
        for (int y = x, last = 0; y; last = y, y = t[y].p) {
            splay(y);
            t[y].ch[1] = last;
            pull(y);
        }
        splay(x);
    }

    void make_root(int x) {
        access(x);
        flip(x);
    }

    void link(int u, int v) {
        make_root(u + 1);
        t[u + 1].p = v + 1;
    }

    void cut(int u, int v) {
        make_root(u + 1);
        access(v + 1);
        t[v + 1].ch[0] = t[u + 1].p = 0;
        pull(v + 1);
    }

    void set(int v, const T &x) {
        access(v + 1);
        t[v + 1].val = x;
        pull(v + 1);
    }

    T fold(int u, int v) {
        make_root(u + 1);
        access(v + 1);
        return t[v + 1].sum;
    }
};

using mint = ModInt<998'244'353>;
using F = AffineComp<mint>;

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<F::T> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
    LinkCutPath<F> lct(a);
    for (ll i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        lct.link(u, v);
    }
    for (ll i = 0; i < q; i++) {
        ll t;
        cin >> t;
        if (t == 0) {
            int u, v, w, x;
            cin >> u >> v >> w >> x;
            lct.cut(u, v);
            lct.link(w, x);
        }
        else if (t == 1) {
            int p;
            mint c, d;
            cin >> p >> c >> d;
            lct.set(p, {c, d});
        }
        else {
            int u, v;
            mint x;
            cin >> u >> v >> x;
            cout << F::eval(lct.fold(u, v), x) << "\n";
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
