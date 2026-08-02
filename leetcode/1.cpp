class Solution {
public:
    vector<int> twoSum(vector<int> &nums, int target) {
        unordered_map<int, int> num_idx;
        for (int i = 0; i < nums.size(); i++) num_idx[nums[i]] = i;
        for (int i = 0; i < nums.size(); i++) {
            if (num_idx.find(target - nums[i]) == num_idx.end()) continue;
            int j = num_idx[target - nums[i]];
            if (i == j) continue;
            return {i, j};
        }
        return {};
    }
};