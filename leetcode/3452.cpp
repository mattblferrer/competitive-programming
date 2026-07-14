class Solution {
public:
    int sumOfGoodNumbers(vector<int> &nums, int k) {
        int ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            bool is_good = true;
            if ((i - k >= 0) && (nums[i - k] >= nums[i])) is_good = false;
            if ((i + k < nums.size()) && (nums[i + k] >= nums[i])) is_good = false;
            if (is_good) ans += nums[i];
        }
        return ans;
    }
};