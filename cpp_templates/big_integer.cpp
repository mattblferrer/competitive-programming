#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// arbitrary-precision signed integer in base 1e9 limbs
// n, m below = number of limbs (~9 decimal digits each)
//   BigInt()                    construct as 0, from ll O(1), or from a decimal string O(len)
//   trim()                      remove leading zero limbs and make 0 non-negative, O(n)
//   read(s)                     parse a decimal string with optional sign, O(len)
//   x = v                       assign from ll, O(1)
//   cin >> x                    read a decimal number from a stream, O(len)
//   cout << x                   write in decimal to a stream, O(n)
//   abs_less(x, y)              |x| < |y|, O(n)
//   <, >, <=, >=, ==, !=        comparisons, O(n)
//   -x                          negation, O(n)
//   abs_val()                   absolute value, O(n)
//   add_vec(x, y)               |x| + |y| on limb vectors, O(max(n, m))
//   sub_vec(x, y)               |x| - |y| on limb vectors, requires |x| >= |y|, O(n)
//   +, -, +=, -=                signed addition and subtraction, O(max(n, m))
//   mul_simple(v)               schoolbook multiplication, O(n * m); used when n * m is small
//   binexp(base, e, mod)        base^e mod mod, O(log e)
//   ntt(f, invert, mod, root)   in-place NTT (inverse NTT if invert); f.size() must be a power of 2, O(L log L)
//   convolve_mod(da, db)        convolution of da and db modulo one NTT prime, O((n + m) log(n + m))
//                               result[i] is only meaningful mod `mod`, not the exact coefficient (see mul_ntt)
//   to_fft_base()               split base-1e9 limbs into base-1000 digits for the NTT, O(n)
//   mul_ntt(v)                  NTT multiplication with two primes + CRT, O((n + m) log(n + m))
//   *, *=                       multiplication: schoolbook if n * m <= 4000, otherwise NTT
//   x *= v, x * v (ll v)        multiply by a ll (|v| < ~9e9), O(n)
//   div_small(x, b)             divide limbs by ll b, returns {quotient, remainder}, O(n)
//   x /= v, x / v (ll v)        divide by a ll (truncates toward 0), O(n)
//   divmod(a1, b1, q, r)        q = a1 / b1 (truncated), r = a1 % b1 (sign of a1); b1 != 0, O(n * m)
//   /, %, /=, %=                division and modulo by a BigInt, O(n * m)
//   is_zero(), bool(x)          zero checks, O(1)
//   to_string()                 decimal string, O(n)
struct BigInt {
    static const int BASE = 1000000000;
    static const int BASE_DIGITS = 9;
    vector<int> a;   // little-endian, base 1e9 digits
    int sign;        // 1 or -1 (0 is stored as sign=1, empty a)

    BigInt(): sign(1) {}
    BigInt(ll v) { *this = v; }
    BigInt(const string &s) { read(s); }

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
        for (int i = (int)s.size() - 1; i >= pos; i -= BASE_DIGITS) {
            int x = 0;
            int start = max(pos, i - BASE_DIGITS + 1);
            for (int j = start; j <= i; j++) x = x * 10 + (s[j] - '0');
            a.push_back(x);
        }
        trim();
    }

    BigInt &operator=(ll v) {
        sign = 1;
        if (v < 0) { sign = -1; v = -v; }
        a.clear();
        for (; v > 0; v /= BASE) a.push_back((int)(v % BASE));
        return *this;
    }

    friend istream &operator>>(istream &in, BigInt &v) {
        string s;
        in >> s;
        v.read(s);
        return in;
    }

    friend ostream &operator<<(ostream &out, const BigInt &v) {
        if (v.sign == -1 && !v.a.empty()) out << '-';
        out << (v.a.empty() ? 0 : v.a.back());
        char fill = out.fill('0');  // setfill is sticky, so restore it afterwards
        for (int i = (int)v.a.size() - 2; i >= 0; --i)
            out << setw(BASE_DIGITS) << v.a[i];
        out.fill(fill);
        return out;
    }

    static bool abs_less(const BigInt &x, const BigInt &y) {
        if (x.a.size() != y.a.size()) return x.a.size() < y.a.size();
        for (int i = (int)x.a.size() - 1; i >= 0; --i)
            if (x.a[i] != y.a[i]) return x.a[i] < y.a[i];
        return false;
    }

    bool operator<(const BigInt &v) const {
        if (sign != v.sign) return sign < v.sign;
        return sign == 1 ? abs_less(*this, v) : abs_less(v, *this);
    }
    bool operator>(const BigInt &v) const { return v < *this; }
    bool operator<=(const BigInt &v) const { return !(v < *this); }
    bool operator>=(const BigInt &v) const { return !(*this < v); }
    bool operator==(const BigInt &v) const { return sign == v.sign && a == v.a; }
    bool operator!=(const BigInt &v) const { return !(*this == v); }

    BigInt operator-() const {
        BigInt res = *this;
        if (!res.a.empty()) res.sign = -sign;
        return res;
    }

    BigInt abs_val() const {
        BigInt res = *this;
        res.sign = 1;
        return res;
    }

    static vector<int> add_vec(const vector<int> &x, const vector<int> &y) {
        vector<int> res;
        int carry = 0;
        for (size_t i = 0; i < max(x.size(), y.size()) || carry; ++i) {
            int cur = carry + (i < x.size() ? x[i] : 0) + (i < y.size() ? y[i] : 0);
            res.push_back(cur % BASE);
            carry = cur / BASE;
        }
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

    BigInt operator+(const BigInt &v) const {
        BigInt res;
        if (sign == v.sign) {
            res.sign = sign;
            res.a = add_vec(a, v.a);
        }
        else if (abs_less(*this, v)) {
            res.sign = v.sign;
            res.a = sub_vec(v.a, a);
            res.trim();
        }
        else {
            res.sign = sign;
            res.a = sub_vec(a, v.a);
            res.trim();
        }
        return res;
    }
    BigInt operator-(const BigInt &v) const { return *this + (-v); }
    BigInt &operator+=(const BigInt &v) { return *this = *this + v; }
    BigInt &operator-=(const BigInt &v) { return *this = *this - v; }

    BigInt mul_simple(const BigInt &v) const {
        vector<__int128> tmp(a.size() + v.a.size());
        for (size_t i = 0; i < a.size(); i++)
            for (size_t j = 0; j < v.a.size(); j++)
                tmp[i + j] += (__int128)a[i] * v.a[j];
        BigInt res;
        res.sign = a.empty() || v.a.empty() ? 1 : sign * v.sign;
        res.a.resize(tmp.size());
        __int128 carry = 0;
        for (size_t i = 0; i < tmp.size(); i++) {
            __int128 cur = tmp[i] + carry;
            res.a[i] = (int)(cur % BASE);
            carry = cur / BASE;
        }
        while (carry) { res.a.push_back((int)(carry % BASE)); carry /= BASE; }
        res.trim();
        return res;
    }

    // ---- NTT (Number Theoretic Transform) multiplication ----
    static const int FFT_BASE = 1000;
    static const int FFT_BASE_DIGITS = 3; // BASE_DIGITS / FFT_BASE_DIGITS == 3

    static const ll NTT_MOD1 = 998244353, NTT_ROOT1 = 3;
    static const ll NTT_MOD2 = 469762049, NTT_ROOT2 = 3;

    static ll binexp(ll base, ll e, ll mod) {
        base %= mod;
        if (base < 0) base += mod;
        ll res = 1;
        while (e > 0) {
            if (e & 1) res = (ll)((__int128)res * base % mod);
            base = (ll)((__int128)base * base % mod);
            e >>= 1;
        }
        return res;
    }

    static void ntt(vector<ll> &f, bool invert, ll mod, ll root) {
        int n = (int)f.size();
        if (n == 1) return;

        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) swap(f[i], f[j]);
        }

        for (int len = 2; len <= n; len <<= 1) {
            ll w = invert
                ? binexp(root, mod - 1 - (mod - 1) / len, mod)
                : binexp(root, (mod - 1) / len, mod);
            for (int i = 0; i < n; i += len) {
                ll wn = 1;
                for (int j = 0; j < len / 2; j++) {
                    ll u = f[i + j];
                    ll v = (ll)((__int128)f[i + j + len / 2] * wn % mod);
                    f[i + j] = u + v >= mod ? u + v - mod : u + v;
                    f[i + j + len / 2] = u - v < 0 ? u - v + mod : u - v;
                    wn = (ll)((__int128)wn * w % mod);
                }
            }
        }
        if (invert) {
            ll n_inv = binexp(n, mod - 2, mod);
            for (ll &x : f) x = (ll)((__int128)x * n_inv % mod);
        }
    }

    static vector<ll> convolve_mod(const vector<int> &da, const vector<int> &db,
        ll mod, ll root) {
        vector<ll> fa(da.begin(), da.end()), fb(db.begin(), db.end());
        int sz = 1;
        while (sz < (int)(da.size() + db.size())) sz <<= 1;
        fa.resize(sz);
        fb.resize(sz);
        ntt(fa, false, mod, root);
        ntt(fb, false, mod, root);
        for (int i = 0; i < sz; i++) fa[i] = (ll)((__int128)fa[i] * fb[i] % mod);
        ntt(fa, true, mod, root);
        return fa;
    }

    vector<int> to_fft_base() const {
        vector<int> res;
        res.reserve(a.size() * FFT_BASE_DIGITS);
        for (int x : a)
            for (int i = 0; i < BASE_DIGITS / FFT_BASE_DIGITS; i++) {
                res.push_back(x % FFT_BASE);
                x /= FFT_BASE;
            }
        while (!res.empty() && res.back() == 0) res.pop_back();
        return res;
    }

    BigInt mul_ntt(const BigInt &v) const {
        vector<int> da = to_fft_base(), db = v.to_fft_base();

        vector<ll> c1 = convolve_mod(da, db, NTT_MOD1, NTT_ROOT1);
        vector<ll> c2 = convolve_mod(da, db, NTT_MOD2, NTT_ROOT2);
        int sz = (int)c1.size(); // c1, c2 always same length: same da/db
        ll inv1_mod2 = binexp(NTT_MOD1 % NTT_MOD2, NTT_MOD2 - 2, NTT_MOD2);

        vector<int> digits;
        digits.reserve(sz + FFT_BASE_DIGITS);
        ll carry = 0;
        for (int i = 0; i < sz || carry; i++) {
            ll cur = carry;
            if (i < sz) {
                ll r1 = c1[i], r2 = c2[i];
                ll t = (r2 - r1) % NTT_MOD2;
                if (t < 0) t += NTT_MOD2;
                t = (ll)((__int128)t * inv1_mod2 % NTT_MOD2);
                ll exact = r1 + t * NTT_MOD1;
                cur += exact;
            }
            digits.push_back((int)(cur % FFT_BASE));
            carry = cur / FFT_BASE;
        }
        while (!digits.empty() && digits.back() == 0) digits.pop_back();

        // regroup base-1000 digits back into base-1e9 digits, 3 at a time
        static const int POW1000[3] = {1, 1000, 1000000};
        BigInt res;
        res.sign = a.empty() || v.a.empty() ? 1 : sign * v.sign;
        res.a.assign((digits.size() + 2) / 3, 0);
        for (size_t i = 0; i < digits.size(); i++)
            res.a[i / 3] += digits[i] * POW1000[i % 3];
        res.trim();
        return res;
    }

    BigInt operator*(const BigInt &v) const {
        if ((ll)a.size() * (ll)v.a.size() <= 4000) return mul_simple(v);
        return mul_ntt(v);
    }
    BigInt &operator*=(const BigInt &v) { return *this = *this * v; }

    // ---- small-int (ll) helpers ----
    BigInt &operator*=(ll v) {
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
    BigInt operator*(ll v) const { BigInt res = *this; res *= v; return res; }

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
    BigInt &operator/=(ll v) {
        if (v < 0) { sign = -sign; v = -v; }
        a = div_small(a, v).first;
        trim();
        return *this;
    }
    BigInt operator/(ll v) const { BigInt res = *this; res /= v; return res; }

    // ---- full bigint / bigint division & modulo ----
    static void divmod(const BigInt &a1, const BigInt &b1, BigInt &q, BigInt &r) {
        ll norm = BASE / (b1.a.back() + 1);
        BigInt a = a1.abs_val() * norm;
        BigInt b = b1.abs_val() * norm;
        q.a.assign(a.a.size(), 0);
        q.sign = 1;
        r = BigInt(0);
        for (int i = (int)a.a.size() - 1; i >= 0; i--) {
            r.a.insert(r.a.begin(), a.a[i]);
            r.trim();
            // estimate digit from top limbs; normalization makes it overshoot by at most 2
            size_t m = b.a.size();
            ll s1 = r.a.size() > m ? r.a[m] : 0;
            ll s2 = r.a.size() > m - 1 ? r.a[m - 1] : 0;
            ll d = min((s1 * BASE + s2) / b.a.back(), (ll)BASE - 1);
            r -= b * d;
            while (r < 0) { r += b; d--; }
            q.a[i] = (int)d;
        }
        q.sign = a1.sign * b1.sign;
        q.trim();
        r /= norm;
        r.sign = a1.is_zero() ? 1 : a1.sign;
        r.trim();
    }

    BigInt operator/(const BigInt &v) const { BigInt q, r; divmod(*this, v, q, r); return q; }
    BigInt operator%(const BigInt &v) const { BigInt q, r; divmod(*this, v, q, r); return r; }
    BigInt &operator/=(const BigInt &v) { return *this = *this / v; }
    BigInt &operator%=(const BigInt &v) { return *this = *this % v; }

    bool is_zero() const { return a.empty(); }
    explicit operator bool() const { return !is_zero(); }

    string to_string() const {
        ostringstream ss;
        ss << *this;
        return ss.str();
    }
};