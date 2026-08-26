#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

using namespace std;

struct BigInt {
    static const int BASE = 1000000000;
    static const int BASE_DIGITS = 9;
    vector<int> a;   // little-endian, base 1e9 digits
    int sign;        // 1 or -1 (0 is stored as sign=1, empty a)

    BigInt(): sign(1) {}
    BigInt(long long v) { *this = v; }
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

    BigInt &operator=(long long v) {
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
        for (int i = (int)v.a.size() - 2; i >= 0; --i)
            out << setw(BASE_DIGITS) << setfill('0') << v.a[i];
        return out;
    }

    static bool absLess(const BigInt &x, const BigInt &y) {
        if (x.a.size() != y.a.size()) return x.a.size() < y.a.size();
        for (int i = (int)x.a.size() - 1; i >= 0; --i)
            if (x.a[i] != y.a[i]) return x.a[i] < y.a[i];
        return false;
    }

    bool operator<(const BigInt &v) const {
        if (sign != v.sign) return sign < v.sign;
        return sign == 1 ? absLess(*this, v) : absLess(v, *this);
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

    BigInt absVal() const {
        BigInt res = *this;
        res.sign = 1;
        return res;
    }

    static vector<int> addVec(const vector<int> &x, const vector<int> &y) {
        vector<int> res;
        int carry = 0;
        for (size_t i = 0; i < max(x.size(), y.size()) || carry; ++i) {
            int cur = carry + (i < x.size() ? x[i] : 0) + (i < y.size() ? y[i] : 0);
            res.push_back(cur % BASE);
            carry = cur / BASE;
        }
        return res;
    }

    // x - y assuming |x| >= |y|
    static vector<int> subVec(const vector<int> &x, const vector<int> &y) {
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
            res.a = addVec(a, v.a);
        }
        else if (absLess(*this, v)) {
            res.sign = v.sign;
            res.a = subVec(v.a, a);
            res.trim();
        }
        else {
            res.sign = sign;
            res.a = subVec(a, v.a);
            res.trim();
        }
        return res;
    }
    BigInt operator-(const BigInt &v) const { return *this + (-v); }
    BigInt &operator+=(const BigInt &v) { return *this = *this + v; }
    BigInt &operator-=(const BigInt &v) { return *this = *this - v; }

    // Naive O(n*m) multiply — used directly for small operands
    BigInt mulSimple(const BigInt &v) const {
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

    static const long long NTT_MOD1 = 998244353, NTT_ROOT1 = 3;
    static const long long NTT_MOD2 = 469762049, NTT_ROOT2 = 3;

    static long long powmod(long long base, long long e, long long mod) {
        base %= mod;
        if (base < 0) base += mod;
        long long res = 1;
        while (e > 0) {
            if (e & 1) res = (long long)((__int128)res * base % mod);
            base = (long long)((__int128)base * base % mod);
            e >>= 1;
        }
        return res;
    }

    static void ntt(vector<long long> &f, bool invert, long long mod, long long root) {
        int n = (int)f.size();
        if (n == 1) return;

        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) swap(f[i], f[j]);
        }

        for (int len = 2; len <= n; len <<= 1) {
            long long w = invert
                ? powmod(root, mod - 1 - (mod - 1) / len, mod)
                : powmod(root, (mod - 1) / len, mod);
            for (int i = 0; i < n; i += len) {
                long long wn = 1;
                for (int j = 0; j < len / 2; j++) {
                    long long u = f[i + j];
                    long long v = (long long)((__int128)f[i + j + len / 2] * wn % mod);
                    f[i + j] = u + v >= mod ? u + v - mod : u + v;
                    f[i + j + len / 2] = u - v < 0 ? u - v + mod : u - v;
                    wn = (long long)((__int128)wn * w % mod);
                }
            }
        }
        if (invert) {
            long long n_inv = powmod(n, mod - 2, mod);
            for (long long &x : f) x = (long long)((__int128)x * n_inv % mod);
        }
    }

    // Convolves da and db modulo a single NTT prime; result[i] is only
    // meaningful mod `mod`, not the exact coefficient — see mulNTT.
    static vector<long long> convolveMod(const vector<int> &da, const vector<int> &db,
        long long mod, long long root) {
        vector<long long> fa(da.begin(), da.end()), fb(db.begin(), db.end());
        int sz = 1;
        while (sz < (int)(da.size() + db.size())) sz <<= 1;
        fa.resize(sz);
        fb.resize(sz);
        ntt(fa, false, mod, root);
        ntt(fb, false, mod, root);
        for (int i = 0; i < sz; i++) fa[i] = (long long)((__int128)fa[i] * fb[i] % mod);
        ntt(fa, true, mod, root);
        return fa;
    }

    vector<int> toFftBase() const {
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

    BigInt mulNTT(const BigInt &v) const {
        vector<int> da = toFftBase(), db = v.toFftBase();

        vector<long long> c1 = convolveMod(da, db, NTT_MOD1, NTT_ROOT1);
        vector<long long> c2 = convolveMod(da, db, NTT_MOD2, NTT_ROOT2);
        int sz = (int)c1.size(); // c1, c2 always same length: same da/db
        long long inv1_mod2 = powmod(NTT_MOD1 % NTT_MOD2, NTT_MOD2 - 2, NTT_MOD2);

        vector<int> digits;
        digits.reserve(sz + FFT_BASE_DIGITS);
        long long carry = 0;
        for (int i = 0; i < sz || carry; i++) {
            long long cur = carry;
            if (i < sz) {
                long long r1 = c1[i], r2 = c2[i];
                long long t = (r2 - r1) % NTT_MOD2;
                if (t < 0) t += NTT_MOD2;
                t = (long long)((__int128)t * inv1_mod2 % NTT_MOD2);
                long long exact = r1 + t * NTT_MOD1;
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
        if ((long long)a.size() * (long long)v.a.size() <= 4000) return mulSimple(v);
        return mulNTT(v);
    }
    BigInt &operator*=(const BigInt &v) { return *this = *this * v; }

    // ---- small-int (long long) helpers ----
    BigInt &operator*=(long long v) {
        if (v < 0) { sign = -sign; v = -v; }
        long long carry = 0;
        for (size_t i = 0; i < a.size() || carry; ++i) {
            if (i == a.size()) a.push_back(0);
            long long cur = a[i] * v + carry;
            a[i] = (int)(cur % BASE);
            carry = cur / BASE;
        }
        trim();
        return *this;
    }
    BigInt operator*(long long v) const { BigInt res = *this; res *= v; return res; }

    static pair<vector<int>, long long> divSmall(const vector<int> &x, long long b) {
        vector<int> res(x.size());
        long long rem = 0;
        for (int i = (int)x.size() - 1; i >= 0; --i) {
            long long cur = x[i] + rem * BASE;
            res[i] = (int)(cur / b);
            rem = cur % b;
        }
        while (!res.empty() && res.back() == 0) res.pop_back();
        return {res, rem};
    }
    BigInt &operator/=(long long v) {
        if (v < 0) { sign = -sign; v = -v; }
        a = divSmall(a, v).first;
        trim();
        return *this;
    }
    BigInt operator/(long long v) const { BigInt res = *this; res /= v; return res; }

    // ---- full bigint / bigint division & modulo ----
    static void divmod(const BigInt &a1, const BigInt &b1, BigInt &q, BigInt &r) {
        long long norm = BASE / (b1.a.back() + 1);
        BigInt a = a1.absVal() * norm;
        BigInt b = b1.absVal() * norm;
        q.a.assign(a.a.size(), 0);
        q.sign = 1;
        r = BigInt(0);
        for (int i = (int)a.a.size() - 1; i >= 0; i--) {
            r.a.insert(r.a.begin(), a.a[i]);
            r.trim();
            long long lo = 0, hi = BASE - 1, d = 0;
            while (lo <= hi) {
                long long mid = (lo + hi) / 2;
                BigInt t = b * mid;
                if (t <= r) { d = mid; lo = mid + 1; }
                else hi = mid - 1;
            }
            q.a[i] = (int)d;
            r = r - b * d;
        }
        q.sign = a1.sign * b1.sign;
        q.trim();
        r /= norm;
        r.sign = a1.isZero() ? 1 : a1.sign;
        r.trim();
    }

    BigInt operator/(const BigInt &v) const { BigInt q, r; divmod(*this, v, q, r); return q; }
    BigInt operator%(const BigInt &v) const { BigInt q, r; divmod(*this, v, q, r); return r; }
    BigInt &operator/=(const BigInt &v) { return *this = *this / v; }
    BigInt &operator%=(const BigInt &v) { return *this = *this % v; }

    bool isZero() const { return a.empty(); }
    explicit operator bool() const { return !isZero(); }

    string toString() const {
        ostringstream ss;
        ss << *this;
        return ss.str();
    }
};

void solve() {
    BigInt a, b;
    cin >> a >> b;
    cout << a * b << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}