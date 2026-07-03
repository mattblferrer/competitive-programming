class Solution {
public:
    long long sumAndMultiply(int n) {
        string n_str = to_string(n), x_str = "";
        long long sum = 0;
        for (int i = 0; i < n_str.size(); i++) {
            if (n_str[i] != '0') x_str += n_str[i];
            sum += n_str[i] - '0';
        }
        if (x_str == "") return 0;
        return stoll(x_str) * sum;
    }
};