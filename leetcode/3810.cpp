class Solution {
public:
    int minOperations(vector<int> &nums, vector<int> &target) {
        int n = nums.size();
        set<int> distinct;
        for (int i = 0; i < n; i++) {
            if (nums[i] != target[i]) distinct.insert(nums[i]);
        }
        return distinct.size();
    }
};