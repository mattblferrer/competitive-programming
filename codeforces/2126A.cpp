#include <bits/stdc++.h>

char problem2126A() {
    std::string x;
    std::cin >> x;
    char min_char = '9';
    for (char c: x) {
        min_char = std::min(min_char, c);
    }
    return min_char;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2126A() << "\n";
    }
    return 0;
}