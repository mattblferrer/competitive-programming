class Solution {
public:
    long long maxAlternatingSum(vector<int> &nums) {
        sort(nums.begin(), nums.end(), [](int a, int b) {
            return abs(a) < abs(b);
            });
        long long ans = 0;
        for (int i = 0; i < nums.size() / 2; i++) ans -= nums[i] * nums[i];
        for (int i = nums.size() / 2; i < nums.size(); i++) ans += nums[i] * nums[i];
        return ans;
    }
};