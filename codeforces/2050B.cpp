#include <iostream>
#include <string>
#include <vector>

std::string problem2050B() {
    long long n;
    std::cin >> n;
    std::vector<long long> a(n);
    long long even = 0;
    long long odd = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        if (i % 2 == 0) {
            even += a[i];
        }
        else {
            odd += a[i];
        }
    }
    if ((even + odd) % n != 0) return "NO";
    if (odd % (n / 2) != 0) return "NO";
    if (even % (n / 2 + n % 2) != 0) return "NO";
    if (odd / (n / 2) != even / (n / 2 + n % 2)) return "NO";
    return "YES";
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2050B() << "\n";
    }

    return 0;
}