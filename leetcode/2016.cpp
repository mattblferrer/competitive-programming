class Solution {
public:
    int maximumDifference(vector<int> &nums) {
        int min_n = INT_MAX, ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            ans = max(ans, nums[i] - min_n);
            min_n = min(min_n, nums[i]);
        }
        if (ans == 0) return -1;
        return ans;
    }
};