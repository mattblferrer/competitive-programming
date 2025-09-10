#include <algorithm>
#include <iostream>

long long ABC137A() {
    long long a, b;
    std::cin >> a >> b;
    return std::max({a + b, a - b, a * b});
}

int main() {
    std::cout << ABC137A();
    return 0;
}