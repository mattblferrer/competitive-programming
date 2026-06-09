class Solution {
public:
    string mapWordWeights(vector<string>& words, vector<int>& weights) {
        string ans = "";
        for (int i = 0; i < words.size(); i++) {
            int weight = 0;
            for (char c : words[i]) weight += weights[c - 'a'];
            ans += (25 - weight % 26) + 'a';
        }
        return ans;
    }
};