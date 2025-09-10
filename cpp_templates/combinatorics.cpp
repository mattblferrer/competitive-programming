#include <bits/stdc++.h>

long long comb(long long n, long long k) {
    if (k < 0) return 0;
    if (k == 0) return 1;
    return (n * comb(n - 1, k - 1)) / k;
}
