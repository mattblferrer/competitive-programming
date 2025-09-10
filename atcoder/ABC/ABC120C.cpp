#include <bits/stdc++.h>

int ABC120C() {
    std::string s;
    std::cin >> s;
    int ones = 0, zeros = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '0') zeros++;
        else ones++;
    }
    return 2 * std::min(zeros, ones);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << ABC120C() << "\n";
    return 0;
}