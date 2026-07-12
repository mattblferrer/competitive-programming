class Solution {
public:
    long long MOD = 1'000'000'007;
    int minimumCost(vector<int> &nums, int k) {
        long long sum = 0, n = nums.size();
        for (int i = 0; i < n; i++) {
            sum += nums[i];
        }
        long long ref = ((sum + k - 1) / k) % MOD;
        long long cost = ((ref * (ref - 1)) / 2) % MOD;
        return cost;
    }
};