#include <iostream>
#include <string>

std::string problem1971C() {
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;
    int min_1 = std::min(a, b);
    int max_1 = std::max(a, b);
    int min_2 = std::min(c, d);
    int max_2 = std::max(c, d);

    if (min_2 < max_1 && max_1 < max_2) {
        if (min_2 < min_1 && min_1 < max_2) {
            return "NO";
        }
        return "YES";
    }
    if (min_1 < max_2 && max_2 < max_1) {
        if (min_1 < min_2 && min_2 < max_1) {
            return "NO";
        }
        return "YES";
    }
    return "NO";
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1971C() << "\n";
    }

    return 0;
}