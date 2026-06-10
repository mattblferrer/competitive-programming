class Solution {
public:
    int sumFourDivisors(vector<int>& nums) {
        int ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            int sum = 0, div = 0;
            for (int j = 1; j * j <= nums[i]; j++) {
                if (nums[i] % j == 0) {
                    sum += j;
                    div++;
                    if (nums[i] / j != j) {
                        sum += nums[i] / j;
                        div++;
                    }
                }
            }
            if (div == 4) {
                ans += sum;
            }
        }
        return ans;
    }
};