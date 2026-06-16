class Solution {
public:
    string processStr(string s) {
        deque<char> result;
        bool rev = false;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '*') {
                if (result.empty()) continue;
                if (rev) result.pop_front();
                else result.pop_back();
            }
            else if (s[i] == '#') {
                if (rev) {
                    string dupl(result.rbegin(), result.rend());
                    for (int j = 0; j < dupl.size(); j++) result.push_front(dupl[j]);
                }
                else {
                    string dupl(result.begin(), result.end());
                    for (int j = 0; j < dupl.size(); j++) result.push_back(dupl[j]);
                }
            }
            else if (s[i] == '%') {
                if (rev) rev = false;
                else rev = true;
            }
            else {
                if (rev) result.push_front(s[i]);
                else result.push_back(s[i]);
            }
        }
        if (rev) reverse(result.begin(), result.end());
        string fi(result.begin(), result.end());
        return fi;
    }
};