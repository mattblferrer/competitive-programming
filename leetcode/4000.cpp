class Solution {
public:
    int largestInteger(int n, int s) {
        string nstr = "";
        int curr = 0;
        for (int i = 0; i < n; i++) {
            int digit = min(s - curr, 9);
            nstr += '0' + digit;
            curr += digit;
        }
        if (curr != s) return -1;
        return stoi(nstr);
    }
};