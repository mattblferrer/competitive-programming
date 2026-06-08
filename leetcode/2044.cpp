class Solution {
public:
    int countMaxOrSubsets(vector<int>& nums) {
        map<int, int> subset_or;
        for (int i = 0; i < (1 << nums.size()); i++) {
            int curr = 0;
            for (int j = 0; j < nums.size(); j++) {
                if (i & (1 << j)) curr |= nums[j];
            }
            subset_or[curr]++;
        }
        return prev(subset_or.end())->second;
    }
};