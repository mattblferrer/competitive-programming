class Solution {
public:
    long long minCost(string s, vector<int> &cost) {
        long long ans = 0;
        vector<long long> letter(26);
        for (int i = 0; i < s.size(); i++) {
            letter[s[i] - 'a'] += cost[i];
        }
        for (int i = 0; i < 26; i++) ans += letter[i];
        ans -= *max_element(letter.begin(), letter.end());
        return ans;
    }
};