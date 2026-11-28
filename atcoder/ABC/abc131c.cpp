#include <iostream>
#include <numeric>

long long ABC131C() {
    long long a, b, c, d;
    std::cin >> a >> b >> c >> d;
    long long upper = b - (b / c + b / d - b / std::lcm(c, d));
    long long lower = (a - 1) - ((a - 1) / c + (a - 1) / d - (a - 1) / std::lcm(c, d));
    return upper - lower;
}

int main() {
    std::cout << ABC131C();
    return 0;
}