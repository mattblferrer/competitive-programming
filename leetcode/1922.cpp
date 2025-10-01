#include <bits/stdc++.h>
using namespace std;
const long long mod = 1000000007;

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

class Solution {
public:
    int countGoodNumbers(long long n) {
        long long ans = (binexp(5, n / 2 + n % 2, mod) * binexp(4, n / 2, mod)) % mod;
        return ans;
    }
};