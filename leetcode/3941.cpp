class Solution {
public:
    int passwordStrength(string password) {
        set<char> lower, upper, digit, special;
        for (char c : password) {
            if (islower(c)) lower.insert(c);
            else if (isupper(c)) upper.insert(c);
            else if (isdigit(c)) digit.insert(c);
            else special.insert(c);
        }
        return lower.size() + 2 * upper.size() + 3 * digit.size() + 5 * special.size();
    }
};