class Solution {
public:
    int maxLength(vector<int> &nums) {
        int n = nums.size(), ans = 0;
        for (int i = 0; i < n; i++) {
            long long p = 1, g = nums[i], l = nums[i], max_lcm = 1'000'000'000'000'000;
            for (int j = i; j < n; j++) {
                p *= nums[j];
                if (p > max_lcm) break;
                g = gcd(g, nums[j]);
                l = lcm(l, nums[j]);
                if (p == g * l) ans = max(ans, j - i + 1);
            }
        }
        return ans;
    }
};