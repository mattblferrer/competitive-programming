class Solution {
public:
    string longestWord(vector<string> &words) {
        set<string> word_set(words.begin(), words.end());
        string ans = "";
        for (string word : words) {
            string check = "";
            bool valid = true;
            for (int i = 0; i < word.size(); i++) {
                check += word[i];
                if (!word_set.count(check)) {
                    valid = false;
                    break;
                }
            }
            if (!valid) continue;
            if (ans.size() < word.size()) ans = word;
            else if (ans.size() == word.size()) ans = min(ans, word);
        }
        return ans;
    }
};