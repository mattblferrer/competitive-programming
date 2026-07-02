class Solution {
public:
    string trimTrailingVowels(string s) {
        while (!s.empty()) {
            bool remove = false;
            for (char c : "aeiou") {
                if (s.back() == c) {
                    s.pop_back();
                    remove = true;
                    break;
                }
            }
            if (!remove) return s;
        }
        return s;
    }
};