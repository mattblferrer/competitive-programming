class Solution {
public:
    int largestInteger(vector<int> &nums, int k) {
        if (nums.size() == k) return *max_element(nums.begin(), nums.end());

        int ans = -1;
        map<int, int> cnt;
        for (int i = 0; i < nums.size(); i++) cnt[nums[i]]++;
        if (k == 1) {
            for (int i = 0; i < nums.size(); i++) {
                if (cnt[nums[i]] == 1) ans = max(ans, nums[i]);
            }
            return ans;
        }

        if (cnt[nums.front()] == 1) ans = max(ans, nums.front());
        if (cnt[nums.back()] == 1) ans = max(ans, nums.back());
        return ans;
    }
};