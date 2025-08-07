#include <bits/stdc++.h>

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

long long extended_euclidean(long long a, long long b, long long& x, long long& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long gcd = extended_euclidean(b, a % b, y, x);
    y -= (a / b) * x;
    return gcd;
}

long long modinv(long long a, long long mod) {
    long long x, y;
    long long gcd = extended_euclidean(a, mod, x, y);
    if (gcd != 1) {
        return -1;  // doesn't exist
    }
    return (x % mod + mod) % mod;
}
