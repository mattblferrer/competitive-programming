class Solution {
public:
    int smallestAbsent(vector<int> &nums) {
        int sum = 0, n = nums.size();
        for (int i = 0; i < n; i++) sum += nums[i];
        set<int> num_set(nums.begin(), nums.end());
        for (int i = 1; i <= 10001; i++) {
            if (i * n <= sum) continue;
            if (num_set.count(i) == 0) return i;
        }
        return sum;
    }
};