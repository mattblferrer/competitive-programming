class Solution {
public:
    int vowelConsonantScore(string s) {
        int v = 0, c = 0;
        for (char ch : s) {
            bool is_vowel = false;
            for (char check : "aeiou") {
                if (ch == check) is_vowel = true;
            }
            if (is_vowel) v++;
            else if (isalpha(ch)) c++;
        }
        if (c == 0) return 0;
        return v / c;
    }
};