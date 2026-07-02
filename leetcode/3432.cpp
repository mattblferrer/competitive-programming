class Solution {
public:
    int countPartitions(vector<int> &nums) {
        int left = 0, right = 0, ans = 0;
        for (int i = 0; i < nums.size(); i++) left += nums[i];
        for (int i = 0; i < nums.size() - 1; i++) {
            left -= nums[i];
            right += nums[i];
            if (abs(left - right) % 2 == 0) ans++;
        }
        return ans;
    }
};