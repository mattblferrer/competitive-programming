class Solution {
public:
    vector<int> limitOccurrences(vector<int> &nums, int k) {
        int curr = 0, cnt = 0;
        vector<int> ans;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != curr) {
                curr = nums[i];
                cnt = 1;
            }
            else cnt++;
            if (cnt <= k) ans.push_back(curr);
        }
        return ans;
    }
};