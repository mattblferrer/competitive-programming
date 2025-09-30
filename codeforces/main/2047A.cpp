#include <cmath>
#include <iostream>

int problem2047A() {
    int n, a_i, curr, root, days;
    std::cin >> n;
    curr = 0;
    days = 0;

    for (int i = 0; i < n; i++) {
        std::cin >> a_i;
        curr += a_i;
        root = std::sqrt(curr);
        if ((std::pow(root, 2) == curr) && (root % 2 == 1)) {
            days++;
        }
    }
    return days;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2047A() << std::endl;
    }

    return 0;
}