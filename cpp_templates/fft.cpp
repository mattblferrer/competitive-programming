#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using cd = complex<double>;
const ll NTT_MOD = 998'244'353, NTT_ROOT = 3;

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
// exact while (sum a[i]^2 + sum b[i]^2) * log2(n + m) < ~9e14; use ntt_multiply for results mod 998244353
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

// in-place NTT mod 998244353 (inverse if invert); a.size() must be a power of 2 up to 2^23, O(n log n)
void ntt(vector<ll> &a, bool invert = false) {
    int n = a.size();
    assert(n > 0 && (n & (n - 1)) == 0);
    for (int i = 1, j = 0; i < n; i++) {  // bit-reversal permutation
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ll w = binexp(NTT_ROOT, (NTT_MOD - 1) / len, NTT_MOD);
        if (invert) w = binexp(w, NTT_MOD - 2, NTT_MOD);
        for (int i = 0; i < n; i += len) {
            ll wn = 1;
            for (int j = 0; j < len / 2; j++) {
                ll u = a[i + j], v = a[i + j + len / 2] * wn % NTT_MOD;
                a[i + j] = u + v < NTT_MOD ? u + v : u + v - NTT_MOD;
                a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + NTT_MOD;
                wn = wn * w % NTT_MOD;
            }
        }
    }
    if (invert) {
        ll n_inv = binexp(n, NTT_MOD - 2, NTT_MOD);
        for (ll &x : a) x = x * n_inv % NTT_MOD;
    }
}

// product of polynomials a and b mod 998244353 (exact mod p for any input size), O((n + m) log(n + m))
vector<ll> ntt_multiply(vector<ll> a, vector<ll> b) {
    if (a.empty() || b.empty()) return {};
    int need = a.size() + b.size() - 1, n = 1;
    while (n < need) n <<= 1;
    for (ll &x : a) x = (x % NTT_MOD + NTT_MOD) % NTT_MOD;
    for (ll &x : b) x = (x % NTT_MOD + NTT_MOD) % NTT_MOD;
    a.resize(n);
    b.resize(n);
    ntt(a);
    ntt(b);
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % NTT_MOD;
    ntt(a, true);
    a.resize(need);
    return a;
}
