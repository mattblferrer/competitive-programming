// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 998'244'353;
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

// DSU with potentials: keeps value(u) - value(v) for u, v in the same set, under constraints value(u) - value(v) = x
// T is any additive group (+, -, == and T() as zero): ll, ModInt, ...; union by size keeps find's recursion shallow
//   PotentialDSU(n)    n singleton sets, O(n)
//   find(v)            root of v's set, O(log n)
//   connected(u, v)    true if u and v are in the same set, O(log n)
//   diff(u, v)         value(u) - value(v); u and v must be connected, O(log n)
//   merge(u, v, x)     add the constraint value(u) - value(v) = x; false if it contradicts the others, O(log n)
template <class T>
struct PotentialDSU {
    vector<int> p, sz;
    vector<T> pot;  // pot[v] = value(v) - value(p[v])

    PotentialDSU(int n = 0): p(n), sz(n, 1), pot(n) { iota(p.begin(), p.end(), 0); }

    int find(int v) {
        if (p[v] == v) return v;
        int r = find(p[v]);
        pot[v] = pot[v] + pot[p[v]];
        p[v] = r;
        return r;
    }

    bool connected(int u, int v) { return find(u) == find(v); }

    T diff(int u, int v) {
        find(u);
        find(v);
        return pot[u] - pot[v];
    }

    bool merge(int u, int v, T x) {
        int ru = find(u), rv = find(v);
        if (ru == rv) return pot[u] - pot[v] == x;
        if (sz[ru] < sz[rv]) {
            p[ru] = rv;
            pot[ru] = x - pot[u] + pot[v];
            sz[rv] += sz[ru];
        } else {
            p[rv] = ru;
            pot[rv] = pot[u] - pot[v] - x;
            sz[ru] += sz[rv];
        }
        return true;
    }
};

using mint = ModInt<998'244'353>;

void solve() {
    ll n, q;
    cin >> n >> q;
    PotentialDSU<mint> ds(n);
    for (ll i = 0; i < q; i++) {
        ll t;
        cin >> t;
        if (t == 0) {
            ll u, v, x;
            cin >> u >> v >> x;
            cout << ds.merge(u, v, x) << "\n";
        }
        else if (t == 1) {
            ll u, v;
            cin >> u >> v;
            if (ds.connected(u, v)) cout << ds.diff(u, v) << "\n";
            else cout << -1 << "\n";
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
