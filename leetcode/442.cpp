class Solution {
public:
    vector<int> findDuplicates(vector<int> &nums) {
        vector<int> ans, temp = nums;
        for (int i = 0; i < nums.size(); i++) {
            if (temp[nums[i] - 1] < 0) ans.push_back(nums[i]);
            else temp[nums[i] - 1] = -temp[nums[i] - 1];
        }
        return ans;
    }
};