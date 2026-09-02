class Solution {
public:
    int maxValidSplits(vector<int> &nums) {
        int m = nums.size() - 1;

        // remove no element
        int ans = 0;
        vector<int> nums_left(m + 1), nums_right(m + 1);
        int g = nums[0];
        for (int i = 0; i <= m; i++) {
            g = gcd(g, nums[i]);
            nums_left[i] = g;
        }
        g = nums[m];
        for (int i = m; i >= 0; i--) {
            g = gcd(g, nums[i]);
            nums_right[i] = g;
        }
        for (int i = 0; i < m; i++) {
            if (nums_left[i] == nums_right[i + 1]) ans++;
        }
        if (m == 1) return ans;

        // remove one element
        for (int skip = 0; skip <= m; skip++) {
            int curr = 0;

            vector<int> left(m), right(m);
            int g = (skip == 0) ? nums[1] : nums[0];
            for (int i = 0; i <= m; i++) {
                if (i == skip) continue;
                g = gcd(g, nums[i]);
                if (i > skip) left[i - 1] = g;
                else left[i] = g;
            }
            g = (skip == m) ? nums[m - 1] : nums[m];
            for (int i = m; i >= 0; i--) {
                if (i == skip) continue;
                g = gcd(g, nums[i]);
                if (i > skip) right[i - 1] = g;
                else right[i] = g;
            }
            for (int i = 0; i < m - 1; i++) {
                if (left[i] == right[i + 1]) {
                    curr++;
                }
            }
            ans = max(ans, curr);
        }
        return ans;
    }
};