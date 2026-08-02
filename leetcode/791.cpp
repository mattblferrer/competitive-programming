class Solution {
public:
    string customSortString(string order, string s) {
        vector<int> ind(26);
        for (int i = 0; i < order.size(); i++) ind[order[i] - 'a'] = i;
        sort(s.begin(), s.end(), [&](char a, char b) {
            return ind[a - 'a'] < ind[b - 'a'];
            });
        return s;
    }
};