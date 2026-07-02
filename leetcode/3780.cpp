class Solution {
public:
    int maximumSum(vector<int> &nums) {
        vector<vector<int>> rem(3);
        for (int i = 0; i < nums.size(); i++) {
            rem[nums[i] % 3].push_back(nums[i]);
        }
        for (int i = 0; i < 3; i++) {
            while (rem[i].size() < 3) rem[i].push_back(-10000000);
            sort(rem[i].begin(), rem[i].end(), greater<int>());
        }
        return max({0,
            rem[0][0] + rem[1][0] + rem[2][0],
            rem[0][0] + rem[0][1] + rem[0][2],
            rem[1][0] + rem[1][1] + rem[1][2],
            rem[2][0] + rem[2][1] + rem[2][2]
            });
    }
};