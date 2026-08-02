class Solution {
public:
    long long maxPairStrength(vector<int> &nums) {
        int n = nums.size();
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                long long ni = nums[i], nj = nums[j], g = gcd(nums[i], nums[j]);
                ans = max(ans, ni * nj / (g * g));
            }
        }
        return ans;
    }
};