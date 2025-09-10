#include <iostream>
#include <string>

char problem1742C() {
    std::string* lines = new std::string[8];
    for (int i = 0; i < 8; i++) {
        std::cin >> lines[i];
    }
    for (int i = 0; i < 8; i++) {
        bool found = true;
        for (int j = 0; j < 8; j++) {
            if (lines[i][j] == 'B') {
                found = false;
                break;
            }
        }
        if (found) {
            return 'R';
        }
    }
    return 'B';
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1742C() << "\n";
    }
    return 0;
}
