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

// arbitrary-precision signed hex integer in base 2^28 limbs (7 hex digits each)
// n, m below = number of limbs; M(n) = cost of an n-limb multiply = O(n log n)
// verified on yosupo: addition / multiplication / division_of_hex_big_integers (|x| up to 16^1600000)
//   HexBigInt()                 construct as 0, from ll O(1), or from a hex string O(len)
//   trim()                      remove leading zero limbs and make 0 non-negative, O(n)
//   read(s)                     parse a hex string with optional sign, case-insensitive, O(len)
//   x = v                       assign from ll, O(1)
//   cin >> x                    read a hex number from a stream, O(len)
//   cout << x                   write in uppercase hex to a stream, O(n)
//   to_string()                 uppercase hex string, O(n)
//   size()                      number of hex digits (0 for zero), O(1)
//   x[idx]                      idx-th most significant hex digit, O(1)
//   abs_less(x, y)              |x| < |y|, O(n)
//   <, >, <=, >=, ==, !=        comparisons, O(n)
//   -x                          negation, O(n)
//   abs_val()                   absolute value, O(n)
//   shift(k)                    x * BASE^k, or x / BASE^-k truncated toward 0 if k < 0, O(n + k)
//   add_vec(x, y)               |x| + |y| on limb vectors, O(max(n, m))
//   sub_vec(x, y)               |x| - |y| on limb vectors, requires |x| >= |y|, O(n)
//   +, -, +=, -=                signed addition and subtraction, O(max(n, m))
//   mul_simple(x, y)            schoolbook product of limb vectors, O(n * m)
//   binexp(base, e, mod)        base^e mod mod, O(log e)
//   ntt<MOD>(f)                 in-place NTT mod MOD (primitive root 3); f.size() must be a power of 2
//   convolve_mod<MOD>(x, y)     convolution of limb vectors mod MOD, O((n + m) log(n + m))
//   mul_ntt(x, y)               exact product of limb vectors: 3-prime NTT + CRT, O((n + m) log(n + m))
//   mul_vec(x, y)               product of limb vectors: schoolbook if min(n, m) <= 60, else NTT
//   *, *=                       signed multiplication, O(M(n + m))
//   x *= v, x * v (ll v)        multiply by a ll (|v| < 2^35), O(n)
//   div_small(x, b)             divide limbs by ll b, returns {quotient, remainder}, O(n)
//   x /= v, x / v (ll v)        divide by a ll (truncates toward 0), O(n)
//   divmod_simple(x, y, q, r)   Knuth algorithm D on limb vectors: x = q*y + r, 0 <= r < y, O(m * (n - m + 1))
//   inverse(d)                  floor(BASE^(2p) / d) for d > 0 with p limbs, Newton iteration, O(M(p))
//   divmod_newton(x, y, q, r)   x = q*y + r, 0 <= r < y for x >= y > 0, O(M(n))
//   divmod(a1, b1, q, r)        q = a1 / b1 (truncated), r = a1 % b1 (sign of a1); b1 != 0
//                               uses Knuth D if min(m, n - m + 1) <= 64, else Newton
//   /, %, /=, %=                division and modulo by a HexBigInt (truncated, like C++ ints)
//   is_zero(), bool(x)          zero checks, O(1)
struct HexBigInt {
    using u64 = unsigned long long;
    using u128 = unsigned __int128;
    static const int BASE = 1 << 28;
    static const int BASE_DIGITS = 7;
    vector<int> a;  // little-endian limbs; zero is stored as empty a
    int sign;       // 1 or -1 (zero has sign 1)

    HexBigInt(): sign(1) {}
    HexBigInt(ll v) { *this = v; }
    HexBigInt(const string &s) { read(s); }
    HexBigInt(const char *s) { read(s); }

    void trim() {
        while (!a.empty() && a.back() == 0) a.pop_back();
        if (a.empty()) sign = 1;
    }

    void read(const string &s) {
        sign = 1;
        a.clear();
        int pos = 0;
        while (pos < (int)s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-') sign = -sign;
            pos++;
        }
        a.reserve(((int)s.size() - pos) / BASE_DIGITS + 1);
        for (int i = (int)s.size() - 1; i >= pos; i -= BASE_DIGITS) {
            int x = 0;
            for (int j = max(pos, i - BASE_DIGITS + 1); j <= i; j++) {
                char c = (char)toupper(s[j]);
                x = x * 16 + (isdigit(c) ? c - '0' : c - 'A' + 10);
            }
            a.push_back(x);
        }
        trim();
    }

    HexBigInt &operator=(ll v) {
        sign = 1;
        if (v < 0) { sign = -1; v = -v; }
        a.clear();
        for (; v > 0; v /= BASE) a.push_back((int)(v % BASE));
        return *this;
    }

    string to_string() const {
        if (a.empty()) return "0";
        string s = sign == -1 ? "-" : "";
        for (int j = (31 - __builtin_clz(a.back())) / 4; j >= 0; j--)  // top limb, no leading zeros
            s += "0123456789ABCDEF"[a.back() >> (4 * j) & 15];
        size_t at = s.size();
        s.resize(at + (a.size() - 1) * BASE_DIGITS);
        for (int i = (int)a.size() - 2; i >= 0; i--, at += BASE_DIGITS) {
            int x = a[i];
            for (int j = BASE_DIGITS - 1; j >= 0; j--, x >>= 4) s[at + j] = "0123456789ABCDEF"[x & 15];
        }
        return s;
    }

    friend istream &operator>>(istream &in, HexBigInt &v) {
        string s;
        in >> s;
        v.read(s);
        return in;
    }
    friend ostream &operator<<(ostream &out, const HexBigInt &v) { return out << v.to_string(); }

    static bool abs_less(const HexBigInt &x, const HexBigInt &y) {
        if (x.a.size() != y.a.size()) return x.a.size() < y.a.size();
        for (int i = (int)x.a.size() - 1; i >= 0; --i)
            if (x.a[i] != y.a[i]) return x.a[i] < y.a[i];
        return false;
    }

    bool operator<(const HexBigInt &v) const {
        if (sign != v.sign) return sign < v.sign;
        return sign == 1 ? abs_less(*this, v) : abs_less(v, *this);
    }
    bool operator>(const HexBigInt &v) const { return v < *this; }
    bool operator<=(const HexBigInt &v) const { return !(v < *this); }
    bool operator>=(const HexBigInt &v) const { return !(*this < v); }
    bool operator==(const HexBigInt &v) const { return sign == v.sign && a == v.a; }
    bool operator!=(const HexBigInt &v) const { return !(*this == v); }

    HexBigInt operator-() const {
        HexBigInt res = *this;
        if (!res.a.empty()) res.sign = -sign;
        return res;
    }

    HexBigInt abs_val() const {
        HexBigInt res = *this;
        res.sign = 1;
        return res;
    }

    HexBigInt shift(int k) const {
        HexBigInt res;
        if (a.empty()) return res;
        res.sign = sign;
        if (k >= 0) {
            res.a.assign(k, 0);
            res.a.insert(res.a.end(), a.begin(), a.end());
        }
        else if (-k < (int)a.size()) res.a.assign(a.begin() - k, a.end());
        res.trim();
        return res;
    }

    static vector<int> add_vec(const vector<int> &x, const vector<int> &y) {
        if (x.size() < y.size()) return add_vec(y, x);
        vector<int> res(x.size() + 1);
        int carry = 0;
        for (size_t i = 0; i < x.size(); i++) {
            int cur = x[i] + carry + (i < y.size() ? y[i] : 0);
            carry = cur >= BASE;
            res[i] = carry ? cur - BASE : cur;
        }
        res.back() = carry;
        if (!carry) res.pop_back();
        return res;
    }

    static vector<int> sub_vec(const vector<int> &x, const vector<int> &y) {
        vector<int> res = x;
        int borrow = 0;
        for (size_t i = 0; i < y.size() || borrow; ++i) {
            res[i] -= borrow + (i < y.size() ? y[i] : 0);
            borrow = res[i] < 0;
            if (borrow) res[i] += BASE;
        }
        while (!res.empty() && res.back() == 0) res.pop_back();
        return res;
    }

    HexBigInt operator+(const HexBigInt &v) const {
        HexBigInt res;
        if (sign == v.sign) {
            res.sign = sign;
            res.a = add_vec(a, v.a);
        }
        else if (abs_less(*this, v)) {
            res.sign = v.sign;
            res.a = sub_vec(v.a, a);
        }
        else {
            res.sign = sign;
            res.a = sub_vec(a, v.a);
        }
        res.trim();
        return res;
    }
    HexBigInt operator-(const HexBigInt &v) const { return *this + (-v); }
    HexBigInt &operator+=(const HexBigInt &v) { return *this = *this + v; }
    HexBigInt &operator-=(const HexBigInt &v) { return *this = *this - v; }

    // ---- multiplication ----
    static vector<int> mul_simple(const vector<int> &x, const vector<int> &y) {
        if (x.empty() || y.empty()) return {};
        if (x.size() > y.size()) return mul_simple(y, x);
        vector<int> res(x.size() + y.size());
        for (size_t i = 0; i < x.size(); i++) {
            u64 carry = 0, xi = x[i];
            for (size_t j = 0; j < y.size(); j++) {
                u64 cur = res[i + j] + xi * y[j] + carry;
                res[i + j] = (int)(cur % BASE);
                carry = cur / BASE;
            }
            res[i + y.size()] = (int)carry;
        }
        while (!res.empty() && res.back() == 0) res.pop_back();
        return res;
    }

    static ll binexp(ll base, ll e, ll mod) {
        base %= mod;
        if (base < 0) base += mod;
        ll res = 1;
        for (; e > 0; e >>= 1, base = base * base % mod)
            if (e & 1) res = res * base % mod;
        return res;
    }

    template <int MOD>
    static void ntt(vector<ll> &f) {
        int n = (int)f.size(), L = __builtin_ctz(n);
        static vector<ll> rt(2, 1);
        for (static int k = 2, s = 2; k < n; k *= 2, s++) {
            rt.resize(n);
            ll z[] = {1, binexp(3, MOD >> s, MOD)};
            for (int i = k; i < 2 * k; i++) rt[i] = rt[i / 2] * z[i & 1] % MOD;
        }
        vector<int> rev(n);
        for (int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
        for (int i = 0; i < n; i++) if (i < rev[i]) swap(f[i], f[rev[i]]);
        for (int k = 1; k < n; k *= 2)
            for (int i = 0; i < n; i += 2 * k)
                for (int j = 0; j < k; j++) {
                    ll z = rt[j + k] * f[i + j + k] % MOD, &fi = f[i + j];
                    f[i + j + k] = fi - z + (z > fi ? MOD : 0);
                    fi += (fi + z >= MOD ? z - MOD : z);
                }
    }

    template <int MOD>
    static vector<ll> convolve_mod(const vector<int> &x, const vector<int> &y) {
        int s = (int)(x.size() + y.size()) - 1, n = 1;
        while (n < s) n <<= 1;
        vector<ll> f(n), g(n), out(n);
        for (size_t i = 0; i < x.size(); i++) f[i] = x[i] % MOD;
        for (size_t i = 0; i < y.size(); i++) g[i] = y[i] % MOD;
        ntt<MOD>(f);
        ntt<MOD>(g);
        ll inv = binexp(n, MOD - 2, MOD);
        for (int i = 0; i < n; i++) out[-i & (n - 1)] = f[i] * g[i] % MOD * inv % MOD;
        ntt<MOD>(out);
        out.resize(s);
        return out;
    }

    // coefficients are < min(n, m) * BASE^2 < M1 * M2 * M3 (~7.9e25) for up to ~7e7 limbs
    static vector<int> mul_ntt(const vector<int> &x, const vector<int> &y) {
        const int M1 = 998244353, M2 = 167772161, M3 = 469762049;
        vector<ll> c1 = convolve_mod<M1>(x, y), c2 = convolve_mod<M2>(x, y), c3 = convolve_mod<M3>(x, y);
        const ll inv1 = binexp(M1, M2 - 2, M2), inv12 = binexp((ll)M1 * M2 % M3, M3 - 2, M3);
        vector<int> res(c1.size());
        u128 carry = 0;
        for (size_t i = 0; i < c1.size(); i++) {
            ll t2 = (c2[i] - c1[i] % M2 + M2) % M2 * inv1 % M2;
            ll x12 = c1[i] + (ll)M1 * t2;  // CRT mod M1 * M2
            ll t3 = ((c3[i] - x12 % M3) % M3 + M3) % M3 * inv12 % M3;
            u128 cur = carry + (u128)x12 + (u128)((ll)M1 * M2) * t3;
            res[i] = (int)(cur % BASE);
            carry = cur / BASE;
        }
        for (; carry > 0; carry /= BASE) res.push_back((int)(carry % BASE));
        while (!res.empty() && res.back() == 0) res.pop_back();
        return res;
    }

    static vector<int> mul_vec(const vector<int> &x, const vector<int> &y) {
        if (min(x.size(), y.size()) <= 60) return mul_simple(x, y);
        return mul_ntt(x, y);
    }

    HexBigInt operator*(const HexBigInt &v) const {
        HexBigInt res;
        res.a = mul_vec(a, v.a);
        res.sign = sign * v.sign;
        res.trim();
        return res;
    }
    HexBigInt &operator*=(const HexBigInt &v) { return *this = *this * v; }

    // ---- small-int (ll) helpers ----
    HexBigInt &operator*=(ll v) {
        if (v < 0) { sign = -sign; v = -v; }
        ll carry = 0;
        for (size_t i = 0; i < a.size() || carry; ++i) {
            if (i == a.size()) a.push_back(0);
            ll cur = a[i] * v + carry;
            a[i] = (int)(cur % BASE);
            carry = cur / BASE;
        }
        trim();
        return *this;
    }
    HexBigInt operator*(ll v) const { HexBigInt res = *this; res *= v; return res; }

    static pair<vector<int>, ll> div_small(const vector<int> &x, ll b) {
        vector<int> res(x.size());
        ll rem = 0;
        for (int i = (int)x.size() - 1; i >= 0; --i) {
            ll cur = x[i] + rem * BASE;
            res[i] = (int)(cur / b);
            rem = cur % b;
        }
        while (!res.empty() && res.back() == 0) res.pop_back();
        return {res, rem};
    }
    HexBigInt &operator/=(ll v) {
        if (v < 0) { sign = -sign; v = -v; }
        a = div_small(a, v).first;
        trim();
        return *this;
    }
    HexBigInt operator/(ll v) const { HexBigInt res = *this; res /= v; return res; }

    // ---- full bigint / bigint division & modulo ----
    static void divmod_simple(const vector<int> &x, const vector<int> &y, vector<int> &q, vector<int> &r) {
        int n = (int)x.size(), m = (int)y.size();
        if (n < m) { q.clear(); r = x; return; }
        if (m == 1) {
            ll rem;
            tie(q, rem) = div_small(x, y[0]);
            r.clear();
            if (rem) r.push_back((int)rem);
            return;
        }
        // normalize so the top limb of v is >= BASE / 2; then qhat is off by at most 2
        ll norm = BASE / (y.back() + 1), carry = 0;
        vector<ll> u(n + 1), v(m);
        for (int i = 0; i < n; i++) { ll cur = x[i] * norm + carry; u[i] = cur % BASE; carry = cur / BASE; }
        u[n] = carry;
        carry = 0;
        for (int i = 0; i < m; i++) { ll cur = y[i] * norm + carry; v[i] = cur % BASE; carry = cur / BASE; }
        q.assign(n - m + 1, 0);
        for (int j = n - m; j >= 0; j--) {
            ll num = u[j + m] * BASE + u[j + m - 1];
            ll qhat = num / v[m - 1], rhat = num % v[m - 1];
            while (qhat >= BASE || qhat * v[m - 2] > rhat * BASE + u[j + m - 2]) {
                qhat--;
                rhat += v[m - 1];
                if (rhat >= BASE) break;
            }
            ll borrow = 0;
            carry = 0;
            for (int i = 0; i < m; i++) {
                ll p = qhat * v[i] + carry;
                carry = p / BASE;
                ll t = u[i + j] - p % BASE - borrow;
                borrow = t < 0;
                u[i + j] = borrow ? t + BASE : t;
            }
            ll t = u[j + m] - carry - borrow;
            if (t < 0) {  // qhat was one too large: add v back
                qhat--;
                carry = 0;
                for (int i = 0; i < m; i++) {
                    ll s = u[i + j] + v[i] + carry;
                    carry = s >= BASE;
                    u[i + j] = carry ? s - BASE : s;
                }
                t += carry;
            }
            u[j + m] = t;
            q[j] = (int)qhat;
        }
        while (!q.empty() && q.back() == 0) q.pop_back();
        r = div_small(vector<int>(u.begin(), u.begin() + m), norm).first;
    }

    static HexBigInt inverse(const HexBigInt &d) {
        int p = (int)d.a.size();
        if (p <= 32) {
            vector<int> num(2 * p + 1, 0);
            num.back() = 1;
            HexBigInt q, r;
            divmod_simple(num, d.a, q.a, r.a);
            return q;
        }
        // y = floor(BASE^(2h) / top h limbs of d) ~ BASE^(p+h) / d, then one Newton step
        int h = p / 2 + 3;
        HexBigInt y = inverse(d.shift(h - p));
        HexBigInt e = HexBigInt(1).shift(p + h) - d * y;
        HexBigInt x = y.shift(p - h) + (y * e).shift(-2 * h);
        HexBigInt r = HexBigInt(1).shift(2 * p) - d * x;  // fix the last few units exactly
        while (r.sign < 0) { x -= 1; r += d; }
        while (r >= d) { x += 1; r -= d; }
        return x;
    }

    static void divmod_newton(const HexBigInt &x, const HexBigInt &y, HexBigInt &q, HexBigInt &r) {
        int n = (int)x.a.size(), m = (int)y.a.size(), p = n - m + 2;
        HexBigInt inv = inverse(y.shift(p - m));  // ~ BASE^(p+m) / y with p limbs of precision
        q = (x * inv).shift(-(p + m));
        r = x - q * y;
        while (r.sign < 0) { q -= 1; r += y; }
        while (r >= y) { q += 1; r -= y; }
    }

    static void divmod(const HexBigInt &a1, const HexBigInt &b1, HexBigInt &q, HexBigInt &r) {
        HexBigInt x = a1.abs_val(), y = b1.abs_val();
        if (abs_less(x, y)) { q = HexBigInt(); r = a1; return; }
        int n = (int)x.a.size(), m = (int)y.a.size();
        if (min(m, n - m + 1) <= 64) divmod_simple(x.a, y.a, q.a, r.a);
        else divmod_newton(x, y, q, r);
        q.sign = a1.sign * b1.sign;
        r.sign = a1.sign;
        q.trim();
        r.trim();
    }

    HexBigInt operator/(const HexBigInt &v) const { HexBigInt q, r; divmod(*this, v, q, r); return q; }
    HexBigInt operator%(const HexBigInt &v) const { HexBigInt q, r; divmod(*this, v, q, r); return r; }
    HexBigInt &operator/=(const HexBigInt &v) { return *this = *this / v; }
    HexBigInt &operator%=(const HexBigInt &v) { return *this = *this % v; }

    int size() const {
        if (a.empty()) return 0;
        return ((int)a.size() - 1) * BASE_DIGITS + (31 - __builtin_clz(a.back())) / 4 + 1;
    }
    int operator[](int idx) const {
        int pos = size() - 1 - idx;
        return a[pos / BASE_DIGITS] >> (pos % BASE_DIGITS * 4) & 15;
    }

    bool is_zero() const { return a.empty(); }
    explicit operator bool() const { return !is_zero(); }
};

void solve() {
    HexBigInt a, b;
    cin >> a >> b;
    HexBigInt q, r;
    HexBigInt::divmod(a, b, q, r);
    cout << q << " " << r << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;  // comment out for single test
    while (t--) solve();
}
