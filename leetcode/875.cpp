class Solution {
public:
    int minEatingSpeed(vector<int> &piles, int h) {
        long long left = 0, right = 1'000'000'000;
        while (right - left > 1) {
            long long k = midpoint(left, right);
            long long curr_h = 0;
            for (long long p : piles) {
                curr_h += (p + k - 1) / k;
            }
            if (curr_h <= h) right = k;
            else left = k;
        }
        return right;
    }
};