class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        set<int> s(nums.begin(), nums.end());
        vector<int> ans;
        for (int i = *(s.begin()); i <= *prev(s.end()); i++) {
            if (s.count(i) == 0) ans.push_back(i);
        }
        return ans;
    }
};