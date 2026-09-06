class Solution {
public:
    int countGoodRotations(vector<int> &nums) {
        int n = nums.size(), ans = 0;
        long long sum_first = 0, sum_last = 0;
        for (int i = 0; i < n / 2; i++) sum_first += nums[i];
        for (int i = n / 2; i < n; i++) sum_last += nums[i];

        for (int i = 0; i < n; i++) {
            cout << sum_first << " " << sum_last << "\n";
            if (sum_first > sum_last) ans++;

            sum_first -= nums[i];
            sum_first += nums[(i + n / 2) % n];
            sum_last -= nums[(i + n / 2) % n];
            sum_last += nums[i];
        }

        return ans;
    }
};