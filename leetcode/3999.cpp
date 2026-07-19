class Solution {
public:
    struct booth {
        int *f;
        string s;
        booth(string &s) {
            this->s = s;
            this->f = new int[2 * s.length()];
        }
        int run() {
            s.append(s);
            int n = s.length(), i, j, k = 0;
            memset(f, -1, sizeof(int) * n);
            for (j = 1; j < n; j++) {
                i = f[j - k - 1];
                while (i != -1 && s[j] != s[k + i + 1]) {
                    if (s[j] < s[k + i + 1]) k = j - i - 1;
                    i = f[i];
                }
                if (i == -1 && s[j] != s[k + i + 1]) {
                    if (s[j] < s[k + i + 1]) k = j;
                    f[j - k] = -1;
                }
                else f[j - k] = i + 1;
            }
            return k;
        }
    };

    int minimumGroups(vector<string> &words) {
        int n = words.size();
        map<pair<string, string>, int> mapping;
        for (int i = 0; i < n; i++) {
            string word = words[i];
            string even = "", odd = "";
            for (int j = 0; j < word.size(); j++) {
                if (j % 2 == 0) even += word[j];
                else odd += word[j];
            }

            booth b_even(even);
            string min_even = b_even.s.substr(b_even.run(), even.size());
            booth b_odd(odd);
            string min_odd = b_odd.s.substr(b_odd.run(), odd.size());
            mapping[{min_even, min_odd}]++;
        }
        return mapping.size();
    }
};