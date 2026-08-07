class Solution {
public:
    long long repairCars(vector<int> &ranks, int cars) {
        long long left = 0, right = (long long)(*max_element(ranks.begin(), ranks.end())) * cars * cars;
        while (right - left > 1) {
            long long mid = midpoint(left, right);
            long long curr = 0;
            for (int i = 0; i < ranks.size(); i++) {
                curr += sqrt(mid / ranks[i]);
            }
            if (curr < cars) left = mid;
            else right = mid;
        }
        return right;
    }
};