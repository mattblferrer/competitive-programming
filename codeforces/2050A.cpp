#include <iostream>
#include <string>

long long problem2050A() {
    long long n, m, curr, max;
    curr = 0;
    max = 0;
    std::string input;
    std::cin >> n >> m; 
    for (long long i = 0; i < n; i++) {
        std::cin >> input;
        curr += input.length();
        if (curr <= m) {
            max++;
        }
    }
    return max;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2050A() << std::endl;
    }

    return 0;
}