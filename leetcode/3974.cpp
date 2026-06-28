class Solution {
public:
    long long maxSum(vector<int> &nums, int k, int mul) {
        long long ans = 0;
        sort(nums.begin(), nums.end(), greater<long long>());
        for (long long i = 0; i < k; i++) {
            if (mul > 1) {
                ans += (long long)nums[i] * mul;
                mul--;
            }
            else ans += nums[i];
        }
        return ans;
    }
};