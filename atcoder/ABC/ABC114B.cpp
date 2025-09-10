#include <iostream>
#include <string>

int ABC114B() {
    std::string s;
    std::cin >> s;
    int length = s.length();
    int min_diff = 999;

    for (int i = 0; i < length - 2; i++) {
        int d_1 = s[i] - '0';
        int d_2 = s[i + 1] - '0';
        int d_3 = s[i + 2] - '0';
        int diff = std::abs(753 - (100 * d_1 + 10 * d_2 + d_3));
        min_diff = std::min(min_diff, diff);
    }
    return min_diff;
}

int main() {
    std::cout << ABC114B() << "\n";
    return 0;
}