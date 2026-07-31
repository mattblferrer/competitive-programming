class Solution {
public:
    int valueAfterKSeconds(int n, int k) {
        long long mod = 1'000'000'007;
        vector<long long> cur(n, 1);
        for (int i = 0; i < k; i++) {
            for (int j = 1; j < n; j++) {
                cur[j] = (cur[j - 1] + cur[j]) % mod;
            }
        }
        return cur[n - 1];
    }
};