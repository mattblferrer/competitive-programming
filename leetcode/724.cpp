class Solution {
public:
    int pivotIndex(vector<int> &nums) {
        int n = nums.size();
        vector<int> pref(n);
        pref[0] = nums[0];
        for (int i = 1; i < n; i++) pref[i] = pref[i - 1] + nums[i];
        if (pref[n - 1] - pref[0] == 0) return 0;
        for (int i = 1; i < n; i++) {
            if (pref[i - 1] == pref[n - 1] - pref[i]) return i;
        }
        return -1;
    }
};