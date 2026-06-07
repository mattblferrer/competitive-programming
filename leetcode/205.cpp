class Solution {
public:
    bool isIsomorphic(string s, string t) {
        map<char, char> map1, map2;
        for (int i = 0; i < s.size(); i++) {
            if (map1.count(s[i]) == 0) map1[s[i]] = t[i];
            else if (map1[s[i]] != t[i]) return false;
        }
        for (int i = 0; i < s.size(); i++) {
            if (map2.count(t[i]) == 0) map2[t[i]] = s[i];
            else if (map2[t[i]] != s[i]) return false;
        }
        return true;
    }
};