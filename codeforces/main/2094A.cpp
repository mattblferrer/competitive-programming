#include <iostream>
#include <string>

std::string problem2094A() {
    std::string a, b, c;
    std::cin >> a >> b >> c;
    return a.substr(0, 1) + b.substr(0, 1) + c.substr(0, 1);
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2094A() << "\n";
    }
    return 0;
}