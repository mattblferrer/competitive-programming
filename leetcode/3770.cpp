class Solution {
public:
    bool is_prime(int n) {
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) return false;
        }
        return n > 1;
    }
    int largestPrime(int n) {
        int curr = 0, ans = 0;
        for (int i = 2; curr <= n; i++) {
            if (is_prime(curr)) ans = curr;
            if (!is_prime(i)) continue;
            curr += i;
        }
        return ans;
    }
};