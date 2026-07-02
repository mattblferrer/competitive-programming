class Solution {
public:
    int minimumDistance(vector<int> &nums) {
        map<int, vector<int>> pos;
        int n = nums.size(), ans = INT_MAX;
        for (int i = 0; i < n; i++) {
            pos[nums[i]].push_back(i);
        }
        for (const auto &pair : pos) {
            auto &arr = pair.second;
            if (arr.size() < 3) continue;
            for (int i = 0; i <= arr.size() - 3; i++) {
                ans = min(ans, arr[i + 1] - arr[i] + arr[i + 2] - arr[i + 1] + arr[i + 2] - arr[i]);
            }
        }
        if (ans == INT_MAX) return -1;
        return ans;
    }
};