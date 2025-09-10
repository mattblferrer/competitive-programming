#include <iostream>

long long ABC079B() {
    long long n;
    std::cin >> n;
    long long a = 2;
    long long b = 1;
    long long temp;
    for (int i = 0; i < n; i++) {
        temp = b;
        b = a + b;
        a = temp;
    }
    return a;
}

int main() {
    std::cout << ABC079B();
    return 0;
}