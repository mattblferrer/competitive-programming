#include <iostream>

void ABC137B() {
    long long k, x;
    std::cin >> k >> x;
    for (int i = x - k + 1; i < x + k - 1; i++) {
        std::cout << i << " ";
    }
    std::cout << x + k - 1;
}

int main() {
    ABC137B();
    return 0;
}