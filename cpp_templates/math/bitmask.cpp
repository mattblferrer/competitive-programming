// Contents
//   sos_subset          SOS DP: a[mask] becomes the sum of a[sub] over all submasks sub of mask (undone if...
//   sos_superset        SOS DP: a[mask] becomes the sum of a[sup] over all supermasks sup of mask (undone if...
//   xor_transform       Walsh-Hadamard transform (inverse if invert, including the 1/n scaling), O(n log n)
//   pad_to_power        pads a and b with zeros to a common power of 2 length (at least 1), O(n)
//   or_convolution      c[k] = sum of a[i] * b[j] over all i | j == k, O(n log n)
//   and_convolution     c[k] = sum of a[i] * b[j] over all i & j == k, O(n log n)
//   xor_convolution     c[k] = sum of a[i] * b[j] over all i ^ j == k, O(n log n)
//   subset_convolution  c[k] = sum of a[i] * b[j] over i | j == k and i & j == 0, mod a prime, O(n^2 2^n)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// everything here works with T = ll or T = ModInt<MOD>; a.size() must be a power of 2 for the transforms

// SOS DP: a[mask] becomes the sum of a[sub] over all submasks sub of mask (undone if invert), O(n log n)
template <class T>
void sos_subset(vector<T> &a, bool invert = false) {
    int n = a.size();
    assert(n > 0 && (n & (n - 1)) == 0);
    for (int bit = 1; bit < n; bit <<= 1) {
        for (int mask = 0; mask < n; mask++) {
            if (!(mask & bit)) continue;
            if (invert) a[mask] -= a[mask ^ bit];
            else a[mask] += a[mask ^ bit];
        }
    }
}

// SOS DP: a[mask] becomes the sum of a[sup] over all supermasks sup of mask (undone if invert), O(n log n)
template <class T>
void sos_superset(vector<T> &a, bool invert = false) {
    int n = a.size();
    assert(n > 0 && (n & (n - 1)) == 0);
    for (int bit = 1; bit < n; bit <<= 1) {
        for (int mask = 0; mask < n; mask++) {
            if (mask & bit) continue;
            if (invert) a[mask] -= a[mask ^ bit];
            else a[mask] += a[mask ^ bit];
        }
    }
}

// Walsh-Hadamard transform (inverse if invert, including the 1/n scaling), O(n log n)
// the inverse divides by n, which is exact for T = ll and needs an odd modulus for T = ModInt
template <class T>
void xor_transform(vector<T> &a, bool invert = false) {
    int n = a.size();
    assert(n > 0 && (n & (n - 1)) == 0);
    for (int bit = 1; bit < n; bit <<= 1) {
        for (int i = 0; i < n; i += 2 * bit) {
            for (int j = i; j < i + bit; j++) {
                T x = a[j], y = a[j + bit];
                a[j] = x + y;
                a[j + bit] = x - y;
            }
        }
    }
    if (invert) {
        for (T &x : a) x = x / T(n);
    }
}

// pads a and b with zeros to a common power of 2 length (at least 1), O(n)
template <class T>
int pad_to_power(vector<T> &a, vector<T> &b) {
    int n = 1;
    while (n < (int)max(a.size(), b.size())) n <<= 1;
    a.resize(n);
    b.resize(n);
    return n;
}

// c[k] = sum of a[i] * b[j] over all i | j == k, O(n log n)
template <class T>
vector<T> or_convolution(vector<T> a, vector<T> b) {
    int n = pad_to_power(a, b);
    sos_subset(a);
    sos_subset(b);
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i];
    sos_subset(a, true);
    return a;
}

// c[k] = sum of a[i] * b[j] over all i & j == k, O(n log n)
template <class T>
vector<T> and_convolution(vector<T> a, vector<T> b) {
    int n = pad_to_power(a, b);
    sos_superset(a);
    sos_superset(b);
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i];
    sos_superset(a, true);
    return a;
}

// c[k] = sum of a[i] * b[j] over all i ^ j == k, O(n log n)
template <class T>
vector<T> xor_convolution(vector<T> a, vector<T> b) {
    int n = pad_to_power(a, b);
    xor_transform(a);
    xor_transform(b);
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i];
    xor_transform(a, true);
    return a;
}

// subset convolution: c[k] = sum of a[i] * b[j] over all i | j == k with i & j == 0, mod mod (below 2^31)
// a and b have size 2^n; zeta transforms split by popcount (rank), multiplied rank by rank, O(n^2 2^n)
vector<ll> subset_convolution(const vector<ll> &a, const vector<ll> &b, ll mod) {
    int N = a.size(), n = __lg(N), R = n + 1;
    assert(N == (1 << n) && b.size() == a.size());
    unsigned m = mod;
    vector<unsigned> f((size_t)N * R), g((size_t)N * R);  // f[mask * R + rank]
    for (int s = 0; s < N; s++) {
        f[(size_t)s * R + __builtin_popcount(s)] = a[s] % mod;
        g[(size_t)s * R + __builtin_popcount(s)] = b[s] % mod;
    }
    auto zeta = [&](vector<unsigned> &h, bool invert) {
        for (int bit = 1; bit < N; bit <<= 1) {
            for (int s = 0; s < N; s++) {
                if (!(s & bit)) continue;
                unsigned *x = &h[(size_t)s * R], *y = &h[(size_t)(s ^ bit) * R];
                if (invert) for (int r = 0; r < R; r++) x[r] = x[r] >= y[r] ? x[r] - y[r] : x[r] + m - y[r];
                else for (int r = 0; r < R; r++) x[r] = x[r] + y[r] >= m ? x[r] + y[r] - m : x[r] + y[r];
            }
        }
    };
    zeta(f, false);
    zeta(g, false);
    vector<unsigned> prod(R);
    for (int s = 0; s < N; s++) {
        unsigned *x = &f[(size_t)s * R], *y = &g[(size_t)s * R];
        for (int k = 0; k < R; k++) {
            unsigned long long acc = 0;
            for (int i = 0; i <= k; i++) acc = (acc + (unsigned long long)x[i] * y[k - i]) % m;
            prod[k] = acc;
        }
        copy(prod.begin(), prod.end(), x);
    }
    zeta(f, true);
    vector<ll> c(N);
    for (int s = 0; s < N; s++) c[s] = f[(size_t)s * R + __builtin_popcount(s)];
    return c;
}
