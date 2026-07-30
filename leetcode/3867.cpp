class Solution {
public:
    long long gcdSum(vector<int> &nums) {
        int n = nums.size();
        int mx = 0;
        vector<int> prefix_gcd(n);
        for (int i = 0; i < n; i++) {
            mx = max(mx, nums[i]);
            prefix_gcd[i] = gcd(nums[i], mx);
        }
        sort(prefix_gcd.begin(), prefix_gcd.end());
        long long ans = 0;
        for (int i = 0; i < n / 2; i++) {
            ans += gcd(prefix_gcd[i], prefix_gcd[n - i - 1]);
        }
        return ans;
    }
};