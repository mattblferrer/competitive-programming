class Solution {
public:
    int smallestDivisor(vector<int> &nums, int threshold) {
        int left = 0, right = 2'000'000;
        while (right - left > 1) {
            int m = midpoint(left, right);
            long long sum = 0;
            for (int i = 0; i < nums.size(); i++) {
                sum += (nums[i] + m - 1) / m;
            }
            if (sum <= threshold) right = m;
            else left = m;
        }
        return right;
    }
};