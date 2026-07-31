class Solution {
public:
    int minimumOperations(vector<int> &nums) {
        reverse(nums.begin(), nums.end());
        int ans = 0, n = nums.size();
        vector<int> cnt(101);
        for (int i = 0; i < n; i++) {
            cnt[nums[i]]++;
        }
        while (!nums.empty()) {
            bool distinct = true;
            for (int i = 0; i <= 100; i++) {
                if (cnt[i] > 1) {
                    distinct = false;
                    break;
                }
            }
            if (distinct) return ans;
            ans++;
            for (int i = 0; i < 3; i++) {
                cnt[nums.back()]--;
                nums.pop_back();
                if (nums.empty()) return ans;
            }
        }
        return ans;
    }
};