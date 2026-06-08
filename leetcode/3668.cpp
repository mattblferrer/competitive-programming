class Solution {
public:
    vector<int> recoverOrder(vector<int>& order, vector<int>& friends) {
        set<int> fset;
        for (int f : friends) fset.insert(f);
        vector<int> ans;
        for (int i = 0; i < order.size(); i++) {
            if (fset.count(order[i])) ans.push_back(order[i]);
        }
        return ans;
    }
};