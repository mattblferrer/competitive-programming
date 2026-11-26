// Contents
//   fft                  in-place FFT (inverse FFT if invert, including the 1/n scaling)
//   multiply             product of integer polynomials a and b, O((n + m) log(n + m))
//   binexp               a^b mod mod, O(log b)
//   NTT                  number theoretic transform, each MOD and ROOT pair is its own type
//   garner               combine residues mod several primes into the value mod `mod` (0 means mod 2^64)
//   convolution_any_mod  product of polynomials a and b mod any modulus below 2^31
//   convolution_mod_2_64 product of polynomials a and b mod 2^64
//   wildcard_match       res[i] = 1 if s[i, i + |t|) matches t, where `wild` matches any character

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
using cd = complex<double>;

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
//   ntt(a, invert)   in-place NTT (inverse if invert) of a vector<ll> or vector<unsigned> (half the memory) with values
//                    in [0, MOD); a.size() must be a power of 2 up to the max size; the forward result is in
//                    bit-reversed order and the inverse expects that order (fine for pointwise products), O(n log n)
//   multiply(a, b)   product of polynomials a and b mod MOD, O((n + m) log(n + m))
//   multiply_large(a, b)   multiply for products longer than the max size, in blocks; pass a and b with move to save
//                          memory, O((n + m) log(max size) + n * m / max size)
template <ll MOD, ll ROOT>
struct NTT {
    template <class T>
    static void ntt(vector<T> &a, bool invert = false) {
        int n = a.size();
        assert(n > 0 && (n & (n - 1)) == 0 && (MOD - 1) % n == 0);
        static vector<T> rt(2, 1);  // rt[k + j] = w^j, w a primitive (2k)-th root of unity, for each power of 2 k
        for (static int k = 2; k < n; k *= 2) {
            rt.resize(n);
            ull z = binexp(ROOT, (MOD - 1) / (2 * k), MOD);
            for (int j = k; j < 2 * k; j++) rt[j] = j & 1 ? rt[j / 2] * z % MOD : rt[j / 2];
        }
        if (!invert) {  // decimation in frequency: no bit-reversal pass, output in bit-reversed order
            for (int k = n / 2; k >= 1; k /= 2) {
                for (int i = 0; i < n; i += 2 * k) {
                    for (int j = 0; j < k; j++) {
                        T &u = a[i + j], &v = a[i + j + k], x = u, y = v;
                        u = x + y < MOD ? x + y : x + y - MOD;
                        v = (ull)(x < y ? x + MOD - y : x - y) * rt[j + k] % MOD;
                    }
                }
            }
            return;
        }
        for (int k = 1; k < n; k *= 2) {  // decimation in time: bit-reversed input, natural order output
            for (int i = 0; i < n; i += 2 * k) {
                for (int j = 0; j < k; j++) {
                    T &u = a[i + j], &v = a[i + j + k], x = u, y = (ull)v * rt[j + k] % MOD;
                    u = x + y < MOD ? x + y : x + y - MOD;
                    v = x < y ? x + MOD - y : x - y;
                }
            }
        }
        reverse(a.begin() + 1, a.end());  // turns the transform with w into the one with w^-1
        ull n_inv = binexp(n, MOD - 2, MOD);
        for (T &x : a) x = x * n_inv % MOD;
    }

    static vector<ll> multiply(const vector<ll> &a, const vector<ll> &b) {
        if (a.empty() || b.empty()) return {};
        int need = a.size() + b.size() - 1, n = 1;
        while (n < need) n <<= 1;
        vector<unsigned> fa(n), fb(n);
        for (int i = 0; i < (int)a.size(); i++) fa[i] = (a[i] % MOD + MOD) % MOD;
        for (int i = 0; i < (int)b.size(); i++) fb[i] = (b[i] % MOD + MOD) % MOD;
        ntt(fa);
        ntt(fb);
        for (int i = 0; i < n; i++) fa[i] = (ull)fa[i] * fb[i] % MOD;
        ntt(fa, true);
        return vector<ll>(fa.begin(), fa.begin() + need);
    }

    static vector<ll> multiply_large(vector<ll> a, vector<ll> b) {
        if (a.empty() || b.empty()) return {};
        int need = a.size() + b.size() - 1, sz = (MOD - 1) & -(MOD - 1), L = sz / 2;  // sz = max size
        if (need <= sz) return multiply(a, b);
        auto blocks = [&](vector<ll> &v) {  // NTT of each length-L block of v, zero-padded to sz; frees v
            vector<vector<unsigned>> res;
            for (int i = 0; i < (int)v.size(); i += L) {
                vector<unsigned> blk(sz);
                for (int t = i; t < min((int)v.size(), i + L); t++) blk[t - i] = (v[t] % MOD + MOD) % MOD;
                ntt(blk);
                res.push_back(move(blk));
            }
            vector<ll>().swap(v);
            return res;
        };
        vector<vector<unsigned>> A = blocks(a), B = blocks(b);
        int na = A.size(), nb = B.size();
        vector<ll> res(need);
        vector<unsigned> c(sz);
        for (int k = 0; k < na + nb - 1; k++) {  // output block k = sum of A[i] * B[k - i], overlap-added at k * L
            fill(c.begin(), c.end(), 0);
            for (int i = max(0, k - nb + 1); i <= min(k, na - 1); i++) {
                for (int t = 0; t < sz; t++) c[t] = (c[t] + (ull)A[i][t] * B[k - i][t]) % MOD;
            }
            ntt(c, true);
            for (int t = 0; t < sz && (ll)k * L + t < need; t++) {
                ll &r = res[(ll)k * L + t];
                r = r + c[t] < MOD ? r + c[t] : r + c[t] - MOD;
            }
        }
        return res;
    }
};

// Garner/CRT: combine residues r[j][i] mod primes ps[j] into the value mod `mod` (mod = 0 means mod 2^64);
// exact while each value is below the product of ps, O(len * k^2)
vector<ull> garner(const vector<vector<ll>> &r, const vector<ll> &ps, ull mod) {
    int k = ps.size(), len = r[0].size();
    vector<vector<ll>> pre(k, vector<ll>(k + 1, 1));  // pre[j][t] = ps[0] * ... * ps[t - 1] mod ps[j]
    vector<ll> inv(k), x(k);
    vector<ull> pm(k + 1, 1), res(len);  // pm[t] = ps[0] * ... * ps[t - 1] mod `mod`
    for (int j = 0; j < k; j++) {
        for (int t = 0; t < k; t++) pre[j][t + 1] = pre[j][t] * (ps[t] % ps[j]) % ps[j];
        inv[j] = binexp(pre[j][j], ps[j] - 2, ps[j]);
        pm[j + 1] = mod ? pm[j] * (ps[j] % mod) % mod : pm[j] * ps[j];
    }
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < k; j++) {  // value = x[0] + x[1] * ps[0] + x[2] * ps[0] * ps[1] + ...
            ll cur = r[j][i];
            for (int t = 0; t < j; t++) cur = (cur - x[t] * pre[j][t] % ps[j] + ps[j]) % ps[j];
            x[j] = cur * inv[j] % ps[j];
            res[i] = mod ? (res[i] + x[j] % mod * pm[j]) % mod : res[i] + x[j] * pm[j];
        }
    }
    return res;
}

// product of polynomials a and b mod any modulus below 2^31, using three NTT primes and CRT, O((n + m) log(n + m))
// exact while (n + m) <= 2^23 and min(n, m) * mod^2 < 7.8e25
vector<ll> convolution_any_mod(vector<ll> a, vector<ll> b, ll mod) {
    if (a.empty() || b.empty()) return {};
    for (ll &x : a) x = (x % mod + mod) % mod;
    for (ll &x : b) x = (x % mod + mod) % mod;
    vector<ull> c = garner({NTT<998'244'353, 3>::multiply(a, b), NTT<469'762'049, 3>::multiply(a, b),
                            NTT<167'772'161, 3>::multiply(a, b)}, {998'244'353, 469'762'049, 167'772'161}, mod);
    return vector<ll>(c.begin(), c.end());
}

// product of polynomials a and b mod 2^64, using five NTT primes and CRT, exact while (n + m) <= 2^21,
// O((n + m) log(n + m))
vector<ull> convolution_mod_2_64(const vector<ull> &a, const vector<ull> &b) {
    if (a.empty() || b.empty()) return {};
    auto red = [](const vector<ull> &v, ll p) {  // reduce as ull: values >= 2^63 don't fit in ll
        vector<ll> w;
        for (ull x : v) w.push_back(x % p);
        return w;
    };
    return garner({NTT<998'244'353, 3>::multiply(red(a, 998'244'353), red(b, 998'244'353)),
                   NTT<469'762'049, 3>::multiply(red(a, 469'762'049), red(b, 469'762'049)),
                   NTT<754'974'721, 11>::multiply(red(a, 754'974'721), red(b, 754'974'721)),
                   NTT<1'004'535'809, 3>::multiply(red(a, 1'004'535'809), red(b, 1'004'535'809)),
                   NTT<2'013'265'921, 31>::multiply(red(a, 2'013'265'921), red(b, 2'013'265'921))},
                  {998'244'353, 469'762'049, 754'974'721, 1'004'535'809, 2'013'265'921}, 0);
}

// res[i] = 1 if s[i, i + |t|) matches t, where `wild` (in either string) matches any character; using NTT above
// window sum of a * b * (a - b)^2 is 0 on a match, with wild = 0 and each character a random nonzero value mod p
// (random so no fixed test can force a false match; about n / p chance of any error), O(n log n)
vector<int> wildcard_match(const string &s, const string &t, char wild = '*') {
    constexpr ull p = 998'244'353;
    static mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
    int n = s.size(), m = t.size(), sz = 1;
    if (m > n) return {};
    while (sz < n) sz <<= 1;  // cyclic convolution of size >= n is enough: wrapped terms land below index m - 1
    ull val[256];
    for (ull &v : val) v = gen() % (p - 1) + 1;
    val[(unsigned char)wild] = 0;
    vector<vector<unsigned>> A(3, vector<unsigned>(sz)), B = A;  // powers 1, 2, 3 of s and of reversed t
    for (int i = 0; i < n; i++) {
        ull x = val[(unsigned char)s[i]];
        A[0][i] = x, A[1][i] = x * x % p, A[2][i] = A[1][i] * x % p;
    }
    for (int i = 0; i < m; i++) {
        ull x = val[(unsigned char)t[m - 1 - i]];
        B[0][i] = x, B[1][i] = x * x % p, B[2][i] = B[1][i] * x % p;
    }
    for (int k = 0; k < 3; k++) NTT<p, 3>::ntt(A[k]), NTT<p, 3>::ntt(B[k]);
    vector<unsigned> c(sz);
    for (int i = 0; i < sz; i++) {
        c[i] = ((ull)A[0][i] * B[2][i] + (ull)A[2][i] * B[0][i] + (p - 2) * A[1][i] % p * B[1][i]) % p;
    }
    NTT<p, 3>::ntt(c, true);
    vector<int> res(n - m + 1);
    for (int i = 0; i <= n - m; i++) res[i] = c[m - 1 + i] == 0;
    return res;
}
