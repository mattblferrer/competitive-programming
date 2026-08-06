class Solution {
public:
    bool is_nondecreasing(vector<int> &nums) {
        bool is_nondec = true;
        for (int j = 0; j < nums.size() - 1; j++) {
            if (nums[j] > nums[j + 1]) return false;
        }
        return true;
    }

    int minimumPairRemoval(vector<int> &nums) {
        if (is_nondecreasing(nums)) return 0;

        int ans = 0;
        while (nums.size() > 1) {
            int min_sum = 1'000'000, min_j = -1;
            for (int j = 0; j < nums.size() - 1; j++) {
                if (min_sum > nums[j] + nums[j + 1]) {
                    min_sum = nums[j] + nums[j + 1];
                    min_j = j;
                }
            }
            vector<int> new_nums;
            for (int j = 0; j < min_j; j++) new_nums.push_back(nums[j]);
            new_nums.push_back(nums[min_j] + nums[min_j + 1]);
            for (int j = min_j + 2; j < nums.size(); j++) new_nums.push_back(nums[j]);
            nums = new_nums;
            ans++;

            if (is_nondecreasing(nums)) return ans;

        }
        return ans;
    }
};