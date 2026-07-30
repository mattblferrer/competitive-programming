class Solution {
public:
    int minimumSwaps(vector<int> &nums) {
        int n = nums.size(), zeros = 0, ans = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) zeros++;
        }
        ans = zeros;
        for (int i = n - 1; i > n - zeros - 1; i--) {
            if (nums[i] == 0) ans--;
        }
        return ans;
    }
};