#include <iostream>

int ABC116A() {
    int ab, bc, ca;
    std::cin >> ab >> bc >> ca;
    return ab * bc / 2;
}

int main() {
    std::cout << ABC116A();
    return 0;
}