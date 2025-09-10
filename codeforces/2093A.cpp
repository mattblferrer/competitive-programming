#include <iostream>
#include <string>

std::string problem2093A() {
    int n;
    std::cin >> n;
    if (n % 2 == 0) {
        return "NO";
    }
    return "YES";
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2093A() << "\n";
    }
    return 0;
}