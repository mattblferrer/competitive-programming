class Solution {
public:
    vector<int> toggleLightBulbs(vector<int> &bulbs) {
        vector<bool> is_on(101);
        for (int i = 0; i < bulbs.size(); i++) {
            is_on[bulbs[i]] = 1 - is_on[bulbs[i]];
        }
        vector<int> ans;
        for (int i = 1; i <= 100; i++) {
            if (is_on[i]) ans.push_back(i);
        }
        return ans;
    }
};