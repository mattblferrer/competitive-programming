#include <iostream>

int problem2063A() {
    int l, r;
    std::cin >> l >> r;
    if (l == 1 && r == 1) {
        return 1;
    }
    return r - l;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2063A() << "\n";
    }
    return 0;
}