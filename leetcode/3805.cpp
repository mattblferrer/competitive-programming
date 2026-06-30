class Solution {
public:
    long long countPairs(vector<string> &words) {
        map<string, long long> word_shifted;
        for (string word : words) {
            int start = word[0] - 'a';
            for (int i = 0; i < word.size(); i++) {
                word[i] = 'a' + (word[i] - start + 26) % 26;
            }
            word_shifted[word]++;
        }
        long long ans = 0;
        for (const auto &pair : word_shifted) {
            ans += pair.second * (pair.second - 1) / 2;
        }
        return ans;
    }
};