#include <iostream>
#include <string>

std::string problem2039B() {
    std::string p;
    std::cin >> p;
    if (p.size() == 1) return "-1";
    for (int i = 0; i < p.size() - 1; i++) {
        if (p[i] == p[i + 1]) {
            return p.substr(i, 2);
        }
    }
    for (int i = 0; i < p.size() - 2; i++) {
        if (p[i] != p[i + 1] && p[i + 1] != p[i + 2] && p[i] != p[i + 2]) {
            return p.substr(i, 3);
        } 
    }
    return "-1";
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2039B() << std::endl;
    }

    return 0;
}