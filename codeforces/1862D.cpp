#include <cmath>
#include <iostream>

long long problem1862D() {
    long long n;
    std::cin >> n;
    long long s = std::sqrt(n * 2) - 2;
    long long t, temp, corr;
    for (int i = 0; i < 5; i++) {
        temp = (s + i) * ((s + i) - 1) / 2;
        if (temp > n) {
            corr = i - 1;
            break;
        } 
        t = temp;
    }
    long long e = n - t;
    return s + corr + e;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1862D() << "\n";
    }
    return 0;
}