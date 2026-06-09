class Solution {
public:
    int countDigitOccurrences(vector<int>& nums, int digit) {
        int ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            int n = nums[i];
            while (n > 0) {
                if (n % 10 == digit) ans++;
                n /= 10;
            }
        }
        return ans;
    }
};