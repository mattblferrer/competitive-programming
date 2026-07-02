class Solution {
public:
    int absDifference(vector<int> &nums, int k) {
        sort(nums.begin(), nums.end());
        int ans = 0, n = nums.size();
        for (int i = n - 1; i >= n - k; i--) ans += nums[i];
        for (int i = 0; i < k; i++) ans -= nums[i];
        return ans;
    }
};