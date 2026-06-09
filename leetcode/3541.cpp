class Solution {
public:
    int maxFreqSum(string s) {
        map<char, int> vowels;
        map<char, int> consonants;
        vector<char> check = {'a', 'e', 'i', 'o', 'u'};
        for (int i = 0; i < s.size(); i++) {
            if (find(check.begin(), check.end(), s[i]) != check.end()) vowels[s[i]]++;
            else consonants[s[i]]++;
        }
        int v = 0, c = 0;
        for (auto pair : vowels) v = max(v, pair.second);
        for (auto pair : consonants) c = max(c, pair.second);
        return v + c;
    }
};