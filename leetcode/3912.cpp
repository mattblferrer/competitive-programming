class Solution {
public:
    vector<int> findValidElements(vector<int> &nums) {
        vector<int> valid;
        for (int i = 0; i < nums.size(); i++) {
            bool is_valid = true;
            for (int j = 0; j < i; j++) {
                if (nums[j] >= nums[i]) {
                    is_valid = false;
                    break;
                }
            }
            if (is_valid) { valid.push_back(nums[i]); continue; }
            is_valid = true;
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[j] >= nums[i]) {
                    is_valid = false;
                    break;
                }
            }
            if (is_valid) { valid.push_back(nums[i]); continue; }
        }
        return valid;
    }
};