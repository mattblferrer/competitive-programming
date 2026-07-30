class Solution {
public:
    int mirrorFrequency(string s) {
        int ans = 0;
        vector<int> letters(26), numbers(10);
        for (char c : s) {
            if (('a' <= c) && (c <= 'z')) letters[c - 'a']++;
            else numbers[c - '0']++;
        }
        for (int i = 0; i < 13; i++) ans += abs(letters[i] - letters[25 - i]);
        for (int i = 0; i < 5; i++) ans += abs(numbers[i] - numbers[9 - i]);
        return ans;
    }
};