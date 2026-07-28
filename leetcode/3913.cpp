class Solution {
public:
    struct v_pair {
        int cnt = 0, index = -1;
    };
    string sortVowels(string s) {
        set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
        map<char, v_pair> v_cnt;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (vowels.count(c)) {
                v_cnt[c].cnt++;  // count
                if (v_cnt[c].index == -1) v_cnt[c].index = i;  // first index
            }
        }
        vector<pair<char, v_pair>> vq(v_cnt.begin(), v_cnt.end());
        sort(vq.begin(), vq.end(), [](auto a, auto b) {
            if (a.second.cnt == b.second.cnt) return a.second.index > b.second.index;
            return a.second.cnt < b.second.cnt;
            });
        string ans = "";
        for (int i = 0; i < s.size(); i++) {
            if (vowels.count(s[i]) == 0) ans += s[i];
            else {
                ans += vq.back().first;
                vq.back().second.cnt--;
                if (vq.back().second.cnt == 0) vq.pop_back();
            }
        }
        return ans;
    }
};