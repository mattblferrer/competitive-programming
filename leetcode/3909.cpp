class Solution {
public:
    int compareBitonicSums(vector<int> &nums) {
        int n = nums.size(), maxn = 0;
        for (int i = 0; i < n; i++) maxn = max(maxn, nums[i]);
        long long asc = maxn, dec = nums[n - 1];
        for (int i = 0; i < n - 1; i++) {
            if (nums[i] < nums[i + 1]) asc += nums[i];
            else dec += nums[i];
        }
        if (asc > dec) return 0;
        else if (asc < dec) return 1;
        else return -1;
    }
};