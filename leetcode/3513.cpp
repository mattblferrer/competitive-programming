class Solution {
public:
    int uniqueXorTriplets(vector<int> &nums) {
        int n = nums.size();
        if (n == 1) return 1;
        if (n == 2) return 2;
        return 1 << bit_width((unsigned int)n);
    }
};