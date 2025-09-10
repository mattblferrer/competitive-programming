#include <algorithm>
#include <iostream>

long long problem322B() {
    long long r, g, b;
    std::cin >> r >> g >> b;
    long long max = 0;
    long long min = std::min({r, g, b});
    for (long long i = 0; i < 3; i++) {
        max = std::max(max, (r - i) / 3 + (g - i) / 3 + (b - i) / 3 + std::min(i, min));
    }

    return max;
}

int main() {
    std::cout << problem322B();
    return 0;
}