class Solution {
public:
    int rotate(int n) {
        string to_str = to_string(n), ans_str = "";
        for (char c : to_str) {
            if ((c == '0') || (c == '1') || (c == '8')) ans_str += c;
            else if (c == '2') ans_str += '5';
            else if (c == '5') ans_str += '2';
            else if (c == '6') ans_str += '9';
            else if (c == '9') ans_str += '6';
            else return n;
        }
        return stoi(ans_str);
    }
    int rotatedDigits(int n) {
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (rotate(i) != i) ans++;
        }
        return ans;
    }
};