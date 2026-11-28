#include <iostream>

int ABC046A() {
    int a, b, c;
    std::cin >> a >> b >> c;
    if (a == b && b == c) {
        return 1;
    }
    if (a == b || b == c || a == c) {
        return 2;
    }
    return 3;
}

int main() {
    std::cout << ABC046A();
    return 0;
}