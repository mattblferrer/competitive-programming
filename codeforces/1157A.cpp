#include <iostream>

int problem1157A() {
    int n, diff = 0;
    std::cin >> n;
    while (n > 9) {
        n++;
        diff++;
        while (n % 10 == 0) {
            n /= 10;
        }
    }
    return diff + 9;
}

int main() {
    std::cout << problem1157A();
    return 0;
}