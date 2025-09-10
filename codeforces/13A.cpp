#include <iostream>

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

void problem13A() {
    int a;
    int num = 0;
    std::cin >> a;
    for (int base = 2; base < a; base++) {
        int n = a;
        while (n > 0) {
            num += n % base;
            n /= base;
        }
    }
    int g = gcd(num, a - 2);
    std::cout << num / g << "/" << (a - 2) / g;
}

int main() {
    problem13A();

    return 0;
}