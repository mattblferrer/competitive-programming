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

bool is_prime(long long n) {
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return n > 1;
}

void sieve(std::vector<bool>& is_prime, long long n) {
    is_prime.assign(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (long long i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (long long j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
}