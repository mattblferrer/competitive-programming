#include <iostream>
#include <string>

int problem1873D() {
    int n, k, left, right;
    std::string line;
    std::cin >> n >> k >> line;
    int ops = 0;

    for (int i = 0; i < n; i++) {
        if (line[i] == 'B') {
            ops++;
            for (int j = i; j < std::min(n, i + k); j++) {
                line[j] = 'W';
            } 
        }
    }
    return ops;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1873D() << std::endl;
    }

    return 0;
}