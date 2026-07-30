class Solution {
public:
    long long maxProduct(vector<int> &nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end(), [](int a, int b) {
            return abs(a) < abs(b);
            });
        long long ans = max({
            (long long)nums[n - 1] * nums[n - 2] * nums[n - 3],
            (long long)nums[n - 1] * nums[n - 2] * -100'000,
            (long long)nums[n - 1] * nums[n - 2] * 100'000
            });
        return ans;
    }
};