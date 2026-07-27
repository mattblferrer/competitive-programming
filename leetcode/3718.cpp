class Solution {
public:
    int missingMultiple(vector<int> &nums, int k) {
        set<int> num_set(nums.begin(), nums.end());
        int curr = k;
        while (true) {
            if (num_set.count(curr) == 0) return curr;
            curr += k;
        }
    }
};