#include <iostream>
#include <string>

std::string problem2065A() {
    std::string s;
    std::cin >> s;
    return s.substr(0, s.size() - 2) + "i";
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2065A() << "\n";
    }
    return 0;
}