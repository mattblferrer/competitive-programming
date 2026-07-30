class Solution {
public:
    string reverseWords(string s) {
        string ans = "";

        // split into words vector
        vector<string> words;
        string curr = "";
        for (char c : s) {
            if (c == ' ') {
                words.push_back(curr);
                curr = "";
            }
            else curr += c;
        }
        words.push_back(curr);

        // get number of vowels and process
        set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
        int first = 0;
        string &word = words[0];
        for (int i = 0; i < word.size(); i++) {
            if (vowels.count(word[i])) first++;
        }
        ans += word + ' ';

        for (int i = 1; i < words.size(); i++) {
            string &word = words[i];
            int v = 0;
            for (int j = 0; j < word.size(); j++) {
                if (vowels.count(word[j])) v++;
            }
            if (v == first) reverse(word.begin(), word.end());
            ans += word + ' ';
        }
        ans.pop_back();
        return ans;
    }
};