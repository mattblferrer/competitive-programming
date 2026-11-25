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

// map x -> first * x + second; query(l, r) is "apply f_l, then f_{l+1}, ..., then f_{r-1}"
template <class V>
struct AffineComp {
    using T = pair<V, V>;
    static T id() { return {1, 0}; }
    static T op(const T &f, const T &g) { return {f.first * g.first, g.first * f.second + g.second}; }
    static V eval(const T &f, const V &x) { return f.first * x + f.second; }
};

// deque with the fold of a monoid M (like the ones in monoids.cpp) over all its elements, front to back
// two stacks, each keeping the fold of everything below; an empty side takes half of the other
// as a queue (push_back, pop_front) it is the classic two-stack queue
//   push_front(x), push_back(x)   add x at that end, O(1)
//   pop_front(), pop_back()       remove from that end; the deque must not be empty, O(1) amortized
//   fold()                        op over all elements from front to back, M::id() if empty, O(1)
//   size()                        number of elements, O(1)
template <class M>
struct FoldDeque {
    using T = typename M::T;
    vector<T> fv, fa, bv, ba;  // front stack (top = front) and back stack (top = back): values and folds

    void push_front(const T &x) {
        fv.push_back(x);
        fa.push_back(M::op(x, fa.empty() ? M::id() : fa.back()));
    }

    void push_back(const T &x) {
        bv.push_back(x);
        ba.push_back(M::op(ba.empty() ? M::id() : ba.back(), x));
    }

    void rebuild(bool front) {  // split all elements in half between the two stacks
        vector<T> all(fv.rbegin(), fv.rend());
        all.insert(all.end(), bv.begin(), bv.end());
        fv.clear(), fa.clear(), bv.clear(), ba.clear();
        int k = all.size(), m = front ? (k + 1) / 2 : k / 2;  // the side being popped gets at least one
        for (int i = m - 1; i >= 0; i--) push_front(all[i]);
        for (int i = m; i < k; i++) push_back(all[i]);
    }

    void pop_front() {
        if (fv.empty()) rebuild(true);
        fv.pop_back(), fa.pop_back();
    }

    void pop_back() {
        if (bv.empty()) rebuild(false);
        bv.pop_back(), ba.pop_back();
    }

    T fold() const { return M::op(fa.empty() ? M::id() : fa.back(), ba.empty() ? M::id() : ba.back()); }

    int size() const { return fv.size() + bv.size(); }
};

using mint = ModInt<998'244'353>;
using F = AffineComp<mint>;

void solve() {
    ll q;
    cin >> q;
    FoldDeque<F> dq;
    for (ll i = 0; i < q; i++) {
        ll t;
        cin >> t;
        if (t == 0 || t == 1) {
            mint a, b;
            cin >> a >> b;
            if (t == 0) dq.push_front({a, b});
            else dq.push_back({a, b});
        }
        else if (t == 2) {
            dq.pop_front();
        }
        else if (t == 3) {
            dq.pop_back();
        }
        else if (t == 4) {
            mint x;
            cin >> x;
            cout << F::eval(dq.fold(), x) << "\n";
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
