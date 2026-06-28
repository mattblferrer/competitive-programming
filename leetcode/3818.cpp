class Solution {
public:
    int minimumPrefixLength(vector<int> &nums) {
        int ans = nums.size() - 1;
        for (int i = nums.size() - 2; i >= 0; i--) {
            if (nums[i] < nums[i + 1]) ans--;
            else break;
        }
        return ans;
    }
};