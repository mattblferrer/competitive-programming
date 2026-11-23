// Contents
//   fft                  in-place FFT (inverse FFT if invert, including the 1/n scaling)
//   multiply             product of integer polynomials a and b, O((n + m) log(n + m))
//   binexp               a^b mod mod, O(log b)
//   NTT                  number theoretic transform, each MOD and ROOT pair is its own type
//   garner               combine residues mod several primes into the value mod `mod` (0 means mod 2^64)
//   convolution_any_mod  product of polynomials a and b mod any modulus below 2^31
//   convolution_mod_2_64 product of polynomials a and b mod 2^64

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
