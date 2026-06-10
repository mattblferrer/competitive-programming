class Solution {
public:
    int distinctPrimeFactors(vector<int>& nums) {
        set<int> factors;
        for (int i = 0; i < nums.size(); i++) {
            int n = nums[i];
            for (int j = 2; j * j <= n; j++) {
                while (n % j == 0) {
                    factors.insert(j);
                    n /= j;
                }
            }
            if (n != 1) factors.insert(n);
        }
        return factors.size();
    }
};