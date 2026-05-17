#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPrime(int n) {
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) return false;
        }
        return n > 1;
    }

    int sumOfPrimesInRange(int n) {
        string rstr = to_string(n);
        reverse(rstr.begin(), rstr.end());
        int rev = stoi(rstr);

        int ans = 0;
        for (int i = min(n, rev); i <= max(n, rev); i++) {
            if (isPrime(i)) ans += i;
        }
        return ans;
    }
};