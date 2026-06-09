class Solution {
public:
    int maxNumberOfBalloons(string text) {
        vector<int> text_freq(26);
        for (int i = 0; i < text.size(); i++) text_freq[text[i] - 'a']++;
        return min({
            text_freq['b' - 'a'],
            text_freq['a' - 'a'],
            text_freq['l' - 'a'] / 2,
            text_freq['o' - 'a'] / 2,
            text_freq['n' - 'a']
            });
    }
};