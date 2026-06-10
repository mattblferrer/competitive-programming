class Solution {
public:
    int subarrayLCM(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int arr_lcm = 1;
            for (int j = i; j < n; j++) {
                arr_lcm = lcm(arr_lcm, nums[j]);
                if (arr_lcm == k) ans++;
                if (arr_lcm > k) break;
            }
        }
        return ans;
    }
};