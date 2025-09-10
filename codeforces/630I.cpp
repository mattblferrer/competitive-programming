#include <cmath>
#include <iostream>

long long problem630I() {
    long long n;
    std::cin >> n;
    return 24 * std::pow(4, n - 3) + 36 * (n - 3) * std::pow(4, n - 4);
}

int main() {
    std::cout << problem630I() << "\n";	
    return 0;
}