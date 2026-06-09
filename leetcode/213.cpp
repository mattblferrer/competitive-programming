class Solution {
public:
    int helper(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];

        int n = nums.size();
        vector<int> ans(n);
        ans[0] = nums[0];
        ans[1] = max(nums[0], nums[1]);
        for (int i = 2; i < n; i++) {
            ans[i] = max(ans[i - 2] + nums[i], ans[i - 1]);
        }

        return ans.back();
    }
    int rob(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];

        vector<int> a(nums.begin(), nums.end() - 1);
        vector<int> b(nums.begin() + 1, nums.end());
        return max(helper(a), helper(b));
    }
};