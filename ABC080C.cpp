#include <iostream>

int ABC080C() {
    int n;
    std::cin >> n;
    int** f = new int*[n];
    int** p = new int*[n];
    for (int i = 0; i < n; i++) {
        f[i] = new int[10];
        for (int j = 0; j < 10; j++) {
            std::cin >> f[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        p[i] = new int[11];
        for (int j = 0; j < 11; j++) {
            std::cin >> p[i][j];
        }
    }
    // TODO: solve
    return 0;
}

int main() {
    std::cout << ABC080C();
    return 0;
}