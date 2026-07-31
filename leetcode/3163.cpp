class Solution {
public:
    string compressedString(string word) {
        string comp = "";
        int s = 0;
        char c = word[0];
        for (int i = 0; i < word.size(); i++) {
            if ((word[i] != c) || ((word[i] == c) && (s == 9))) {
                comp += (s + '0');
                comp += c;
                s = 1;
                c = word[i];
            }
            else s++;
        }
        comp += (s + '0');
        comp += c;
        return comp;
    }
};