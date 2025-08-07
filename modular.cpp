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

long long modinv(long long a, long long mod) {
    return binexp(a, mod - 2, mod);
}
