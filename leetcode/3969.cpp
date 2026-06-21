class Solution {
public:
    int countValidSubarrays(vector<int> &nums, int x) {
        int ans = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            long long curr = 0;
            for (int j = i; j < n; j++) {
                curr += nums[j];
                if (curr % 10 == x && to_string(curr).front() == '0' + x) ans++;
            }
        }
        return ans;
    }
}
