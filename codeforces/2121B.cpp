#include <bits/stdc++.h>

std::string problem2121B() {
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::vector<int> cnt(26);
    for (int i = 0; i < n; i++) {
        cnt[s[i] - 'a']++;
    }
    for (int i = 1; i < n - 1; i++) {
        if (cnt[s[i] - 'a'] > 1) return "Yes";
    }
    return "No";
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2121B() << "\n";
    }
    return 0;
}