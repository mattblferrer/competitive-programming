#include <iostream>

int problem1926E(int n, int k) {
    if (k <= (n + 1) / 2) {
        return 2 * k - 1;
    }
    else {
        return 2 * problem1926E(n / 2, k - (n + 1) / 2);
    }
}

int main() {
    int t, n, k;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cin >> n >> k;
        std::cout << problem1926E(n, k) << "\n";
    }
    
    return 0;
}