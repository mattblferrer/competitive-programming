class Solution {
public:
    string majorityFrequencyGroup(string s) {
        map<char, int> cnt;
        int n = s.size();
        for (char c : s) cnt[c]++;
        map<int, string> freq_grp;
        for (auto pair : cnt) freq_grp[pair.second] += pair.first;
        string ans = "";
        for (auto pair : freq_grp) {
            if (pair.second.size() >= ans.size()) ans = pair.second;
        }
        return ans;
    }
};