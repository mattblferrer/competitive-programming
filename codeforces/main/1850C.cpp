#include <iostream>
#include <string>

std::string problem1850C() {
    std::string line, word;
    for (int i = 0; i < 8; i++) {
        std::cin >> line;
        for (int j = 0; j < 8; j++) {
            if (line[j] != '.') {
                word += line[j];
            }
        }
    }
    return word;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1850C() << std::endl;
    }

    return 0;
}