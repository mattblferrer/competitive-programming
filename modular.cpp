#include <bits/stdc++.h>

long long binexp(long long a, long long b, long long mod) {
    long long ans = 1;
    while (b > 0) {
        if (b % 2 == 1) {
            ans = (ans * a) % mod;
            b--;
        }
        a = (a * a) % mod;  
        b >>= 1;
    }
    return ans;
}

long long modinv(long long a, long long mod) {
    return binexp(a, mod - 2, mod);
}
