class Solution {
public:
    bool isDigitorialPermutation(int n) {
        string s = to_string(n);
        int sum = 0;
        for (int i = 0; i < s.size(); i++) {
            int curr = 1;
            for (int j = 1; j <= s[i] - '0'; j++) curr *= j;
            sum += curr;
        }
        string sum_s = to_string(sum);
        sort(s.begin(), s.end());
        sort(sum_s.begin(), sum_s.end());
        return (s == sum_s);
    }
};