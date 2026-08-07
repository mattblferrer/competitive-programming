class Solution {
public:
    bool is_prime(int n) {
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) return false;
        }
        return n > 1;
    }

    bool primeSubOperation(vector<int> &nums) {
        set<int> primes = {0, 2};
        for (int i = 3; i < 1000; i += 2) {
            if (is_prime(i)) primes.insert(i);
        }
        nums[0] -= *prev(primes.lower_bound(nums[0]));
        for (int i = 1; i < nums.size(); i++) {
            nums[i] -= *prev(primes.lower_bound(nums[i] - nums[i - 1]));
        }
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i - 1] >= nums[i]) return false;
        }
        return true;
    }
};