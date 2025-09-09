#include <bits/stdc++.h>

int problem556A() {
    int n, zeros = 0, ones = 0;
    std::string s;
    std::cin >> n >> s;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') zeros++;
        else if (s[i] == '1') ones++;
    }
    return n - 2 * std::min(zeros, ones);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << problem556A() << "\n";
    return 0;
}