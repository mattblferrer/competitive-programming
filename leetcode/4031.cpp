class Solution {
public:
    vector<vector<int>> findDisappearedNumbers(vector<int> &nums, int lower, int upper) {
        set<int> num_set(nums.begin(), nums.end());
        vector<vector<int>> ans;
        int left = lower, right = lower - 1;
        for (int i = lower; i <= upper; i++) {
            if (num_set.count(i) == 1) {
                if (left <= right) ans.push_back({left, right});
                left = i + 1;
                right = i;
                continue;
            }
            else right++;
        }
        if (left <= right) ans.push_back({left, right});
        return ans;
    }
};