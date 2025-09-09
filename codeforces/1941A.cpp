#include <iostream>

int problem1941A() {
    int n, m, k, indices;
    indices = 0;
    std::cin >> n >> m >> k;
    int* b = new int[n];
    int* c = new int[m];
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    for (int i = 0; i < m; i++) {
        std::cin >> c[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (b[i] + c[j] <= k) {
                indices++;
            }
        }
    }
    return indices;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1941A() << std::endl;
    }

    return 0;
}