#include <iostream>
#include <string>

long long problem2065B() {
    std::string s;
    std::cin >> s;
    for (int i = 0; i < s.size() - 1; i++) {
        if (s[i] == s[i + 1]) {
            return 1;
        }
    }
    return s.size();
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2065B() << "\n";
    }
    return 0;
}