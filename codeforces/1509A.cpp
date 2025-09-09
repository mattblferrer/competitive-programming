#include <iostream>

void problem1509A() {
    int n;
    std::cin >> n;
    int* a = new int[n];

    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int p = 0; p <= 1; p++) {
        for (int i = 0; i < n; i++) {
            if (a[i] % 2 == p) {
                std::cout << a[i] << " ";
            }
        }
    }
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem1509A();
    }

    return 0;
}