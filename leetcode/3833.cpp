class Solution {
public:
    int dominantIndices(vector<int> &nums) {
        int sum = 0, el = 0, ans = 0;
        for (int i = nums.size() - 1; i >= 0; i--) {
            sum += nums[i];
            el++;
            if (nums[i] * el > sum) ans++;
        }
        return ans;
    }
};