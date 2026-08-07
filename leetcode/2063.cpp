class Solution {
public:
    long long countVowels(string word) {
        long long ans = 0;
        string vowels = "aeiou";
        for (int i = 0; i < word.size(); i++) {
            for (char v : vowels) {
                if (word[i] == v) { ans += (word.size() - i) * (i + 1); break; }
            }
        }
        return ans;
    }
};