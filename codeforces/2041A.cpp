#include <iostream>

int problem2041A() {
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;
    return 15 - a - b - c - d;
}

int main() {
    std::cout << problem2041A();	

    return 0;
}