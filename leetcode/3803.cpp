class Solution {
public:
    int residuePrefixes(string s) {
        set<char> unique;
        int ans = 0;
        for (int i = 0; i < s.size(); i++) {
            unique.insert(s[i]);
            if ((i + 1) % 3 == unique.size()) ans++;
        }
        return ans;
    }
};