#include <iostream>

void problem1389A() {
    long long l, r;
    std::cin >> l >> r;
    if (r >= 2*l) {
        std::cout << l << " " << 2*l << std::endl;
    }
    else {
        std::cout << "-1 -1" << std::endl;
    }
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem1389A();
    }

    return 0;
}