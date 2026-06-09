class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        long long min_n = LLONG_MAX, max_n = 0;
        for (int i = 0; i < nums.size(); i++) {
            min_n = min(min_n, (long long)nums[i]);
            max_n = max(max_n, (long long)nums[i]);
        }
        return (max_n - min_n) * k;
    }
};