class Solution {
public:
    int subarraySum(vector<int> &nums) {
        int ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = max(0, i - nums[i]); j <= i; j++) ans += nums[j];
        }
        return ans;
    }
};