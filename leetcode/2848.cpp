class Solution {
public:
    int numberOfPoints(vector<vector<int>> &nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> merged;
        for (auto car : nums) {
            if (merged.empty() || merged.back()[1] < car[0]) merged.push_back(car);
            else merged.back()[1] = max(merged.back()[1], car[1]);
        }
        int ans = 0;
        for (int i = 0; i < merged.size(); i++) ans += merged[i][1] - merged[i][0] + 1;
        return ans;
    }
};