#include <iostream>
#include <string>

int problem1927A() {
    int n, left, right;
    std::string cells;
    std::cin >> n >> cells;

    for (int i = 0; i < cells.length(); i++) {
        if (cells[i] == 'B') {
            left = i;
            break;
        }
    }
    for (int i = cells.length() - 1; i >= 0; i--) {
        if (cells[i] == 'B') {
            right = i;
            break;
        }
    }
    return right - left + 1;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1927A() << std::endl;
    }

    return 0;
}