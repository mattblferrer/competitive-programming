#include <iostream>
#include <string>

int problem1873C() {
    int score = 0;

    for (int i = 0; i < 10; i++) {
        std::string line;
        std::cin >> line;
        for (int j = 0; j < 10; j++) {
            if (line[j] == 'X') {
                score += std::min(std::min(i + 1, 10 - i), std::min(j + 1, 10 - j));
            }
        }
    }
    return score;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1873C() << std::endl;
    }

    return 0;
}