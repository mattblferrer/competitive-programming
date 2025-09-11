#include <bits/stdc++.h>

std::vector<long long> fac;

// helper functions
long long binexp(long long a, long long b, long long mod) {
    long long ans = 1;
    while (b) {
        if (b % 2) {
            ans = (ans * a) % mod;
        }
        a = (a * a) % mod;  
        b >>= 1;
    }
    return ans;
}

long long modinv_p(long long a, long long p) {
    return binexp(a, p - 2, p);
}

void factorial_vec(long long n, long long mod, std::vector<long long> arr) {
    arr.resize(n + 1);
    arr[0] = 1;
    for (int i = 1; i <= n; i++) {
        arr[i] = arr[i - 1] * i % mod;
    }
}

// main functions
long long comb(long long n, long long k) {
    if (k < 0) return 0;
    if (k == 0) return 1;
    return (n * comb(n - 1, k - 1)) / k;
}

long long factorial(long long n) {
    if (n == 0) return 0;
    return n * factorial(n - 1);
}

long long comb_m(long long n, long long k, long long p) {
    // call factorial_vec(n, p, fac)
    return fac[n] * modinv_p((fac[k] * fac[n - k]) % p, p) % p;
}
