class Solution {
public:
    bool is_prime(int n) {
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) return false;
        }
        return n > 1;
    }

    int minOperations(vector<int> &nums) {
        int ans = 0, n = nums.size();
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) {  // even indices
                while (!is_prime(nums[i])) {
                    nums[i]++;
                    ans++;
                }
            }
            else {  // odd indices
                while (is_prime(nums[i])) {
                    nums[i]++;
                    ans++;
                }
            }
        }
        return ans;
    }
};