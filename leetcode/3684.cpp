class Solution {
public:
    vector<int> maxKDistinct(vector<int> &nums, int k) {
        set<int, greater<int>> num_set(nums.begin(), nums.end());
        int curr = 0;
        vector<int> ans;
        for (int n : num_set) {
            ans.push_back(n);
            curr++;
            if (curr == min((int)num_set.size(), k)) break;
        }
        return ans;
    }
};