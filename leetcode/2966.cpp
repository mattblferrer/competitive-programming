class Solution {
public:
    vector<vector<int>> divideArray(vector<int> &nums, int k) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        int n = nums.size();
        vector<int> curr;
        for (int i = 0; i < n; i++) {
            curr.push_back(nums[i]);
            if (curr.size() == 3) {
                ans.push_back(curr);
                curr = {};
            }
        }
        for (int i = 0; i < n / 3; i++) {
            if (ans[i].back() - ans[i].front() > k) return {};
        }
        return ans;
    }
};